#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

void errorCallback(int error, const char* description);

int main()
{
	glfwSetErrorCallback(errorCallback);

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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	return 0;
}
void errorCallback(int error, const char* description)
{
	std::cerr << "ERROR: " << error << " - " << description << std::endl;
}
