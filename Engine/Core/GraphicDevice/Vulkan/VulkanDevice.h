#pragma once

// TODO : ���� Device �ʿ��� ������ �������� �ƴϸ� Device �� ������ ���� Ŭ������ ���� ������ ��� �ؾ���.

class VulkanDevice : public GenericGraphicDevice
{
public:
	VulkanDevice();
	virtual ~VulkanDevice();

public:
	virtual void Init(void* WindowHandle) override;
	virtual void Destroy() override;

public:
	VkDevice& GetDevice();

private:
	void CreateInstance();
	void CreateSurface(void* WindowHandle);
	void CreatePhysicalDevice();
	void CreateDevice();
	void CreateSwapChain();

	void DestroySwapChain();
	void DestroyDevice();
	void DestroyPhysicalDevice();
	void DestroySurface();
	void DestroyInstance();

private:
	VkDevice m_Device;

	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;

	class VulkanSurface* m_Surface;
	class VulkanInstance* m_Instance;
	class VulkanSwapChain* m_SwapChain;
	class VulkanPhysicalDevice* m_PhysicalDevice;
};