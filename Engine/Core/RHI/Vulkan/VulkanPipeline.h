#pragma once

// TODO : 필요에 의한 리펙토링 필요.

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

	// DynamicState 를 통해 이전 구조체에서 지정한 상태의 제한된 양은 파이프 라인을 다시 만들지 않고 실제로 변경할 수 있습니다 . 뷰포트의 크기, 선 너비 및 블렌드 상수를 예로들 수 있습니다.
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
	VkPipelineColorBlendAttachmentState m_ColorBlendAttachment;	// TODO 이후 vector 로 추가 가능하도록 변경.

	VkPipelineViewportStateCreateInfo m_ViewportState = {};
	VkPipelineInputAssemblyStateCreateInfo m_InputAssemblyState = {};
	VkPipelineVertexInputStateCreateInfo m_VertexInputState = {};
	VkPipelineRasterizationStateCreateInfo m_RasterizationState = {};
	VkPipelineMultisampleStateCreateInfo m_MultisampleState = {};
	VkPipelineColorBlendStateCreateInfo m_ColorBlendState = {};
	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;
};