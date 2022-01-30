#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <vector>
#include <algorithm>
#include "MeshObject.h"
#include "Matrix.h"
#include "Lights.h"

class Scene {
public:
	Scene() {};
	Scene(Camera& camera);

	void add_object(MeshObject* _objects);
	void remove_object(MeshObject* _objects);

	void add_light(Light* _light);
	void remove_light(Light* _light);

	Camera& getCamera();

	std::vector<Triangle*> render();
private:
	void project(Triangle* t, Camera& cam);
	unsigned int clip(Triangle& t, const Plane<float>& p, Triangle* out1, Triangle* out2);

	std::vector<MeshObject*> objects;
	std::vector<Light*> lights;

	Camera _camera;
};

#endif