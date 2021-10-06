#ifndef SCENE_CPP
#define SCENE_CPP

#include "Scene.h"

Scene::Scene(Camera& camera)
	: _camera(camera)
{
}

void Scene::add_object(Object* _objects)
{
	objects.push_back(_objects);
}

void Scene::remove_object(Object* _objects)
{
}

void Scene::add_light(Light* _light)
{
	lights.push_back(_light);
}

void Scene::remove_light(Light* _light)
{
}

Camera& Scene::getCamera()
{
	return _camera;
}

std::vector<Triangle*> Scene::render()
{
	std::vector<Triangle*> rendered;
	for (Object* o : objects) {
		for (Triangle* t : o->render(_camera, lights)) {
			rendered.push_back(t);
		}
	}
	std::sort(rendered.begin(), rendered.end(), [](Triangle* t1, Triangle* t2) {
		return ((t1->p[0][2] + t1->p[1][2] + t1->p[2][2]) > (t2->p[0][2] + t2->p[1][2] + t2->p[2][2]));
	});

	return rendered;
}
#endif