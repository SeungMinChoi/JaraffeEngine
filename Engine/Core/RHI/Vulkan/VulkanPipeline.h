#pragma once

// TODO : �ʿ信 ���� �����丵 �ʿ�.

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

	VkRenderPass GetRenderPass() { return m_RenderPass; }
	VkPipeline GetGraphicsPipeline() { return m_GraphicsPipeline; }

public:
	void CreateViewportState(const uint32_t Width, const uint32_t Height);

	void CreateInputAssemblyState(const VkPrimitiveTopology PrimitiveTopology, const bool PrimitiveRestartEnable);

	void CreateVertexInputState(std::vector<VertexDescription>& VertexDescriptions);

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

	void BindShader(const VkShaderStageFlagBits ShaderStageFlag, VulkanShaderModule* ShaderModule, const char* EntryPointName);

private:
	VkPipelineLayout m_PipelineLayout;
	VkRenderPass m_RenderPass;
	VkPipeline m_GraphicsPipeline;

	VkViewport m_Viewport = {};
	VkRect2D m_Scissor = {};
	VkPipelineColorBlendAttachmentState m_ColorBlendAttachment;	// TODO ���� vector �� �߰� �����ϵ��� ����.

	VkPipelineViewportStateCreateInfo m_ViewportState = {};
	VkPipelineInputAssemblyStateCreateInfo m_InputAssemblyState = {};
	VkPipelineVertexInputStateCreateInfo m_VertexInputState = {};
	VkPipelineRasterizationStateCreateInfo m_RasterizationState = {};
	VkPipelineMultisampleStateCreateInfo m_MultisampleState = {};
	VkPipelineColorBlendStateCreateInfo m_ColorBlendState = {};
	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
};