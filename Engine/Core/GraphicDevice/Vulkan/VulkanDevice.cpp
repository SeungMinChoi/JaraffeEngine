#include "stdafx.h"
#include "VulkanDevice.h"

#include "VulkanSurface.h"
#include "VulkanInstance.h"
#include "VulkanSwapchain.h"
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
}

void VulkanDevice::Destroy()
{
	DestroySwapChain();
	DestroyDevice();
	DestroyPhysicalDevice();
	DestroySurface();
	DestroyInstance();
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