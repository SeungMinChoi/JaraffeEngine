#include "stdafx.h"
#include "VulkanSemaphore.h"

#include "VulkanDevice.h"

VulkanSemaphore::VulkanSemaphore()
{
}

VulkanSemaphore::~VulkanSemaphore()
{
}

void VulkanSemaphore::CreateSemaphore(VulkanDevice* Device)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(Device->GetDevice(), &semaphoreInfo, nullptr, &m_Semaphore) != VK_SUCCESS )
	{
		throw std::runtime_error("failed to create semaphores!");
	}
}

void VulkanSemaphore::Destroy(VulkanDevice* Device)
{
	vkDestroySemaphore(Device->GetDevice(), m_Semaphore, nullptr);
}