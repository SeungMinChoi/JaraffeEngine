#pragma once

// TODO : 이후 이쪽 구조 한번 리펙토링 필요.

class VulkanSurface;
class VulkanInstance;
class VulkanPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	virtual ~VulkanPhysicalDevice();

public:
	struct QueueFamilyIndices
	{
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete() 
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

public:
	void Init(VulkanInstance* Instance, VulkanSurface* Surface);

	VkPhysicalDevice& GetMainDeviceHandle();
	std::vector<const char*>& GetDeviceExtensions();
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device, VulkanSurface* Surface);
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice Device, VulkanSurface* Surface);
	
private:
	bool IsDeviceSuitable(VkPhysicalDevice Device, VulkanSurface* Surface);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice Device);
	
private:
	VkPhysicalDevice m_MainPhysicalDevice = VK_NULL_HANDLE;

	std::vector<const char*> m_DeviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
};

