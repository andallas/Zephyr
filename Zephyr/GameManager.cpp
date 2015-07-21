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

	// Vertex data and buffer objects
	GLfloat vertices[] =
	{
		/*
		Positions					Normals						Texture Coords
		*/
		// Front
		-0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		 0.0f,  1.0f,

		// Back
		 0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		 0.0f,  1.0f,

		// Left
		-0.5f,  0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,		 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,		 0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,		 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,		 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,		 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,		 0.0f,  1.0f,

		// Right
		 0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		 1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		 0.0f,  1.0f,

		// Top
		-0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,		 0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,		 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,		 0.0f,  1.0f,

		// Bottom
		 0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,		 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		 0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		 1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,		 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,		 0.0f,  1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] =
	{
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// TexCoords attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);

	// Load Textures
	GLuint diffuseMap = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container2.png");
	GLuint specularMap = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container2_specular.png");
	GLuint emissionMap = TextureLoader::LoadTexture(Utility::ImageDirectory() + "container2_emission.jpg");

	defaultShader.Use();
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.specular"), 1);
	glUniform1i(glGetUniformLocation(defaultShader.program, "material.emission"), 2);
	

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
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.ambient"),    0.05f,  0.05f,  0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.diffuse"),    0.4f,   0.4f,   0.4f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "directionalLight.specular"),   0.5f,   0.5f,   0.5f);

		// Point light 1
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].ambient"),    0.05f,  0.05f,  0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].diffuse"),    0.8f,   0.8f,   0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[0].specular"),   1.0f,   1.0f,   1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[0].quadratic"), 0.032f);
		
		// Point light 2
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(defaultShader.program, "pointLights[3].quadratic"), 0.032f);

		// Spot light
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.position"), _camera->GetPosition().x, _camera->GetPosition().y, _camera->GetPosition().z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.direction"), _camera->GetFront().x, _camera->GetFront().y, _camera->GetFront().z);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(defaultShader.program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
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

		// Bind textures map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap);

		// Draw the containers
		glBindVertexArray(VAO);

		glm::mat4 modelMatrix;
		for (GLuint i = 0; i < 10; i++)
		{
			modelMatrix = glm::mat4();
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// New shader
		lampShader.Use();
		
		// Get location objects from matrices on shader
		modelLocation = glGetUniformLocation(lampShader.program, "model");
		viewLocation = glGetUniformLocation(lampShader.program, "view");
		projectionLocation = glGetUniformLocation(lampShader.program, "projection");

		// Pass matrices to shader
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		// Draw the point light objects
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			modelMatrix = glm::mat4();
			modelMatrix = glm::translate(modelMatrix, pointLightPositions[i]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Swap buffers
		glfwSwapBuffers(GameManager::Instance().CurrentWindow()->GetWindow());
		_input->Update();
	}

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
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
