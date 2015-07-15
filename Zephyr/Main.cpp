#include "MemoryLeakDetector.h"
#include "Context.h"
#include "Window.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "Utility.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Initialization();
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void DoMovement();
void CalculateTime();

bool wireframeMode = false;
int exitCode = 0;
Window* window;
Context* context;

const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat aspect = 45.0f;

// Input
bool keys[11024];
GLfloat lastMouseX = 400;
GLfloat lastMouseY = 300;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
bool firstMouse = true;
bool inverted = false;

// Clock
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Light source
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	Initialization();

	if (exitCode != 0)
	{
		glfwTerminate();
		return exitCode;
	}

	// Build and compile shaders
	Shader defaultShader((Utility::ShaderDirectory() + "default.vert").c_str(), (Utility::ShaderDirectory() + "default.frag").c_str());
	Shader lampShader((Utility::ShaderDirectory() + "lamp.vert").c_str(), (Utility::ShaderDirectory() + "lamp.frag").c_str());

	// Vertex data and buffer objects
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Game Loop
	while (!glfwWindowShouldClose(window->CurrentWindow()))
	{
		// Check and call events
		glfwPollEvents();
		DoMovement();
		CalculateTime();

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Lighting uniforms
		defaultShader.Use();
		GLint objectColorLocation = glGetUniformLocation(defaultShader.program, "objectColor");
		GLint lightColorLocation = glGetUniformLocation(defaultShader.program, "lightColor");
		glUniform3f(objectColorLocation, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

		// Create matrices
		glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(aspect), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		// Matrix uniforms
		GLint modelLocation = glGetUniformLocation(defaultShader.program, "model");
		GLint viewLocation = glGetUniformLocation(defaultShader.program, "view");
		GLint projectionLocation = glGetUniformLocation(defaultShader.program, "projection");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		// Draw the container
		glBindVertexArray(VAO);
		glm::mat4 modelMatrix;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);



		lampShader.Use();
		modelLocation = glGetUniformLocation(lampShader.program, "model");
		viewLocation = glGetUniformLocation(lampShader.program, "view");
		projectionLocation = glGetUniformLocation(lampShader.program, "projection");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, lightPos);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		// Draw the lamp
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap buffers
		glfwSwapBuffers(window->CurrentWindow());
	}

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	delete context;
	delete window;
	glfwTerminate();

#ifdef _DEBUG
	std::cout << CurrentMemoryUsage() << std::endl;
	DumpUnfreed();
#endif
	return exitCode;
}

void Initialization()
{
	context = new Context(WIDTH, HEIGHT);
	window = new Window(WIDTH, HEIGHT, "Zephyr", nullptr, nullptr);

	context->PreInitialization();
	window->Initialize();
	context->PostInitialization(window->CurrentWindow());

	// TODO: Move to input class
	glfwSetInputMode(window->CurrentWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set callback functions
	glfwSetKeyCallback(window->CurrentWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->CurrentWindow(), MouseCallback);
	glfwSetScrollCallback(window->CurrentWindow(), ScrollCallback);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		wireframeMode = !wireframeMode;
		if (wireframeMode)
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
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastMouseX = (GLfloat)xPos;
		lastMouseY = (GLfloat)yPos;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat)(xPos - lastMouseX);
	GLfloat yOffset = (GLfloat)(yPos - lastMouseY);
	lastMouseX = (GLfloat)xPos;
	lastMouseY = (GLfloat)yPos;

	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians((inverted) ? pitch : -pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians((inverted) ? pitch : -pitch));
	front.z = cos(glm::radians((inverted) ? pitch : -pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
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

void DoMovement()
{
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (keys[GLFW_KEY_S])
	{
		cameraPos -= cameraSpeed * cameraFront;
	}

	if (keys[GLFW_KEY_A])
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (keys[GLFW_KEY_D])
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void CalculateTime()
{
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}