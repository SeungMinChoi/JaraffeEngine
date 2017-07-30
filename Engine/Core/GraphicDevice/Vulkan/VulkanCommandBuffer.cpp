#include "stdafx.h"
#include "VulkanCommandBuffer.h"

#include "VulkanDevice.h"
#include "VulkanFrameBuffer.h"
#include "VulkanCommandPool.h"

VulkanCommandBuffer::VulkanCommandBuffer()
{
}


VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

void VulkanCommandBuffer::CreateCommandBuffer(VulkanDevice* Device, VulkanFrameBuffer* FrameBuffer, VulkanCommandPool* CommandPool)
{
	const std::vector<VkFramebuffer> frameBuffers = FrameBuffer->GetFrameBuffers();

	m_CommandBuffers.resize(frameBuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = CommandPool->GetCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

	if (vkAllocateCommandBuffers(Device->GetDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void VulkanCommandBuffer::Destroy()
{
	m_CommandBuffers.clear();
}
