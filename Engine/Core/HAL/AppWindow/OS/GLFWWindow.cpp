#include "stdafx.h"
#include "GLFWWindow.h"

GLFWWindow::GLFWWindow(std::string WindowName, int32_t Width, int32_t Height)
	: GenericWindow(WindowName, Width, Height)
{
}

GLFWWindow::~GLFWWindow()
{
}

void GLFWWindow::CreateWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
}

void GLFWWindow::CloseWindow()
{
	glfwDestroyWindow(m_Window);

	glfwTerminate();
}

void GLFWWindow::SetCallBackWindowResized(WindowResizeCallBack Callback)
{
	GenericWindow::SetCallBackWindowResized(Callback);
	
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, OnWindowResized);
}

void GLFWWindow::OnWindowResized(GLFWwindow* Window, int32_t Width, int32_t Height)
{
	GLFWWindow* m_Window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(Window));
	m_Window->m_Width = Width;
	m_Window->m_Height = Height;
	m_Window->m_cbWindowResized(Width, Height);
}

void* GLFWWindow::GetHandle()
{
	return m_Window;
}

bool GLFWWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(m_Window) > 0;
}