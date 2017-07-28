#pragma once

class VulkanExtensionsInfo
{
public:
	VulkanExtensionsInfo();
	virtual ~VulkanExtensionsInfo();

public:
	static std::vector<const char*> GetRequiredExtensions();
};