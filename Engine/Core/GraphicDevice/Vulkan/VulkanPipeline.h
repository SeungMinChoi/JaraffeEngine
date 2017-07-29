#pragma once

class VulkanDevice;
class VulkanSwapChain;
class VulkanShaderModule;
class VulkanPipeline
{
public:
	VulkanPipeline();
	virtual ~VulkanPipeline();

public:
	void Destroy(VulkanDevice* Device);

public:
	void CreateViewportState(const uint32_t Width, const uint32_t Height);

	void CreateInputAssemblyState(const VkPrimitiveTopology PrimitiveTopology, const bool PrimitiveRestartEnable);

	void CreateVertexInputState();

	void CreateRasterizationState(
		const VkPolygonMode PolygonMode = VK_POLYGON_MODE_FILL
		, const VkCullModeFlags CullMode = VK_CULL_MODE_BACK_BIT
		, const VkFrontFace FrontFace = VK_FRONT_FACE_CLOCKWISE
		, const bool DepthClampEnable = false
		, const bool RasterizerDiscardEnable = false);

	void CreateMultisampleState();

	void CreateColorBlendAttachmentState();

	// DynamicState �� ���� ���� ����ü���� ������ ������ ���ѵ� ���� ������ ������ �ٽ� ������ �ʰ� ������ ������ �� �ֽ��ϴ� . ����Ʈ�� ũ��, �� �ʺ� �� ���� ����� ���ε� �� �ֽ��ϴ�.
	void CreateDynamicState();

	void CreateLayout(VulkanDevice* Device);

	void CreateRenderPass(VulkanDevice* Device, VulkanSwapChain* SwapChain);

	void CreateGraphicsPipeline(VulkanDevice* Device);

	void BindShader(const VkShaderStageFlagBits ShaderStageFlag, VulkanShaderModule* ShaderModule, const std::string& EntryPointName);

private:
	VkPipelineLayout m_PipelineLayout;
	VkRenderPass m_RenderPass;
	VkPipeline m_GraphicsPipeline;

	VkPipelineInputAssemblyStateCreateInfo m_InputAssemblyState = {};
	VkPipelineVertexInputStateCreateInfo m_VertexInputState = {};
	VkPipelineViewportStateCreateInfo m_ViewportState = {};
	VkPipelineRasterizationStateCreateInfo m_RasterizationState = {};
	VkPipelineMultisampleStateCreateInfo m_MultisampleState = {};
	VkPipelineColorBlendStateCreateInfo m_ColorBlendState = {};
	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
};