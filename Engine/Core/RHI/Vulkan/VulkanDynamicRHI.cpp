#include "stdafx.h"
#include "VulkanDynamicRHI.h"

#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include "VulkanPipeline.h"
#include "VulkanInstance.h"
#include "VulkanSwapchain.h"
#include "VulkanSemaphore.h"
#include "VulkanFrameBuffer.h"
#include "VulkanCommandPool.h"
#include "VulkanShaderModule.h"
#include "VulkanCommandBuffer.h"
#include "VulkanPhysicalDevice.h"

VulkanDynamicRHI::VulkanDynamicRHI()
{
}


VulkanDynamicRHI::~VulkanDynamicRHI()
{
}

void VulkanDynamicRHI::Init(void* WindowHandle)
{
    CreateInstance();
    CreateSurface(WindowHandle);
    CreatePhysicalDevice();
    CreateDevice();
    CreateSwapChain();
    CreateDefalutPipeline();
    CreateFrameBuffer();
    CreateCommandPool();
    CreateCommandBuffer();
    CreateSemaphore();
}

void VulkanDynamicRHI::Draw()
{
    const std::vector<VkCommandBuffer> commandBuffers = m_CommandBuffer->GetCommandBuffers();

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(m_Device->GetDevice(), m_SwapChain->GetSwapChain(), std::numeric_limits<uint64_t>::max(), m_ImageAvailableSemaphore->GetSemaphore(), VK_NULL_HANDLE, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        ReCreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphore->GetSemaphore() };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore->GetSemaphore() };

    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { m_SwapChain->GetSwapChain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(m_Device->GetPresentQueue(), &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        ReCreateSwapChain();
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to present swap chain image!");
    }

    vkQueueWaitIdle(m_Device->GetPresentQueue());
}

void VulkanDynamicRHI::Destroy()
{
    vkDeviceWaitIdle(m_Device->GetDevice()); // TODO : 임시

    CleanupSwapChain();

    DestroySemaphore();
    DestroyDevice();
    DestroyPhysicalDevice();
    DestroySurface();
    DestroyInstance();
}

void VulkanDynamicRHI::Resize()
{
    ReCreateSwapChain();
}

void VulkanDynamicRHI::CreateInstance()
{
    DestroyInstance();

    m_Instance = new VulkanInstance();
    m_Instance->CreateInstance();
}

void VulkanDynamicRHI::CreateSurface(void * WindowHandle)
{
    DestroySurface();

    m_Surface = new VulkanSurface();
    m_Surface->CreateSurface(m_Instance, WindowHandle);
}

void VulkanDynamicRHI::CreatePhysicalDevice()
{
    DestroyPhysicalDevice();

    m_PhysicalDevice = new VulkanPhysicalDevice();
    m_PhysicalDevice->Init(m_Instance, m_Surface);
}

void VulkanDynamicRHI::CreateDevice()
{
    DestroyDevice();

    m_Device = new VulkanDevice();
    m_Device->CreateDevice(m_PhysicalDevice, m_Surface);
}

void VulkanDynamicRHI::CreateSwapChain()
{
    DestroySwapChain();

    m_SwapChain = new VulkanSwapChain();
    m_SwapChain->Init(m_Device, m_PhysicalDevice, m_Surface);
}

void VulkanDynamicRHI::CreateDefalutPipeline()
{
    DestroyPipeline();

    m_Pipeline = new VulkanPipeline();

    VulkanShaderModule vertShaderModule;
    vertShaderModule.Init(m_Device, "Shaders/Color.vert");

    VulkanShaderModule fragShaderModule;
    fragShaderModule.Init(m_Device, "Shaders/Color.frag");

    m_Pipeline->BindShader(VK_SHADER_STAGE_VERTEX_BIT, &vertShaderModule, "main");
    m_Pipeline->BindShader(VK_SHADER_STAGE_FRAGMENT_BIT, &fragShaderModule, "main");

    VkExtent2D swapChainExtent = m_SwapChain->GetExtent();
    m_Pipeline->CreateViewportState(swapChainExtent.width, swapChainExtent.height);

    m_Pipeline->CreateInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE);

    std::vector<VertexDescription> vertexDescriptions;
    vertexDescriptions.push_back(VertexLayout::PosColor::GetVertexDescription());
    m_Pipeline->CreateVertexInputState(vertexDescriptions);

    m_Pipeline->CreateRasterizationState();

    m_Pipeline->CreateMultisampleState();

    m_Pipeline->CreateColorBlendAttachmentState();

    m_Pipeline->CreateDynamicState();

    m_Pipeline->CreateLayout(m_Device);

    m_Pipeline->CreateRenderPass(m_Device, m_SwapChain);

    m_Pipeline->CreateGraphicsPipeline(m_Device);
}

void VulkanDynamicRHI::CreateFrameBuffer()
{
    DestroyFrameBuffer();

    m_FrameBuffer = new VulkanFrameBuffer();
    m_FrameBuffer->CreateFramebuffers(m_Device, m_SwapChain, m_Pipeline);
}

