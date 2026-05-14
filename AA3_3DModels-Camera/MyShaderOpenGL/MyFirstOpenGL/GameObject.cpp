#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
	meshRenderer = new MeshRenderer();
}


GameObject::~GameObject()
{
	delete transform;
	delete meshRenderer;
}
