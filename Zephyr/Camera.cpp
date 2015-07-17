#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	_cameraPos = position;
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::MoveCamera(glm::vec3 direction)
{
	GLfloat speed = _cameraSpeed * Clock::GetDeltaTime();

	if (direction.x > 0)
	{
		_cameraPos += speed * _cameraFront;
	}
	if (direction.x < 0)
	{
		_cameraPos -= speed * _cameraFront;
	}
	if (direction.y > 0)
	{
		_cameraPos -= speed * _cameraRight;
	}
	if (direction.y < 0)
	{
		_cameraPos += speed * _cameraRight;
	}
}

void Camera::RotateCamera(GLfloat xOffset, GLfloat yOffset, bool isInverted, bool constrainPitch)
{
	xOffset *= _cameraRotateSpeed;
	yOffset *= _cameraRotateSpeed;

	_yaw += xOffset;
	_pitch += (isInverted) ? yOffset : -yOffset;

	if (constrainPitch)
	{
		if (_pitch > 89.0f)
		{
			_pitch = 89.0f;
		}

		if (_pitch < -89.0f)
		{
			_pitch = -89.0f;
		}
	}

	UpdateCameraVectors();
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

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
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


// private
void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	
	_cameraFront	= glm::normalize(front);
	_cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));
	_cameraUp		= glm::normalize(glm::cross(_cameraRight, _cameraFront));
}