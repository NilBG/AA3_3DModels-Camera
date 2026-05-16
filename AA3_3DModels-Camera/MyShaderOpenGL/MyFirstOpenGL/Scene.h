#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include "GameObject.h"
#include "Camera.h"
#include "RenderManager.h"
#include "InputManager.h"

class Scene {
protected:

	Camera* _camera = nullptr;

	std::vector<GameObject*> _objects;
	
	std::vector<GameObject*> _ui;

public:
	Scene() = default;
	virtual ~Scene() {
		OnExit();
	}

	virtual void OnEnter() = 0;
	
	virtual void OnExit() {

		delete _camera;
		_camera = nullptr;

		// Destruimos todos los objetos de la escena
		for (GameObject* o : _objects) {
			delete o;
		}
		_objects.clear();

		for (GameObject* o : _ui) {
			delete o;
		}
		_ui.clear();
	}

	virtual void Update(float dt) {
		// Control de destruccion de objetos
		for (int i = _objects.size() - 1; i >= 0; i--) {
			if (_objects[i]->_isPendingDestroy) {
				delete _objects[i];
				_objects.erase(_objects.begin() + i);
			}
		}

		//Actualizar la camara
		_camera->Update(dt);

		// Actualizamos todos los objetos
		for (GameObject* o : _objects) {
			if (o != nullptr && o->_isVisible) {
				o->Update(dt);
			}
		}
	}

	virtual void Render() {

		// Generamos matrices de cámara
		glm::mat4 viewMatrix = _camera->GetViewMatrix();
		glm::mat4 projectionMatrix = _camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

		// El render de la escena simplemente le pide a cada objeto que se dibuje
		for (GameObject* o : _objects) {
			if (o != nullptr && o->_isVisible) {
				o->Render(viewMatrix, projectionMatrix);
			}
		}
	}

	GameObject* FindByTag(const std::string& tag)
	{
		for (GameObject* o : _objects)
		{
			if (o->_tag == tag)
				return o;
		}
		return nullptr;
	}

	// Metodo para añadir objetos a la escena
	void AddGameObject(GameObject* obj) {
		if (obj != nullptr) _objects.push_back(obj);
	}

	std::vector<GameObject*>& GetObjects() { return _objects; }
};
