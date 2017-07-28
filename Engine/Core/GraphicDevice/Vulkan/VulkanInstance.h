#pragma once

class VulkanInstance
{
public:
	VulkanInstance();
	virtual ~VulkanInstance();

public:
	void CreateInstance();
	void DestroyInstance();

	VkInstance& GetInstance();

private:
	VkInstance m_Instance;
};