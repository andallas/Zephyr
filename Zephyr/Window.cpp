#include "Window.h"


Window::Window(GLuint width, GLuint height, char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	_width = width;
	_height = height;
	_title = title;
	_monitor = monitor;
	_share = share;
}

Window::~Window()
{
}

void Window::Initialize()
{
	_window = glfwCreateWindow(_width, _height, _title, _monitor, _share);
}

GLFWwindow* Window::GetWindow()
{
	return _window;
}