#include "Input.h"

bool Input::isInverted = false;
GLfloat Input::mouseSensitivity = 0.05f;
GLfloat Input::scrollSensitivity = 1.0f;

unsigned int Input::_currentKeys[_ARRAY_SIZE];
unsigned int Input::_previousKeys[_ARRAY_SIZE];
GLfloat Input::_lastMouseX = 400;
GLfloat Input::_lastMouseY = 300;
bool Input::_isFirstMouse = true;
GLfloat Input::_mouseXOffset = 0.0f;
GLfloat Input::_mouseYOffset = 0.0f;
GLfloat Input::_scrollXOffset = 0.0f;
GLfloat Input::_scrollYOffset = 0.0f;


Input::Input()
{
}

Input::~Input()
{
}

Input& Input::Instance()
{
	static Input* instance = NULL;
	if (instance == NULL)
	{
		instance = new Input();
	}

	return *instance;
}

void Input::Destroy()
{
	Input* input = &Instance();
	delete input;
}

void Input::Initialize(GLFWwindow* window)
{
	for (int i = 0; i < _ARRAY_SIZE; i++)
	{
		_previousKeys[i] = false;
		_currentKeys[i] = false;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
}

void Input::Update()
{
	for (int i = 0; i < _ARRAY_SIZE; i++)
	{
		_previousKeys[i] = _currentKeys[i];
	}

	glfwPollEvents();
}

unsigned int Input::GetKey(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode];
	}
	return false;
}

bool Input::GetKeyHeld(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode] != 0 && _previousKeys[keyCode] != 0;
	}
	return 0;
}

bool Input::GetKeyPressed(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode] == 1 && _previousKeys[keyCode] == 0;
	}
	return 0;
}

bool Input::GetKeyReleased(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode] == 0 && _previousKeys[keyCode] != 0;
	}
	return 0;
}

bool Input::GetKeyUp(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode] == 0 && _previousKeys[keyCode] == 0;
	}
	return 0;
}

bool Input::GetKeyDown(GLuint keyCode)
{
	if (keyCode >= 0 && keyCode < _ARRAY_SIZE)
	{
		return _currentKeys[keyCode] == 1 || _currentKeys[keyCode] == 2;
	}
	return 0;
}

GLfloat Input::GetMouseXOffset()
{
	GLfloat temp = _mouseXOffset;
	_mouseXOffset = 0.0f;
	return temp;
}

GLfloat Input::GetMouseYOffset()
{
	GLfloat temp = _mouseYOffset;
	_mouseYOffset = 0.0f;
	return temp;
}

GLfloat Input::GetScrollXOffset()
{
	GLfloat temp = _scrollXOffset;
	_scrollXOffset = 0.0f;
	return temp;
}

GLfloat Input::GetScrollYOffset()
{
	GLfloat temp = _scrollYOffset;
	_scrollYOffset = 0.0f;
	return temp;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		_currentKeys[key] = 1;
	}
	else if (action == GLFW_REPEAT)
	{
		_currentKeys[key] = 2;
		_previousKeys[key] = 2;
	}
	else if (action == GLFW_RELEASE)
	{
		_currentKeys[key] = 0;
	}
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
