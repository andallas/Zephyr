#include "Input.h"

bool Input::Keys[1024];
GLfloat Input::LastMouseX = 400;
GLfloat Input::LastMouseY = 300;
GLfloat Input::Yaw = -90.0f;
GLfloat Input::Pitch = 0.0f;
bool Input::FirstMouse = true;
bool Input::Inverted = false;
bool Input::WireframeMode = false;


Input::Input()
{
}


Input::~Input()
{
}

void Input::Initialize()
{
	// TODO: Move to input class
	glfwSetInputMode(window->CurrentWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// TODO: Move to input class
	// Set callback functions
	glfwSetKeyCallback(window->CurrentWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->CurrentWindow(), MouseCallback);
	glfwSetScrollCallback(window->CurrentWindow(), ScrollCallback);
}

void Input::DoMovement()
{
	GLfloat cameraSpeed = 5.0f * deltaTime;

	if (Keys[GLFW_KEY_W])
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (Keys[GLFW_KEY_S])
	{
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (Keys[GLFW_KEY_A])
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (Keys[GLFW_KEY_D])
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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

	if (action == GLFW_PRESS)
	{
		Keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		Keys[key] = false;
	}
}

void Input::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (FirstMouse)
	{
		LastMouseX = (GLfloat)xPos;
		LastMouseY = (GLfloat)yPos;
		FirstMouse = false;
	}

	GLfloat xOffset = (GLfloat)(xPos - LastMouseX);
	GLfloat yOffset = (GLfloat)(yPos - LastMouseY);
	LastMouseX = (GLfloat)xPos;
	LastMouseY = (GLfloat)yPos;

	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;

	if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians((Inverted) ? Pitch : -Pitch)) * cos(glm::radians(Yaw));
	front.y = sin(glm::radians((Inverted) ? Pitch : -Pitch));
	front.z = cos(glm::radians((Inverted) ? Pitch : -Pitch)) * sin(glm::radians(Yaw));
	cameraFront = glm::normalize(front);
}

void Input::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (aspect >= 1.0f && aspect <= 45.0f)
	{
		aspect -= (GLfloat)yOffset;
	}
	if (aspect <= 1.0f)
	{
		aspect = 1.0f;
	}
	if (aspect >= 45.0f)
	{
		aspect = 45.0f;
	}
}
