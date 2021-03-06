#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include "Input.h"
#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Clock.h"
#include "Utility.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"


class GameManager
{
public:
	static GameManager& Instance();
	static void Run();
	static void Destroy();
	static Window* CurrentWindow();
	static Input* GetInput();
	static GLuint GetWidth();
	static GLuint GetHeight();

private:
	GameManager() {};
	virtual ~GameManager();
	static void Initialization();

	static Window* _window;
	static Context* _context;
	static Input* _input;
	static Camera* _camera;
	static Clock* _clock;
	static Renderer* _renderer;

	static GLuint _width;
	static GLuint _height;
	static char* _title;
};

#endif