#pragma once

class VulkanDevice;
class VulkanSurface;
class VulkanPhysicalDevice;
class VulkanCommandPool
{
public:
	VulkanCommandPool();
	virtual ~VulkanCommandPool();

public:
	void CreateCommandPool(VulkanDevice* Device, VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface);
	void Destroy(VulkanDevice* Device);

	VkCommandPool GetCommandPool() { return m_CommandPool; }

private:
	VkCommandPool m_CommandPool;
};