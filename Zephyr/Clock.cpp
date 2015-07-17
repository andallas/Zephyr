#include "Clock.h"


GLfloat Clock::_deltaTime = 0.0f;
GLfloat Clock::_lastFrame = 0.0f;

void Clock::CalculateTime()
{
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;
}

GLfloat Clock::GetDeltaTime()
{
	return _deltaTime;
}