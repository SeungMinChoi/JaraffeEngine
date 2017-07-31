#include "stdafx.h"

#include "Core/HAL/AppWindow/OS/GLFWWindow.h"
#include "Core/RHI/Vulkan/VulkanDynamicRHI.h"

class TestApp
{
public:
	void Init()
	{
		m_Window = new GLFWWindow(ENGINE_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
        m_DynamicRHI = new VulkanDynamicRHI();

		m_Window->CreateWindow();
        m_DynamicRHI->Init(m_Window->GetHandle());

		m_Window->SetCallBackWindowResized(std::bind(std::mem_fn(&TestApp::WindowResize), this, std::placeholders::_1, std::placeholders::_2));
	}

	void Destroy()
	{
        m_DynamicRHI->Destroy();
		m_Window->CloseWindow();
	}

	void Run()
	{
		while (m_Window->WindowShouldClose() == false)
		{
			glfwPollEvents();
            m_DynamicRHI->Draw();
		}
	}

	void WindowResize(int32_t Width, int32_t Height)
	{
        m_DynamicRHI->Resize();
	}

public:
	GenericWindow* m_Window = nullptr;
	DynamicRHI* m_DynamicRHI = nullptr;
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