void VulkanDynamicRHI::CreateCommandPool()
{
    DestroyCommandPool();

    m_CommandPool = new VulkanCommandPool();
    m_CommandPool->CreateCommandPool(m_Device, m_PhysicalDevice, m_Surface);
}

void VulkanDynamicRHI::CreateCommandBuffer()
{
    DestroyCommandBuffer();

    m_CommandBuffer = new VulkanCommandBuffer();
    m_CommandBuffer->CreateCommandBuffer(m_Device, m_FrameBuffer, m_CommandPool);

    // TODO : 이후 CommandBuffer 생성할때 Draw 할 정보들을 담고 있는 vector 같은걸로 입력하도록 수정하기.
    const VkExtent2D swapChainExtent = m_SwapChain->GetExtent();
    const std::vector<VkFramebuffer> frameBuffers = m_FrameBuffer->GetFrameBuffers();
    const std::vector<VkCommandBuffer> commandBuffers = m_CommandBuffer->GetCommandBuffers();

    for (size_t i = 0; i < commandBuffers.size(); ++i)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_Pipeline->GetRenderPass();
        renderPassInfo.framebuffer = frameBuffers[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChainExtent;

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline->GetGraphicsPipeline());

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

void VulkanDynamicRHI::CreateSemaphore()
{
    DestroySemaphore();

    m_ImageAvailableSemaphore = new VulkanSemaphore();
    m_ImageAvailableSemaphore->CreateSemaphore(m_Device);

    m_RenderFinishedSemaphore = new VulkanSemaphore();
    m_RenderFinishedSemaphore->CreateSemaphore(m_Device);
}

void VulkanDynamicRHI::DestroySwapChain()
{
    if (m_SwapChain != nullptr)
    {
        m_SwapChain->Destroy(m_Device);
        SAFE_DELETE(m_SwapChain);
    }
}

void VulkanDynamicRHI::DestroyDevice()
{
    if (m_Device != nullptr)
    {
        m_Device->Destroy();
        SAFE_DELETE(m_Device);
    }
}

void VulkanDynamicRHI::DestroyPhysicalDevice()
{
    SAFE_DELETE(m_PhysicalDevice);
}

void VulkanDynamicRHI::DestroySurface()
{
    if (m_Surface != nullptr)
    {
        m_Surface->DestroySurface(m_Instance);
        SAFE_DELETE(m_Surface);
    }
}

void VulkanDynamicRHI::DestroyInstance()
{
    if (m_Instance != nullptr)
    {
        m_Instance->DestroyInstance();
        SAFE_DELETE(m_Instance);
    }
}

void VulkanDynamicRHI::DestroyPipeline()
{
    if (m_Pipeline != nullptr)
    {
        m_Pipeline->Destroy(m_Device);
        SAFE_DELETE(m_Pipeline);
    }
}

void VulkanDynamicRHI::DestroyFrameBuffer()
{
    if (m_FrameBuffer != nullptr)
    {
        m_FrameBuffer->Destroy(m_Device);
        SAFE_DELETE(m_FrameBuffer);
    }
}

void VulkanDynamicRHI::DestroyCommandPool()
{
    if (m_CommandPool != nullptr)
    {
        m_CommandPool->Destroy(m_Device);
        SAFE_DELETE(m_CommandPool);
    }
}

void VulkanDynamicRHI::DestroyCommandBuffer()
{
    if (m_CommandBuffer != nullptr)
    {
        m_CommandBuffer->Destroy();
        SAFE_DELETE(m_CommandBuffer);
    }
}

void VulkanDynamicRHI::DestroySemaphore()
{
    if (m_ImageAvailableSemaphore != nullptr)
    {
        m_ImageAvailableSemaphore->Destroy(m_Device);
        SAFE_DELETE(m_ImageAvailableSemaphore);
    }

    if (m_RenderFinishedSemaphore != nullptr)
    {
        m_RenderFinishedSemaphore->Destroy(m_Device);
        SAFE_DELETE(m_RenderFinishedSemaphore);
    }
}

void VulkanDynamicRHI::ReCreateSwapChain()
{
    vkDeviceWaitIdle(m_Device->GetDevice());

    CleanupSwapChain();

    CreateSwapChain();
    CreateDefalutPipeline();
    CreateFrameBuffer();
    CreateCommandPool();
    CreateCommandBuffer();
}

void VulkanDynamicRHI::CleanupSwapChain()
{
    DestroyFrameBuffer();

    vkFreeCommandBuffers(m_Device->GetDevice(), m_CommandPool->GetCommandPool(), static_cast<uint32_t>(m_CommandBuffer->GetCommandBuffers().size()), m_CommandBuffer->GetCommandBuffers().data());
    DestroyCommandPool();
    DestroyCommandBuffer();

    DestroyPipeline();

    DestroySwapChain();
}
