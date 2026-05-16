#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "GameObject.h"

enum class CameraMode {
	ORB,
	STATIC,
	DOLLYZOOM
};

class Camera : public GameObject {
public:

	glm::vec3 localVectorUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 _target = glm::vec3(0.f);
	const glm::vec3 _defaultTarget = glm::vec3(-0.1f, -0.8f, -1.5f);

	float _fFov = 45.f;
	float _fnear = 0.1f;
	float _fFar = 100.f;

	float _radius = 5.0f;
	float _angle = 0.0f;

	//Orbit
	const float _orbitHeight = 3.0f;

	//dollyZoom
	float _dollyZoomTimer = 0.0f;
	const float _dollyZoomDuration = 3.0f;
	glm::vec3 _dollyZoomPos = glm::vec3(0.f);

	Camera();

	CameraMode _mode;

	void Update(float dt) override;
	void SetTarget(GameObject* gameObject);
	void SetMode(CameraMode mode);
	void SetPositionFromTarget(glm::vec3 offset);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix(float aspectRatio) const;
};