#include "stdafx.h"
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

VulkanDevice::VulkanDevice()
{
}

VulkanDevice::~VulkanDevice()
{
}

void VulkanDevice::Init(void* WindowHandle)
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

void VulkanDevice::Draw()
{
	const std::vector<VkCommandBuffer> commandBuffers = m_CommandBuffer->GetCommandBuffers();

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_Device, m_SwapChain->GetSwapChain(), std::numeric_limits<uint64_t>::max(), m_ImageAvailableSemaphore->GetSemaphore(), VK_NULL_HANDLE, &imageIndex);
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

	if (vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
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

	result = vkQueuePresentKHR(m_PresentQueue, &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) 
	{
		ReCreateSwapChain();
	}
	else if (result != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to present swap chain image!");
	}

	vkQueueWaitIdle(m_PresentQueue);
}

void VulkanDevice::Destroy()
{
	vkDeviceWaitIdle(m_Device); // TODO : 임시

	CleanupSwapChain();

	DestroySemaphore();
	DestroyDevice();
	DestroyPhysicalDevice();
	DestroySurface();
	DestroyInstance();
}

void VulkanDevice::Resize()
{
	ReCreateSwapChain();
}

VkDevice& VulkanDevice::GetDevice()
{
	return m_Device;
}

void VulkanDevice::CreateInstance()
{
	DestroyInstance();

	m_Instance = new VulkanInstance();
	m_Instance->CreateInstance();
}

void VulkanDevice::CreateSurface(void* WindowHandle)
{
	DestroySurface();

	m_Surface = new VulkanSurface();
	m_Surface->CreateSurface(m_Instance, WindowHandle);
}

void VulkanDevice::CreatePhysicalDevice()
{
	DestroyPhysicalDevice();

	m_PhysicalDevice = new VulkanPhysicalDevice();
	m_PhysicalDevice->Init(m_Instance, m_Surface);
}

void VulkanDevice::CreateDevice()
{
	DestroyDevice();

	const VulkanPhysicalDevice::QueueFamilyIndices mainDeviceFamilyIndices = m_PhysicalDevice->FindQueueFamilies(m_PhysicalDevice->GetMainDeviceHandle(), m_Surface);
	const std::vector<const char*>& deviceExtensions = m_PhysicalDevice->GetDeviceExtensions();

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = mainDeviceFamilyIndices.graphicsFamily;
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledLayerCount = 0;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (vkCreateDevice(m_PhysicalDevice->GetMainDeviceHandle(), &createInfo, nullptr, &m_Device) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_Device, mainDeviceFamilyIndices.graphicsFamily, 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, mainDeviceFamilyIndices.presentFamily, 0, &m_PresentQueue);
}

void VulkanDevice::CreateSwapChain()
{
	DestroySwapChain();

	m_SwapChain = new VulkanSwapChain();
	m_SwapChain->Init(this, m_PhysicalDevice, m_Surface);
}

void VulkanDevice::CreateDefalutPipeline()
{
	DestroyPipeline();

	m_Pipeline = new VulkanPipeline();

	VulkanShaderModule vertShaderModule;
	vertShaderModule.Init(this, "Shaders/Color.vert");

	VulkanShaderModule fragShaderModule;
	fragShaderModule.Init(this, "Shaders/Color.frag");

	m_Pipeline->BindShader(VK_SHADER_STAGE_VERTEX_BIT, &vertShaderModule, "main");
	m_Pipeline->BindShader(VK_SHADER_STAGE_FRAGMENT_BIT, &fragShaderModule, "main");

	VkExtent2D swapChainExtent = m_SwapChain->GetExtent();
	m_Pipeline->CreateViewportState(swapChainExtent.width, swapChainExtent.height);

	m_Pipeline->CreateInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE);

	m_Pipeline->CreateVertexInputState();

	m_Pipeline->CreateRasterizationState();

	m_Pipeline->CreateMultisampleState();

	m_Pipeline->CreateColorBlendAttachmentState();

	m_Pipeline->CreateDynamicState();

	m_Pipeline->CreateLayout(this);

	m_Pipeline->CreateRenderPass(this, m_SwapChain);

	m_Pipeline->CreateGraphicsPipeline(this);
}

