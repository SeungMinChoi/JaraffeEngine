#pragma once

class VulkanDevice;
class VulkanShaderModule
{
public:
	VulkanShaderModule();
	virtual ~VulkanShaderModule();

public:
	void Init(VulkanDevice* Device, const std::string& ShaderName);
	void Destroy(VulkanDevice* Device);

	VkShaderModule& GetShaderModule();

private:
	void CreateShaderModule(VulkanDevice* Device, const std::string& ShaderName);

private:
	VkShaderModule m_ShaderModule;
};