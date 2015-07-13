#ifndef CONTEXT_H
#define CONTEXT_H

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "Window.h"

class Context
{
public:
	Context(GLuint width, GLuint height);
	~Context();
	void PreInitialization();
	void PostInitialization(GLFWwindow* window);
	static void ErrorCallback(int error, const char* description);

private:
	int _errorCode;
	int _width;
	int _height;
};

#endif