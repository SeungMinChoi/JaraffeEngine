#include "stdafx.h"
#include "VulkanDevice.h"

#include "VulkanPhysicalDevice.h"

VulkanDevice::VulkanDevice()
{
}

VulkanDevice::~VulkanDevice()
{
}

void VulkanDevice::CreateDevice(VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface)
{
	const VulkanPhysicalDevice::QueueFamilyIndices mainDeviceFamilyIndices = PhysicalDevice->FindQueueFamilies(PhysicalDevice->GetMainDeviceHandle(), Surface);
	const std::vector<const char*>& deviceExtensions = PhysicalDevice->GetDeviceExtensions();

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

	if (vkCreateDevice(PhysicalDevice->GetMainDeviceHandle(), &createInfo, nullptr, &m_Device) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_Device, mainDeviceFamilyIndices.graphicsFamily, 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, mainDeviceFamilyIndices.presentFamily, 0, &m_PresentQueue);
}

void VulkanDevice::Destroy()
{
    vkDestroyDevice(m_Device, nullptr);
}