#include "Camera.h"

Camera::Camera()
	: GameObject()
{
	_mode = CameraMode::ORB;
	_transform->position = glm::vec3(0.0f, _orbitHeight, 5.0f);
	_target = _defaultTarget;
}

void Camera::Update(float dt)
{
	switch (_mode)
	{
	case CameraMode::ORB:
	{
		_angle += _speed * dt;
		_transform->position = glm::vec3(_target.x + _radius * cos(_angle), _transform->position.y, _target.z + _radius * sin(_angle));
	}
		break;

	case CameraMode::STATIC:
		break;

	case CameraMode::DOLLYZOOM:
	{
		_dollyZoomTimer += dt;
		//Clampeo la duración para simplemente poner si es más grande que 1
		float _clamp = glm::clamp(_dollyZoomTimer / _dollyZoomDuration, 0.0f, 1.0f);
		_fFov = 10.f + (60.f - 10.f) * _clamp;

		const float _initZ = 5.0f;
		const float _endZ = 1.0f;

		_transform->position = _dollyZoomPos + (_target - _dollyZoomPos) * _clamp;

		if (_clamp >= 1.0f)
		{
			SetMode(CameraMode::ORB);
			_target = _defaultTarget;
		}
	}
		break;
	default:
		break;
	}
}

void Camera::SetTarget(GameObject* gameObject)
{
	if (gameObject != nullptr)
		_target = gameObject->GetTransform()->position;
}

void Camera::SetMode(CameraMode newMode)
{
	_mode = newMode;

	switch (_mode)
	{
	case CameraMode::ORB:
		_fFov = 45.f;
		_transform->position.y = _orbitHeight;
		break;

	case CameraMode::STATIC:
		_fFov = 60.f;
		break;

	case CameraMode::DOLLYZOOM:
		_fFov = 10.f;
		_dollyZoomTimer = 0.0f;
		_dollyZoomPos = _transform->position;
		break;
	default:
		_mode = CameraMode::ORB;
		break;
	}
}

void Camera::SetPositionFromTarget(glm::vec3 offset)
{
	_transform->position = _target + offset;
}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(_transform->position, _target, localVectorUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(_fFov), aspectRatio, _fnear, _fFar);
}
