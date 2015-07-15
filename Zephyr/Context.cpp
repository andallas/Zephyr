#include "Context.h"


Context::Context(GLuint width, GLuint height)
{
	_width = width;
	_height = height;
}

Context::~Context()
{
}

void Context::PreInitialization()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		std::cerr << "ERROR::MAIN::MAIN::GLFW_INIT_FAILED\n" << std::endl;
		ErrorCode = -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X compatibility
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Context::PostInitialization(GLFWwindow* window)
{
	if (window == nullptr)
	{
		std::cerr << "ERROR::MAIN::MAIN::CREATE_WINDOW_FAILED\n" << std::endl;
		glfwTerminate();
		ErrorCode = -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cerr << "ERROR::MAIN::MAIN::GLEW_INIT_FAILED\n" << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		ErrorCode = -1;
	}

	glViewport(0, 0, _width, _height);

	// Depth testing
	glEnable(GL_DEPTH_TEST);

	// Set clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Context::ErrorCallback(int error, const char* description)
{
	std::cerr << "ERROR::GLFW_ERROR\n " << error << " - " << description << std::endl;
	ErrorCode = -1;
}
