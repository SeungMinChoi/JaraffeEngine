#pragma once

struct GLFWwindow;

class GLFWWindow : public GenericWindow
{
public:
	GLFWWindow(std::string WindowName, int32_t Width, int32_t Height);
	virtual ~GLFWWindow();

public:
	virtual void CreateWindow() override;
	virtual void CloseWindow() override;

	virtual void* GetHandle() override;
	virtual bool WindowShouldClose() override;

public:
	virtual void SetCallBackWindowResized(WindowResizeCallBack Callback) override;

protected:
	static void OnWindowResized(GLFWwindow* Window, int32_t Width, int32_t Height);

private:
	GLFWwindow* m_Window;
};