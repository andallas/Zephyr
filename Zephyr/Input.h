#ifndef INPUT_H
#define INPUT_H

#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input
{
public:
	Input();
	~Input();
	void Initialize();
	void DoMovement();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	static bool Keys[];
	static GLfloat LastMouseX;
	static GLfloat LastMouseY;
	static GLfloat Yaw;
	static GLfloat Pitch;
	static bool FirstMouse;
	static bool Inverted;
	static bool WireframeMode;
private:
	
};

#endif