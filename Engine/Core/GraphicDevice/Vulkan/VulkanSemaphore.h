#pragma once

class VulkanDevice;
class VulkanSemaphore
{
public:
	VulkanSemaphore();
	virtual ~VulkanSemaphore();

public:
	void CreateSemaphore(VulkanDevice* Device);
	void Destroy(VulkanDevice* Device);

	VkSemaphore GetSemaphore() { return m_Semaphore; }

private:
	VkSemaphore m_Semaphore;
};