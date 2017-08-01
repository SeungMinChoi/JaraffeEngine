#include "stdafx.h"
#include "VulkanPipeline.h"

#include "VulkanConverter.h"

#include "VulkanDevice.h"
#include "VulkanShaderModule.h"
#include "VulkanSwapchain.h"

VulkanPipeline::VulkanPipeline()
{
}

VulkanPipeline::~VulkanPipeline()
{
}

void VulkanPipeline::Destroy(VulkanDevice* Device)
{
	vkDestroyPipeline(Device->GetDevice(), m_GraphicsPipeline, nullptr);
	vkDestroyPipelineLayout(Device->GetDevice(), m_PipelineLayout, nullptr);
	vkDestroyRenderPass(Device->GetDevice(), m_RenderPass, nullptr);
}

void VulkanPipeline::CreateViewportState(const uint32_t Width, const uint32_t Height)
{
	VkExtent2D extent;
	extent.width = Width;
	extent.height = Height;

	m_Viewport.x = 0.0f;
	m_Viewport.y = 0.0f;
	m_Viewport.width = (float)Width;
	m_Viewport.height = (float)Height;
	m_Viewport.minDepth = 0.0f;
	m_Viewport.maxDepth = 1.0f;

	m_Scissor.offset = { 0, 0 };
	m_Scissor.extent = extent;

	m_ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_ViewportState.viewportCount = 1;
	m_ViewportState.pViewports = &m_Viewport;
	m_ViewportState.scissorCount = 1;
	m_ViewportState.pScissors = &m_Scissor;
}

void VulkanPipeline::CreateInputAssemblyState(const VkPrimitiveTopology PrimitiveTopology, const bool PrimitiveRestartEnable)
{
	m_InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	m_InputAssemblyState.topology = PrimitiveTopology;
	m_InputAssemblyState.primitiveRestartEnable = PrimitiveRestartEnable;
}

