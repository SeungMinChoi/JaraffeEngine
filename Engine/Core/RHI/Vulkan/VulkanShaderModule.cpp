#include "stdafx.h"
#include "VulkanShaderModule.h"

#include "VulkanDevice.h"

VulkanShaderModule::VulkanShaderModule()
{
}

VulkanShaderModule::~VulkanShaderModule()
{
}

void VulkanShaderModule::Init(VulkanDevice* Device, const std::string& ShaderName)
{
	CreateShaderModule(Device, ShaderName);
}

void VulkanShaderModule::Destroy(VulkanDevice* Device)
{
	vkDestroyShaderModule(Device->GetDevice(), m_ShaderModule, nullptr);
}

VkShaderModule& VulkanShaderModule::GetShaderModule()
{
	return m_ShaderModule;
}

void VulkanShaderModule::CreateShaderModule(VulkanDevice* Device, const std::string& ShaderName)
{
	std::vector<char>& shaderCode = GenericFile::ReadFile(ShaderName);

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderCode.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

	if (vkCreateShaderModule(Device->GetDevice(), &createInfo, nullptr, &m_ShaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module!");
	}
}