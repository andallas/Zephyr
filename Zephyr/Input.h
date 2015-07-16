#ifndef INPUT_H
#define INPUT_H

#include "Clock.h"

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input
{
public:
	Input();
	~Input();
	void Initialize(GLFWwindow* window);
	bool GetKey(GLuint keyCode);

	static GLfloat GetMouseXOffset();
	static GLfloat GetMouseYOffset();
	static GLfloat GetScrollXOffset();
	static GLfloat GetScrollYOffset();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	static bool isInverted;
	static bool isWireframeMode;
	static GLfloat mouseSensitivity;
	static GLfloat scrollSensitivity;

private:
	static const GLuint _ARRAY_SIZE = 1024;
	static bool _keys[];
	static GLfloat _lastMouseX;
	static GLfloat _lastMouseY;
	static bool _isFirstMouse;
	static GLfloat _mouseXOffset;
	static GLfloat _mouseYOffset;
	static GLfloat _scrollXOffset;
	static GLfloat _scrollYOffset;
};

#endif