void VulkanPipeline::CreateVertexInputState(std::vector<VertexDescription>& VertexDescriptions)
{
    // TODO : 여기 파이프라인 정리되면 정리하기;;
    std::vector<VkVertexInputBindingDescription> bindingDescription(VertexDescriptions.size());
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

    uint32_t bindingDescriptionCount = 0;
    uint32_t attributeDescriptionsCount = 0;
    for(uint32_t i = 0; i < VertexDescriptions.size(); ++i)
    {
        bindingDescription[i].binding = i;
        bindingDescription[i].stride = VertexDescriptions[i].stride;
        bindingDescription[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        for (uint32_t j = 0; j < VertexDescriptions[i].attributes.size(); ++j)
        {
            VkVertexInputAttributeDescription attributeDescription;
            attributeDescription.binding = i;
            attributeDescription.location = VertexDescriptions[i].attributes[j].location;
            attributeDescription.offset = VertexDescriptions[i].attributes[j].offset;
            attributeDescription.format = JFToVkFormat(VertexDescriptions[i].attributes[j].format);

            attributeDescriptions.push_back(attributeDescription);

            ++attributeDescriptionsCount;
        }

        ++bindingDescriptionCount;
    }

	m_VertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	m_VertexInputState.vertexBindingDescriptionCount = bindingDescriptionCount;
	m_VertexInputState.vertexAttributeDescriptionCount = attributeDescriptionsCount;

	m_VertexInputState.pVertexBindingDescriptions = bindingDescription.data(); // Optional
	m_VertexInputState.pVertexAttributeDescriptions = attributeDescriptions.data(); // Optional
}

void VulkanPipeline::CreateRasterizationState(
	const VkPolygonMode PolygonMode
	, const VkCullModeFlags CullMode
	, const VkFrontFace FrontFace
	, const bool DepthClampEnable
	, const bool RasterizerDiscardEnable)
{
	m_RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	m_RasterizationState.depthClampEnable = DepthClampEnable;	// VK_TRUE하면 near 및 far 비행기를 벗어난 파편이 파기되지 않고 클램핑됩니다. 그림자 맵과 같은 특별한 경우에 유용합니다. 이를 사용하려면 GPU 기능을 활성화해야합니다.
	m_RasterizationState.rasterizerDiscardEnable = RasterizerDiscardEnable; // VK_TRUE하면 프레임 버퍼에 대한 모든 출력을 비활성화합니다.
	m_RasterizationState.polygonMode = PolygonMode;
	m_RasterizationState.lineWidth = 1.0f;
	m_RasterizationState.cullMode = CullMode;
	m_RasterizationState.frontFace = FrontFace;

	// 이후 그림자맵 에 활용.
	m_RasterizationState.depthBiasEnable = VK_FALSE;
	m_RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
	m_RasterizationState.depthBiasClamp = 0.0f; // Optional
	m_RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional
}

void VulkanPipeline::CreateMultisampleState()
{
	m_MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	m_MultisampleState.sampleShadingEnable = VK_FALSE;
	m_MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	m_MultisampleState.minSampleShading = 1.0f; // Optional
	m_MultisampleState.pSampleMask = nullptr; // Optional
	m_MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
	m_MultisampleState.alphaToOneEnable = VK_FALSE; // Optional
}

void VulkanPipeline::CreateColorBlendAttachmentState()
{
	m_ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	m_ColorBlendAttachment.blendEnable = VK_FALSE;
	m_ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	m_ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	m_ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	m_ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	m_ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	m_ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	m_ColorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	m_ColorBlendState.logicOpEnable = VK_FALSE;
	m_ColorBlendState.logicOp = VK_LOGIC_OP_COPY; // Optional
	m_ColorBlendState.attachmentCount = 1;
	m_ColorBlendState.pAttachments = &m_ColorBlendAttachment;
	m_ColorBlendState.blendConstants[0] = 0.0f; // Optional
	m_ColorBlendState.blendConstants[1] = 0.0f; // Optional
	m_ColorBlendState.blendConstants[2] = 0.0f; // Optional
	m_ColorBlendState.blendConstants[3] = 0.0f; // Optional
}

void VulkanPipeline::CreateDynamicState()
{
	// 아직 사용 안함.
	VkDynamicState dynamicStates[] = 
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	VkPipelineDynamicStateCreateInfo dynamicState = {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = 2;
	dynamicState.pDynamicStates = dynamicStates;
}

void VulkanPipeline::CreateLayout(VulkanDevice* Device)
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = 0; // Optional

	if (vkCreatePipelineLayout(Device->GetDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

void VulkanPipeline::CreateRenderPass(VulkanDevice* Device, VulkanSwapChain* SwapChain)
{
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = SwapChain->GetImageFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(Device->GetDevice(), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create render pass!");
	}
}

void VulkanPipeline::CreateGraphicsPipeline(VulkanDevice* Device)
{
	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = (uint32_t)m_ShaderStages.size();
	pipelineInfo.pStages = m_ShaderStages.data();
	pipelineInfo.pVertexInputState = &m_VertexInputState;
	pipelineInfo.pInputAssemblyState = &m_InputAssemblyState;
	pipelineInfo.pViewportState = &m_ViewportState;
	pipelineInfo.pRasterizationState = &m_RasterizationState;
	pipelineInfo.pMultisampleState = &m_MultisampleState;
	pipelineInfo.pDepthStencilState = nullptr; // Optional
	pipelineInfo.pColorBlendState = &m_ColorBlendState;
	pipelineInfo.pDynamicState = nullptr; // Optional
	pipelineInfo.layout = m_PipelineLayout;
	pipelineInfo.renderPass = m_RenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	if (vkCreateGraphicsPipelines(Device->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	for (int32_t i = 0; i < m_ShaderStages.size(); ++i)
	{
		vkDestroyShaderModule(Device->GetDevice(), m_ShaderStages[i].module, nullptr);
	}
}

void VulkanPipeline::BindShader(const VkShaderStageFlagBits ShaderStageFlag, VulkanShaderModule* ShaderModule, const char* EntryPointName)
{
	VkPipelineShaderStageCreateInfo shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.stage = ShaderStageFlag;
	shaderStageInfo.module = ShaderModule->GetShaderModule();
	shaderStageInfo.pName = EntryPointName;

	m_ShaderStages.push_back(shaderStageInfo);
}