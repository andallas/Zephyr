#include "GameManager.h"


GLuint GameManager::_width = 800;
GLuint GameManager::_height = 600;
char* GameManager::_title = "Zephyr";

GameManager::~GameManager()
{
	delete _input;
	delete _window;
	delete _context;
}

GameManager& GameManager::Instance()
{
	static GameManager* instance = NULL;
	if (instance == NULL)
	{
		Initialization();
		instance = new GameManager();
	}

	return *instance;
}

void GameManager::Initialization()
{
	_context = new Context(_width, _height);
	_window = new Window(_width, _height, _title, nullptr, nullptr);
	_input = new Input();

	_context->PreInitialization();
	_window->Initialize();
	_context->PostInitialization(_window->GetWindow());

	_input->Initialize(_window->GetWindow());
}

void GameManager::Run()
{
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	if (Context::ErrorCode != 0)
	{
		glfwTerminate();
		return;
	}

	// Build and compile shaders
	Shader defaultShader((Utility::ShaderDirectory() + "default.vert").c_str(), (Utility::ShaderDirectory() + "default.frag").c_str());
	Shader lampShader((Utility::ShaderDirectory() + "lamp.vert").c_str(), (Utility::ShaderDirectory() + "lamp.frag").c_str());

	// Vertex data and buffer objects
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f
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

	while (!glfwWindowShouldClose(GameManager::Instance().CurrentWindow()->GetWindow()))
	{
		// Check and call events
		glfwPollEvents();
		Clock::CalculateTime();
		_camera->MoveCamera();
		_camera->RotateCamera();
		_camera->ZoomCamera();

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Lighting uniforms
		defaultShader.Use();
		GLint objectColorLocation = glGetUniformLocation(defaultShader.program, "objectColor");
		GLint lightColorLocation = glGetUniformLocation(defaultShader.program, "lightColor");
		glUniform3f(objectColorLocation, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);

		// Create matrices
		glm::vec3 cameraPos = _camera->GetPosition();
		glm::vec3 cameraFront = _camera->GetFront();
		glm::vec3 cameraUp = _camera->GetUp();

		glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projectionMatrix = glm::perspective(	glm::radians(_camera->GetAspectRatio()),
														(GLfloat)GameManager::Instance().GetWidth() / (GLfloat)GameManager::Instance().GetHeight(),
														_camera->GetNearPlane(),
														_camera->GetFarPlane());

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
		glfwSwapBuffers(GameManager::Instance().CurrentWindow()->GetWindow());
	}

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void GameManager::Destroy()
{
	glfwDestroyWindow(_window->GetWindow());
	glfwTerminate();
	GameManager* gameManager = &Instance();
	delete gameManager;
}

Window* GameManager::CurrentWindow()
{
	return _window;
}

Input* GameManager::GetInput()
{
	return _input;
}

GLuint GameManager::GetWidth()
{
	return _width;
}

GLuint GameManager::GetHeight()
{
	return _height;
}
