#include "Camera.h"
#include "GameManager.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::MoveCamera()
{
	GLfloat cameraSensitivty = _cameraSpeed * Clock::GetDeltaTime();

	if (GameManager::Instance().GetInput()->GetKey(GLFW_KEY_W))
	{
		_cameraPos += cameraSensitivty * _cameraFront;
	}
	if (GameManager::Instance().GetInput()->GetKey(GLFW_KEY_S))
	{
		_cameraPos -= cameraSensitivty * _cameraFront;
	}

	if (GameManager::Instance().GetInput()->GetKey(GLFW_KEY_A))
	{
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSensitivty;
	}
	if (GameManager::Instance().GetInput()->GetKey(GLFW_KEY_D))
	{
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSensitivty;
	}
}

void Camera::RotateCamera()
{
	_yaw += GameManager::Instance().GetInput()->GetMouseXOffset();
	_pitch += GameManager::Instance().GetInput()->GetMouseYOffset();

	if (_pitch > 89.0f)
	{
		_pitch = 89.0f;
	}

	if (_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}

	bool inverted = GameManager::Instance().GetInput()->isInverted;

	glm::vec3 front;
	front.x = cos(glm::radians((inverted) ? _pitch : -_pitch)) * cos(glm::radians(_yaw));
	front.y = sin(glm::radians((inverted) ? _pitch : -_pitch));
	front.z = cos(glm::radians((inverted) ? _pitch : -_pitch)) * sin(glm::radians(_yaw));
	_cameraFront = glm::normalize(front);
}

void Camera::ZoomCamera()
{
	if (_aspectRatio >= MIN_ASPECT && _aspectRatio <= MAX_ASPECT)
	{
		_aspectRatio -= GameManager::Instance().GetInput()->GetScrollYOffset();
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