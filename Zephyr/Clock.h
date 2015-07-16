#ifndef CLOCK_H
#define CLOCK_H

#include <glfw3.h>


class Clock
{
public:
	static void CalculateTime();
	static GLfloat GetDeltaTime();

private:
	static GLfloat _deltaTime;
	static GLfloat _lastFrame;
};

#endif