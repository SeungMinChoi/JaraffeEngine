#include "stdafx.h"
#include "VulkanSurface.h"

#include "VulkanInstance.h"

VulkanSurface::VulkanSurface()
{
}

VulkanSurface::~VulkanSurface()
{
}

void VulkanSurface::CreateSurface(VulkanInstance* Instance, void* WindowHandle)
{
	if (glfwCreateWindowSurface(Instance->GetInstance(), (GLFWwindow*)WindowHandle, nullptr, &m_Surface) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

void VulkanSurface::DestroySurface(VulkanInstance* Instance)
{
	vkDestroySurfaceKHR(Instance->GetInstance(), m_Surface, nullptr);
}

VkSurfaceKHR& VulkanSurface::GetSurface()
{
	return m_Surface;
}