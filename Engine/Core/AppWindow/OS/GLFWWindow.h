#pragma once

struct GLFWwindow;

class GLFWWindow : public GenericWindow
{
public:
	GLFWWindow(int Width, int Height);
	virtual ~GLFWWindow();

public:
	virtual void CreateWindow() override;
	virtual void CloseWindow() override;

	virtual void* GetHandle() override;
	virtual bool WindowShouldClose() override;

public:
	virtual void SetCallBackWindowResized(WindowResizeCallBack Callback) override;

protected:
	static void OnWindowResized(GLFWwindow* Window, int Width, int Height);

private:
	GLFWwindow* m_Window;
};