void VulkanDevice::CreateFrameBuffer()
{
	DestroyFrameBuffer();

	m_FrameBuffer = new VulkanFrameBuffer();
	m_FrameBuffer->CreateFramebuffers(this, m_SwapChain, m_Pipeline);
}

void VulkanDevice::CreateCommandPool()
{
	DestroyCommandPool();

	m_CommandPool = new VulkanCommandPool();
	m_CommandPool->CreateCommandPool(this, m_PhysicalDevice, m_Surface);
}

void VulkanDevice::CreateCommandBuffer()
{
	DestroyCommandBuffer();

	m_CommandBuffer = new VulkanCommandBuffer();
	m_CommandBuffer->CreateCommandBuffer(this, m_FrameBuffer, m_CommandPool);

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

void VulkanDevice::CreateSemaphore()
{
	DestroySemaphore();

	m_ImageAvailableSemaphore = new VulkanSemaphore();
	m_ImageAvailableSemaphore->CreateSemaphore(this);

	m_RenderFinishedSemaphore = new VulkanSemaphore();
	m_RenderFinishedSemaphore->CreateSemaphore(this);
}

void VulkanDevice::DestroySwapChain()
{
	if (m_SwapChain != nullptr)
	{
		m_SwapChain->Destroy(this);
		SAFE_DELETE(m_SwapChain);
	}
}

void VulkanDevice::DestroyDevice()
{
	vkDestroyDevice(m_Device, nullptr);
}

void VulkanDevice::DestroyPhysicalDevice()
{
	SAFE_DELETE(m_PhysicalDevice);
}

void VulkanDevice::DestroySurface()
{
	if (m_Surface != nullptr)
	{
		m_Surface->DestroySurface(m_Instance);
		SAFE_DELETE(m_Surface);
	}
}

void VulkanDevice::DestroyInstance()
{
	if (m_Instance != nullptr)
	{
		m_Instance->DestroyInstance();
		SAFE_DELETE(m_Instance);
	}
}

void VulkanDevice::DestroyPipeline()
{
	if (m_Pipeline != nullptr)
	{
		m_Pipeline->Destroy(this);
		SAFE_DELETE(m_Pipeline);
	}
}

void VulkanDevice::DestroyFrameBuffer()
{
	if (m_FrameBuffer != nullptr)
	{
		m_FrameBuffer->Destroy(this);
		SAFE_DELETE(m_FrameBuffer);
	}
}

void VulkanDevice::DestroyCommandPool()
{
	if (m_CommandPool != nullptr)
	{
		m_CommandPool->Destroy(this);
		SAFE_DELETE(m_CommandPool);
	}
}

void VulkanDevice::DestroyCommandBuffer()
{
	if (m_CommandBuffer != nullptr)
	{
		m_CommandBuffer->Destroy();
		SAFE_DELETE(m_CommandBuffer);
	}
}

void VulkanDevice::DestroySemaphore()
{
	if (m_ImageAvailableSemaphore != nullptr)
	{
		m_ImageAvailableSemaphore->Destroy(this);
		SAFE_DELETE(m_ImageAvailableSemaphore);
	}

	if (m_RenderFinishedSemaphore != nullptr)
	{
		m_RenderFinishedSemaphore->Destroy(this);
		SAFE_DELETE(m_RenderFinishedSemaphore);
	}
}

void VulkanDevice::ReCreateSwapChain()
{
	vkDeviceWaitIdle(m_Device);

	CleanupSwapChain();

	CreateSwapChain();
	CreateDefalutPipeline();
	CreateFrameBuffer();
	CreateCommandPool();
	CreateCommandBuffer();
}

void VulkanDevice::CleanupSwapChain()
{
	DestroyFrameBuffer();

	vkFreeCommandBuffers(m_Device, m_CommandPool->GetCommandPool(), static_cast<uint32_t>(m_CommandBuffer->GetCommandBuffers().size()), m_CommandBuffer->GetCommandBuffers().data());
	DestroyCommandPool();
	DestroyCommandBuffer();

	DestroyPipeline();

	DestroySwapChain();
}