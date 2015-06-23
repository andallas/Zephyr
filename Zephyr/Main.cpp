#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void ShaderCompileCheck(GLuint shader, std::string type);
void ShaderLinkCheck(GLuint shaderProgram);

const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout(location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n";

const GLchar* fragmentShaderSource = "#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n";

int main()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		std::cerr << "ERROR: GLFW failed to initialize!" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X compatibility
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Zephyr", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cerr << "ERROR: Failed to initialize GLEW - " << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// Set callback functions
	glfwSetKeyCallback(window, KeyCallback);

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Vertex Shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	ShaderCompileCheck(vertexShader, "VERTEX");

	// Fragment Shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	ShaderCompileCheck(fragmentShader, "FRAGMENT");

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	ShaderLinkCheck(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertex data and buffer objects
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
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

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void ErrorCallback(int error, const char* description)
{
	std::cerr << "ERROR: " << error << " - " << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void ShaderCompileCheck(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::" << type.c_str() << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderLinkCheck(GLuint shaderProgram)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}
