#include "stdafx.h"
#include "VulkanExtensionsInfo.h"

VulkanExtensionsInfo::VulkanExtensionsInfo()
{
}

VulkanExtensionsInfo::~VulkanExtensionsInfo()
{
}

std::vector<const char*> VulkanExtensionsInfo::GetRequiredExtensions()
{
	std::vector<const char*> extensions;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (uint32_t i = 0; i < glfwExtensionCount; ++i)
	{
		extensions.push_back(glfwExtensions[i]);
	}

	return extensions;
}