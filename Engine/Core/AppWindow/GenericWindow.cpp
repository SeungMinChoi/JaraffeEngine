#include "stdafx.h"
#include "GenericWindow.h"

GenericWindow::GenericWindow(int Width, int Height)
	: m_Width(Width)
	, m_Height(Height)
{
}

GenericWindow::~GenericWindow()
{
}

void GenericWindow::GetWindowSize(int& OutWidth, int& OutHeight)
{
	OutWidth = m_Width;
	OutHeight = m_Height;
}

void GenericWindow::SetCallBackWindowResized(WindowResizeCallBack Callback)
{
	m_cbWindowResized = Callback;
}