#include "GameObject.h"

GameObject::GameObject()
{
	_transform = new Transform();
	_meshRenderer = new MeshRenderer();
}


GameObject::~GameObject()
{
	delete _transform;
	delete _meshRenderer;
}

void GameObject::SetTag(std::string tag)
{
	_tag = tag;
}
