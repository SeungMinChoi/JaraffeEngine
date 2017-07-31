#pragma once

class VulkanSurface;
class VulkanPhysicalDevice;
class VulkanDevice
{
public:
	VulkanDevice();
	virtual ~VulkanDevice();

public:
    void CreateDevice(VulkanPhysicalDevice* PhysicalDevice, VulkanSurface* Surface);
    void Destroy();

    VkDevice& GetDevice() { return m_Device; }
    VkQueue& GetGraphicsQueue() { return m_GraphicsQueue; }
    VkQueue& GetPresentQueue() { return m_PresentQueue; }

private:
	VkDevice m_Device;

	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;
};