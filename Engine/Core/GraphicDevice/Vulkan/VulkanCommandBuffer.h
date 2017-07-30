#pragma once

class VulkanDevice;
class VulkanFrameBuffer;
class VulkanCommandPool;
class VulkanCommandBuffer
{
public:
	VulkanCommandBuffer();
	virtual ~VulkanCommandBuffer();

public:
	void CreateCommandBuffer(VulkanDevice* Device, VulkanFrameBuffer* FrameBuffer, VulkanCommandPool* CommandPool);
	void Destroy();

	std::vector<VkCommandBuffer> GetCommandBuffers() { return m_CommandBuffers; }

private:
	std::vector<VkCommandBuffer> m_CommandBuffers;
};