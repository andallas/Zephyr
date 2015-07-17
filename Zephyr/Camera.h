#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Clock.h"


class Camera
{
public:
	Camera();
	~Camera();
	void MoveCamera(glm::vec3 direction);
	void RotateCamera(GLfloat yaw, GLfloat pitch, bool isInverted);
	void ZoomCamera(GLfloat scrollOffset);
	GLfloat GetNearPlane();
	GLfloat GetFarPlane();
	GLfloat GetAspectRatio();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();

private:
	const GLfloat MIN_ASPECT = 1.0f;
	const GLfloat MAX_ASPECT = 45.0f;
	GLfloat _nearPlane = 0.1f;
	GLfloat _farPlane = 100.0f;
	GLfloat _yaw;
	GLfloat _pitch;
	GLfloat _aspectRatio = 45.0f;
	GLfloat _cameraSpeed = 5.0f;
	glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif