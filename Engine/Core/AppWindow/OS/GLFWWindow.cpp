#include "stdafx.h"
#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(int Width, int Height)
	: GenericWindow(Width, Height)
{
}

GLFWWindow::~GLFWWindow()
{
}

void GLFWWindow::CreateWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);
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

void GLFWWindow::OnWindowResized(GLFWwindow* Window, int Width, int Height)
{
	GLFWWindow* app = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(Window));
	app->m_Width = Width;
	app->m_Height = Height;
	app->m_cbWindowResized(Width, Height);
}

void* GLFWWindow::GetHandle()
{
	return m_Window;
}

bool GLFWWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(m_Window) > 0;
}