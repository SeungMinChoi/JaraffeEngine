#pragma once

// TODO : ���� Device �ʿ��� ������ �������� �ƴϸ� Device �� ������ ���� Ŭ������ ���� ������ ��� �ؾ���.

class VulkanDevice : public GenericGraphicDevice
{
public:
	VulkanDevice();
	virtual ~VulkanDevice();

public:
	virtual void Init(void* WindowHandle) override;
	virtual void Draw() override;
	virtual void Destroy() override;
	
	virtual void Resize() override;

public:
	VkDevice& GetDevice();

private:
	void CreateInstance();
	void CreateSurface(void* WindowHandle);
	void CreatePhysicalDevice();
	void CreateDevice();
	void CreateSwapChain();
	void CreateDefalutPipeline();	// TODO : TEST ��
	void CreateFrameBuffer();
	void CreateCommandPool();
	void CreateCommandBuffer();
	void CreateSemaphore();

	void DestroySwapChain();
	void DestroyDevice();
	void DestroyPhysicalDevice();
	void DestroySurface();
	void DestroyInstance();
	void DestroyPipeline();
	void DestroyFrameBuffer();
	void DestroyCommandPool();
	void DestroyCommandBuffer();
	void DestroySemaphore();

	void ReCreateSwapChain();
	void CleanupSwapChain();

private:
	VkDevice m_Device;

	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;

	class VulkanSurface* m_Surface;
	class VulkanInstance* m_Instance;
	class VulkanPipeline* m_Pipeline;
	class VulkanSwapChain* m_SwapChain;
	class VulkanCommandPool* m_CommandPool;
	class VulkanFrameBuffer* m_FrameBuffer;
	class VulkanCommandBuffer* m_CommandBuffer;
	class VulkanPhysicalDevice* m_PhysicalDevice;
	class VulkanSemaphore* m_ImageAvailableSemaphore;
	class VulkanSemaphore* m_RenderFinishedSemaphore;
};