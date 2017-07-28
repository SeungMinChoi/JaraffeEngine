#pragma once

class VulkanSurface
{
public:
	VulkanSurface();
	virtual ~VulkanSurface();

public:
	void CreateSurface(class VulkanInstance* Instance, void* WindowHandle);
	void DestroySurface(class VulkanInstance* Instance);

	VkSurfaceKHR& GetSurface();

private:
	VkSurfaceKHR m_Surface;
};