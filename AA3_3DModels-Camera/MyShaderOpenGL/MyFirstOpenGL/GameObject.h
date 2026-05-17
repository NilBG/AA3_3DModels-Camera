#pragma once
#include <glm.hpp>
#include "Transform.h"
#include "MeshRenderer.h"

class GameObject
{
protected:
	Transform* _transform = nullptr;
	MeshRenderer* _meshRenderer = nullptr;

public:
	bool _isVisible = true;
	float _speed = 1.0f;
	bool _isPendingDestroy = false;
	std::string _tag = "";

	GameObject();
	virtual ~GameObject();
	void SetTag(std::string tag);
	virtual void Update(float dt) = 0;

	virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {};

	Transform* GetTransform() const { return _transform; }
	MeshRenderer* GetMeshRenderer() const { return _meshRenderer; }
};
