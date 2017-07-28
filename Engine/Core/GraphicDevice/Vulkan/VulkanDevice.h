#pragma once

// TODO : 이후 Device 쪽에서 모든것을 관리할지 아니면 Device 도 나누고 관리 클래스를 새로 만들지 고민 해야함.

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