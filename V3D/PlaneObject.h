#ifndef PLANEOBJECT_H
#define PLANEOBJECT_H
#pragma once

#include "Object.h"
#include "Plane.h"

class PlaneObject : public Object
{
public:
	PlaneObject(const Vector<float, 3>& normal, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id = 0);
	PlaneObject(const Plane<float>& p, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id = 0);

	vector<Triangle*> render(Camera& cam, vector<Light*>& lights) override;
private:
	Vector<float, 3> _normal;
};

#endif 
