#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include "Constants.h"
#include "Vector.h"
#include "Matrix.h"
#include "Geometrics.h"
#include "Camera.h"
#include "Lights.h"
#include "XAble.h"
#include "Plane.h"
#include "Line.h"

using namespace std;

class Object : public Movable, public Directable
{
public:
	Object();
	Object(Vector<float, 3>& pos, Mesh& mesh, size_t id = 0);
	Object(Vector<float, 3>& pos, const string& obj_file_name, size_t id = 0);
	void setId(size_t id);
	size_t getId();

	virtual vector<Triangle*> render(Camera& cam, vector<Light*>& lights);
	
protected:
	size_t countOutsidePoints(const Triangle& t, const Plane<float>& p) const;
	size_t clip(Triangle& t, const Plane<float>& p, Triangle* out1, Triangle* out2);
	Matrix<float, 4, 4> getModelMatrix();
	bool isInView(const Triangle& t, Camera& cam) const;
	bool isVisible(const Triangle& t, Vector<float, 3>& normal, Camera& cam) const;
	void project(Triangle* t, Camera& cam);
	void applyLights(Triangle& t, vector<Light*>& lights, Vector<float, 3>& normal);


	Mesh _mesh;
	size_t _id;
};

#endif