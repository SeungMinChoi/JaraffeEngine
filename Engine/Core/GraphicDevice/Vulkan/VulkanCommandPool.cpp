#include "stdafx.h"
#include "VulkanCommandPool.h"

#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"

VulkanCommandPool::VulkanCommandPool()
{
}


VulkanCommandPool::~VulkanCommandPool()
{
}

void VulkanCommandPool::CreateCommandPool(VulkanDevice* Device, VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface)
{
	VulkanPhysicalDevice::QueueFamilyIndices queueFamilyIndices = PhysicalDevice->FindQueueFamilies(PhysicalDevice->GetMainDeviceHandle(), Surface);

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
	poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(Device->GetDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

void VulkanCommandPool::Destroy(VulkanDevice* Device)
{
	vkDestroyCommandPool(Device->GetDevice(), m_CommandPool, nullptr);
}