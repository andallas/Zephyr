#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Initialization();
GLuint LoadTexture(std::string texturePath);
std::string BaseDirectory();
std::string ShaderDirectory();
std::string ImageDirectory();
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void DoMovement();
void CalculateTime();

bool wireframeMode = false;
int exitCode = 0;
GLFWwindow* window;

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
	Shader defaultShader((ShaderDirectory() + "default.vert").c_str(), (ShaderDirectory() + "default.frag").c_str());
	Shader lampShader((ShaderDirectory() + "lamp.vert").c_str(), (ShaderDirectory() + "lamp.frag").c_str());

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
	while (!glfwWindowShouldClose(window))
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
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return exitCode;
}

void Initialization()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		std::cerr << "ERROR::MAIN::MAIN::GLFW_INIT_FAILED\n" << std::endl;
		exitCode = -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X compatibility
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Zephyr", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "ERROR::MAIN::MAIN::CREATE_WINDOW_FAILED\n" << std::endl;
		glfwTerminate();
		exitCode = -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cerr << "ERROR::MAIN::MAIN::GLEW_INIT_FAILED\n" << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		exitCode = -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Depth testing
	glEnable(GL_DEPTH_TEST);

	// Set callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

GLuint LoadTexture(std::string texturePath)
{
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

std::string BaseDirectory()
{
	char full[_MAX_PATH];
	if (_fullpath(full, ".\\", _MAX_PATH) != NULL)
	{
		return full;
	}

	std::cerr << "ERROR::MAIN::BASE_DIRECTORY::INVALID_PATH\n" << std::endl;

	return "";
}

std::string ShaderDirectory()
{
	return (BaseDirectory() + "Resources\\Shaders\\");
}

std::string ImageDirectory()
{
	return (BaseDirectory() + "Resources\\Images\\");
}

void ErrorCallback(int error, const char* description)
{
	std::cerr << "ERROR::GLFW_ERROR\n " << error << " - " << description << std::endl;
	exitCode = -1;
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
		lastMouseX = xPos;
		lastMouseY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastMouseX;
	GLfloat yOffset = yPos - lastMouseY;
	lastMouseX = xPos;
	lastMouseY = yPos;

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
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (aspect >= 1.0f && aspect <= 45.0f)
		aspect -= yOffset;
	if (aspect <= 1.0f)
		aspect = 1.0f;
	if (aspect >= 45.0f)
		aspect = 45.0f;
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
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}