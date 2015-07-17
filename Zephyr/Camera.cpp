#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::MoveCamera(glm::vec3 direction)
{
	GLfloat cameraSensitivty = _cameraSpeed * Clock::GetDeltaTime();

	if (direction.x > 0)
	{
		_cameraPos += cameraSensitivty * _cameraFront;
	}
	if (direction.x < 0)
	{
		_cameraPos -= cameraSensitivty * _cameraFront;
	}
	if (direction.y > 0)
	{
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSensitivty;
	}
	if (direction.y < 0)
	{
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSensitivty;
	}
}

void Camera::RotateCamera(GLfloat yaw, GLfloat pitch, bool isInverted)
{
	_yaw += yaw;
	_pitch += pitch;

	if (_pitch > 89.0f)
	{
		_pitch = 89.0f;
	}

	if (_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}

	bool inverted = isInverted;

	glm::vec3 front;
	front.x = cos(glm::radians((inverted) ? _pitch : -_pitch)) * cos(glm::radians(_yaw));
	front.y = sin(glm::radians((inverted) ? _pitch : -_pitch));
	front.z = cos(glm::radians((inverted) ? _pitch : -_pitch)) * sin(glm::radians(_yaw));
	_cameraFront = glm::normalize(front);
}

void Camera::ZoomCamera(GLfloat scrollOffset)
{
	if (_aspectRatio >= MIN_ASPECT && _aspectRatio <= MAX_ASPECT)
	{
		_aspectRatio -= scrollOffset;
	}
	if (_aspectRatio <= MIN_ASPECT)
	{
		_aspectRatio = MIN_ASPECT;
	}
	if (_aspectRatio >= MAX_ASPECT)
	{
		_aspectRatio = MAX_ASPECT;
	}
}

GLfloat Camera::GetNearPlane()
{
	return _nearPlane;
}

GLfloat Camera::GetFarPlane()
{
	return _farPlane;
}

GLfloat Camera::GetAspectRatio()
{
	return _aspectRatio;
}

glm::vec3 Camera::GetPosition()
{
	return _cameraPos;
}

glm::vec3 Camera::GetFront()
{
	return _cameraFront;
}

glm::vec3 Camera::GetUp()
{
	return _cameraUp;
}