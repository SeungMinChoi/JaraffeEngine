#pragma once

class GenericWindow
{
public:
	GenericWindow(int Width, int Height);
	virtual ~GenericWindow();

public:
	using WindowResizeCallBack = std::function<void(int, int)>;

public:
	virtual void CreateWindow() = 0;
	virtual void CloseWindow() = 0;
	
	virtual void* GetHandle() = 0;
	virtual bool WindowShouldClose() = 0;

public:
	virtual void GetWindowSize(int& OutWidth, int& OutHeight);

	virtual void SetCallBackWindowResized(WindowResizeCallBack Callback);

protected:
	int m_Width;
	int m_Height;

	WindowResizeCallBack m_cbWindowResized = nullptr;
};