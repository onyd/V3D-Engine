#ifndef PLANEOBJECT_H
#define PLANEOBJECT_H
#pragma once

#include "MeshObject.h"
#include "Plane.h"

class PlaneObject : public MeshObject
{
public:
	PlaneObject(const Vector<float, 3>& normal, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id = 0);
	PlaneObject(const Plane<float>& p, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id = 0);

private:
	Vector<float, 3> _normal;
};

#endif 
