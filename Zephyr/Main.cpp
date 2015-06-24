#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>

void Initialization();
GLuint LoadTexture(std::string texturePath);
std::string BaseDirectory();
std::string ShaderDirectory();
std::string ImageDirectory();
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

bool wireframeMode = false;
int exitCode = 0;
GLFWwindow* window;

int main()
{
	Initialization();

	if (exitCode != 0)
	{
		glfwTerminate();
		return exitCode;
	}

	// Build and compile shaders
	Shader shader((ShaderDirectory() + "default.vert").c_str(), (ShaderDirectory() + "default.frag").c_str());

	// Vertex data and buffer objects
	GLfloat vertices[] =
	{
		// Inverted Y coordinates for Textures to fix inverted Y bug on image load
		// Positions           // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// Top Right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		// Bottom Right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		// Bottom Left
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f		// Top Left 
	};

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	GLuint IBO, VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &IBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);


	// Texture loading
	GLuint texture0 = LoadTexture((ImageDirectory() + "container.jpg"));
	GLuint texture1 = LoadTexture((ImageDirectory() + "awesomeface.png"));
	

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glUniform1i(glGetUniformLocation(shader.program, "ourTexture0"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.program, "ourTexture1"), 1);

		shader.Use();
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (sizeof(indices) / sizeof(*indices)), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
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

	window = glfwCreateWindow(800, 600, "Zephyr", nullptr, nullptr);
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

	glViewport(0, 0, 800, 600);

	// Set callback functions
	glfwSetKeyCallback(window, KeyCallback);

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
}
