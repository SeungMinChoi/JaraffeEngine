#pragma once

class VulkanDevice;
class VulkanPipeline;
class VulkanSwapChain;
class VulkanFrameBuffer
{
public:
	VulkanFrameBuffer();
	virtual ~VulkanFrameBuffer();

public:
	void CreateFramebuffers(VulkanDevice* Device, VulkanSwapChain* SwapChain, VulkanPipeline* Pipeline);
	void Destroy(VulkanDevice* Device);

	std::vector<VkFramebuffer> GetFrameBuffers() { return m_Framebuffers; }

private:
	std::vector<VkFramebuffer> m_Framebuffers;
};