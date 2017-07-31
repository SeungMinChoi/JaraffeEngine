#include "stdafx.h"
#include "VulkanFrameBuffer.h"

#include "VulkanDevice.h"
#include "VulkanPipeline.h"
#include "VulkanSwapchain.h"

VulkanFrameBuffer::VulkanFrameBuffer()
{
}


VulkanFrameBuffer::~VulkanFrameBuffer()
{
}

void VulkanFrameBuffer::CreateFramebuffers(VulkanDevice* Device, VulkanSwapChain* SwapChain, VulkanPipeline* Pipeline)
{
	const VkExtent2D swapChainExtent = SwapChain->GetExtent();
	const std::vector<VkImageView> swapChainImageViews = SwapChain->GetSwapChainImageViews();

	m_Framebuffers.resize(swapChainImageViews.size());

	for (size_t i = 0; i < swapChainImageViews.size(); ++i) 
	{
		VkImageView attachments[] = 
		{
			swapChainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = Pipeline->GetRenderPass();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(Device->GetDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}

void VulkanFrameBuffer::Destroy(VulkanDevice* Device)
{
	for (size_t i = 0; i < m_Framebuffers.size(); ++i)
	{
		vkDestroyFramebuffer(Device->GetDevice(), m_Framebuffers[i], nullptr);
	}
}
