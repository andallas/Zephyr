#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
	Window(GLuint width, GLuint height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~Window();

	void Window::Initialize();
	GLFWwindow* CurrentWindow();

private:
	GLFWwindow* _window;
	GLuint _width;
	GLuint _height;
	char* _title;
	GLFWmonitor* _monitor;
	GLFWwindow* _share;
};

#endif