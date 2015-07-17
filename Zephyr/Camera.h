#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Clock.h"


class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);
	~Camera();
	void MoveCamera(glm::vec3 direction);
	void RotateCamera(GLfloat xOffset, GLfloat yOffset, bool isInverted, bool constrainPitch = true);
	void ZoomCamera(GLfloat scrollOffset);
	glm::mat4 GetViewMatrix();
	GLfloat GetNearPlane();
	GLfloat GetFarPlane();
	GLfloat GetAspectRatio();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();

private:
	void UpdateCameraVectors();

	const GLfloat MIN_ASPECT = 1.0f;
	const GLfloat MAX_ASPECT = 45.0f;
	GLfloat _nearPlane = 0.1f;
	GLfloat _farPlane = 100.0f;
	GLfloat _yaw;
	GLfloat _pitch;
	GLfloat _aspectRatio = 45.0f;
	GLfloat _cameraSpeed = 5.0f;
	GLfloat _cameraRotateSpeed = 1.0f;
	glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _cameraRight = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif