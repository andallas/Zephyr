#include "GameManager.h"


GameManager::~GameManager()
{
	delete _window;
	delete _context;
	delete _input;
}

GameManager& GameManager::Instance()
{
	static GameManager instance;
	return instance;
}

void GameManager::Initialization()
{
	_context = new Context(_width, _height);
	_window = new Window(_width, _height, _title, nullptr, nullptr);

	_context->PreInitialization();
	_window->Initialize();
	_context->PostInitialization(_window->GetWindow());

	_input->Initialize();
}

Window* GameManager::CurrentWindow()
{
	return _window;
}


GLuint GameManager::GetWidth()
{
	return _width;
}

GLuint GameManager::GetHeight()
{
	return _height;
}
