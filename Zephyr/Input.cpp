#include "Input.h"

bool Input::isInverted = false;
bool Input::isWireframeMode = false;
GLfloat Input::mouseSensitivity = 0.05f;
GLfloat Input::scrollSensitivity = 1.0f;

bool Input::_keys[_ARRAY_SIZE];
GLfloat Input::_lastMouseX = 400;
GLfloat Input::_lastMouseY = 300;
bool Input::_isFirstMouse = true;


Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialize(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
}

bool Input::GetKey(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _keys[keyCode];
	}
	else
	{
		return false;
	}
}

GLfloat Input::GetMouseXOffset()
{
	return _mouseXOffset;
}

GLfloat Input::GetMouseYOffset()
{
	return _mouseYOffset;
}

GLfloat Input::GetScrollXOffset()
{
	return _scrollXOffset;
}

GLfloat Input::GetScrollYOffset()
{
	return _scrollYOffset;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		_keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		_keys[key] = false;
	}

	// TODO: Application specific code
	/*
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		WireframeMode = !WireframeMode;
		if (WireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	*/
}

void Input::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (_isFirstMouse)
	{
		_lastMouseX = (GLfloat)xPos;
		_lastMouseY = (GLfloat)yPos;
		_isFirstMouse = false;
	}

	_mouseXOffset = (GLfloat)(xPos - _lastMouseX);
	_mouseYOffset = (GLfloat)(yPos - _lastMouseY);
	_lastMouseX = (GLfloat)xPos;
	_lastMouseY = (GLfloat)yPos;

	_mouseXOffset *= mouseSensitivity;
	_mouseYOffset *= mouseSensitivity;
}

void Input::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	_scrollXOffset = (GLfloat)xOffset * scrollSensitivity;
	_scrollYOffset = (GLfloat)yOffset * scrollSensitivity;
}
