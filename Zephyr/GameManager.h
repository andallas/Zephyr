#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Context.h"
#include "Window.h"
#include "Input.h"

#include <iostream>


class GameManager
{
public:
	static GameManager& Instance();
	void GameManager::Initialization();
	Window* CurrentWindow();
	GLuint GetWidth();
	GLuint GetHeight();
	
private:
	GameManager() {};
	~GameManager();

	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;

	Window* _window;
	Context* _context;
	Input* _input;

	GLuint _width = 800;
	GLuint _height = 600;
	char* _title = "Zephyr";
};

#endif