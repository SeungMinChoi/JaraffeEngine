#pragma once

class GenericWindow
{
public:
	GenericWindow(std::string WindowName, int32_t Width, int32_t Height);
	virtual ~GenericWindow();

public:
	using WindowResizeCallBack = std::function<void(int32_t, int32_t)>;

public:
	virtual void CreateWindow() = 0;
	virtual void CloseWindow() = 0;
	
	virtual void* GetHandle() = 0;
	virtual bool WindowShouldClose() = 0;

public:
	virtual void GetWindowSize(int32_t& OutWidth, int32_t& OutHeight);

	virtual void SetCallBackWindowResized(WindowResizeCallBack Callback);

protected:
	int32_t m_Width;
	int32_t m_Height;
	std::string m_WindowName;

	WindowResizeCallBack m_cbWindowResized = nullptr;
};