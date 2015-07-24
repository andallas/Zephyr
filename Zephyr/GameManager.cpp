#include "GameManager.h"


Window* GameManager::_window;
Context* GameManager::_context;
Input* GameManager::_input;
Camera* GameManager::_camera;
Clock* GameManager::_clock;

GLuint GameManager::_width = 800;
GLuint GameManager::_height = 600;
char* GameManager::_title = "Zephyr";

GameManager::~GameManager()
{
	delete _input;
	delete _window;
	delete _context;
	delete _camera;
	delete _clock;
}

GameManager& GameManager::Instance()
{
	static GameManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return *instance;
}

void GameManager::Initialization()
{
	_context = new Context(_width, _height);
	_window = new Window(_width, _height, _title, nullptr, nullptr);
	_input = new Input();
	_camera = new Camera();
	_clock = new Clock();

	_context->PreInitialization();
	_window->Initialize();
	_context->PostInitialization(GameManager::Instance().CurrentWindow()->GetWindow());

	_input->Initialize(GameManager::Instance().CurrentWindow()->GetWindow());
}

void GameManager::Run()
{
	if (Context::ErrorCode != 0)
	{
		glfwTerminate();
		return;
	}

	// Build and compile shaders
	Shader defaultShader((Utility::ShaderDirectory() + "default.vert").c_str(), (Utility::ShaderDirectory() + "default.frag").c_str());
	Shader lampShader((Utility::ShaderDirectory() + "lamp.vert").c_str(), (Utility::ShaderDirectory() + "lamp.frag").c_str());

	// Load Textures
	GLuint containerDiffuse = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container.png", GL_SRGB);
	GLuint containerSpecular = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container_specular.png", GL_RGB);
	GLuint containerEmission = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container_emission.png", GL_RGB);
	/*GLuint floorDiffuse = TextureLoader::LoadTexture(Utility::ImageDirectory() + "floor.png", GL_SRGB);
	GLuint floorSpecular = TextureLoader::LoadTexture(Utility::ImageDirectory() + "floor_specular.png", GL_RGB);
	GLuint wallDiffuse = TextureLoader::LoadTexture(Utility::ImageDirectory() + "wall.png", GL_SRGB);
	GLuint wallSpecular = TextureLoader::LoadTexture(Utility::ImageDirectory() + "wall_specular.png", GL_RGB);*/

	Mesh* testMesh = new Mesh((Utility::ModelDirectory() + "cube.obj").c_str());
	testMesh->textures.push_back(Texture(containerDiffuse, Texture::TextureType::Diffuse));
	testMesh->textures.push_back(Texture(containerSpecular, Texture::TextureType::Specular));
	testMesh->textures.push_back(Texture(containerEmission, Texture::TextureType::Emission));

	std::cout << testMesh->vertices.size() << std::endl;

	defaultShader.Use();
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.specular"), 1);
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.emission"), 2);

	glm::vec3 pointLightPositions[] =
	{
		glm::vec3(0.0f, 0.5f, -3.0f)
	};
	

	while (!glfwWindowShouldClose(GameManager::Instance().CurrentWindow()->GetWindow()))
	{
		Clock::CalculateTime();

		if (_input->GetKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(GameManager::Instance().CurrentWindow()->GetWindow(), GL_TRUE);
		}

		if (_input->GetKeyPressed(GLFW_KEY_F1))
		{
			_context->isWireframeMode = !_context->isWireframeMode;
			if (_context->isWireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}

		glm::vec3 direction;
		if (_input->GetKeyDown(GLFW_KEY_W))
		{
			direction.x += 1.0f;
		}
		if (_input->GetKeyDown(GLFW_KEY_S))
		{
			direction.x -= 1.0f;
		}
		if (_input->GetKeyDown(GLFW_KEY_A))
		{
			direction.y += 1.0f;
		}
		if (_input->GetKeyDown(GLFW_KEY_D))
		{
			direction.y -= 1.0f;
		}
		_camera->MoveCamera(direction);
		_camera->RotateCamera(_input->GetMouseXOffset(), _input->GetMouseYOffset(), _input->isInverted);
		_camera->ZoomCamera(_input->GetScrollYOffset());

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Shaders
		defaultShader.Use();

		GLint viewPosLocation = glGetUniformLocation(defaultShader.program, "viewPos");
		glUniform3f(viewPosLocation, _camera->GetPosition().x, _camera->GetPosition().y, _camera->GetPosition().z);

		// Material properties
		glUniform1f(glGetUniformLocation(defaultShader.program, "material.shininess"), 32.0f);

		// Directional light
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.direction"), -0.2f,  -1.0f,  -0.3f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.ambient"),    0.01f,  0.01f,  0.01f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.diffuse"),    0.01f,  0.01f,  0.01f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.specular"),   0.01f,  0.01f,  0.01f);

		// Point light 1
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].ambient"),    0.01f,  0.01f,  0.01f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].diffuse"),    0.8f,   0.8f,   0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].specular"),   1.0f,   1.0f,   1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].constant"),   1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].linear"),	  0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].quadratic"),  0.032f);

		// Spot light
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.position"), _camera->GetPosition().x, _camera->GetPosition().y, _camera->GetPosition().z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.direction"), _camera->GetFront().x, _camera->GetFront().y, _camera->GetFront().z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.ambient"),	0.01f, 0.01f, 0.01f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.diffuse"),	1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.specular"),	1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(defaultShader.program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Create camera transform
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

		// Pass matrices to shader
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		testMesh->Bind();
		glUniform1i(glGetUniformLocation(defaultShader.program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(defaultShader.program, "material.specular"), 1);
		glUniform1i(glGetUniformLocation(defaultShader.program, "material.emission"), 2);

		glm::mat4 modelMatrix;
		modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 0, testMesh->vertices.size());

		// Swap buffers
		glfwSwapBuffers(GameManager::Instance().CurrentWindow()->GetWindow());
		_input->Update();
	}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void GameManager::Destroy()
{
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
