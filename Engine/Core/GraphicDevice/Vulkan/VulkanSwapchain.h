#pragma once

class VulkanDevice;
class VulkanSurface;
class VulkanPhysicalDevice;
class VulkanSwapChain
{
public:
	VulkanSwapChain();
	virtual ~VulkanSwapChain();

public:
	void Init(VulkanDevice* Device, VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface);
	void Destroy(VulkanDevice* Device);

	std::vector<VkImageView> GetSwapChainImageViews() { return m_SwapChainImageViews; }
	VkFormat GetImageFormat() { return m_SwapChainImageFormat; }
	VkExtent2D GetExtent() { return m_SwapChainExtent; }
	VkSwapchainKHR GetSwapChain() { return m_SwapChain; }

private:
	void CreateSwapChain(VulkanDevice* Device, VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface);
	void CreateImageViews(VulkanDevice* Device);

	void DestroySwapChain(VulkanDevice* Device);
	void DestroyImageViews(VulkanDevice* Device);

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> AvailablePresentModes);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats);

private:
	VkSwapchainKHR m_SwapChain;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;
	std::vector<VkImage> m_SwapChainImages;
	std::vector<VkImageView> m_SwapChainImageViews;
};