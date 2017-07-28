#include "stdafx.h"
#include "GenericWindow.h"

GenericWindow::GenericWindow(std::string WindowName, int32_t Width, int32_t Height)
	: m_WindowName(WindowName)
	, m_Width(Width)
	, m_Height(Height)
{
}

GenericWindow::~GenericWindow()
{
}

void GenericWindow::GetWindowSize(int32_t& OutWidth, int32_t& OutHeight)
{
	OutWidth = m_Width;
	OutHeight = m_Height;
}

void GenericWindow::SetCallBackWindowResized(WindowResizeCallBack Callback)
{
	m_cbWindowResized = Callback;
}