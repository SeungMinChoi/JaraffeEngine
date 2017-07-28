#include "stdafx.h"

#include "Core/AppWindow/OS/GLFWWindow.h"
#include "Core/GraphicDevice/Vulkan/VulkanDevice.h"

class TestApp
{
public:
	void Init()
	{
		m_Window = new GLFWWindow(ENGINE_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
		m_GraphicDevice = new VulkanDevice();

		m_Window->CreateWindow();
		m_GraphicDevice->Init(m_Window->GetHandle());
	}

	void Destroy()
	{
		m_GraphicDevice->Destroy();
		m_Window->CloseWindow();
	}

	void Run()
	{
		while (m_Window->WindowShouldClose() == false)
		{
			break;
		}
	}

public:
	GenericWindow* m_Window = nullptr;
	GenericGraphicDevice* m_GraphicDevice = nullptr;
};

int32_t main() 
{
	TestApp app;

	try
	{
		app.Init();
		app.Run();
		app.Destroy();
	}
	catch (const std::runtime_error& e) 
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}