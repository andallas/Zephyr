#ifndef INPUT_H
#define INPUT_H

#include "Clock.h"

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>


class Input
{
public:
	static Input& Instance();
	static void Destroy();
	void Initialize(GLFWwindow* window);
	void Update();
	unsigned int GetKey(GLuint keyCode);
	bool GetKeyPressed(GLuint keyCode);
	bool GetKeyReleased(GLuint keyCode);
	bool GetKeyDown(GLuint keyCode);
	bool GetKeyHeld(GLuint keyCode);
	bool GetKeyUp(GLuint keyCode);

	static GLfloat GetMouseXOffset();
	static GLfloat GetMouseYOffset();
	static GLfloat GetScrollXOffset();
	static GLfloat GetScrollYOffset();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	static bool isInverted;
	static GLfloat mouseSensitivity;
	static GLfloat scrollSensitivity;

private:
	Input();
	virtual ~Input();

	static const GLuint _ARRAY_SIZE = 1024;
	static unsigned int _currentKeys[];
	static unsigned int _previousKeys[];
	static GLfloat _lastMouseX;
	static GLfloat _lastMouseY;
	static bool _isFirstMouse;
	static GLfloat _mouseXOffset;
	static GLfloat _mouseYOffset;
	static GLfloat _scrollXOffset;
	static GLfloat _scrollYOffset;
};

#endif