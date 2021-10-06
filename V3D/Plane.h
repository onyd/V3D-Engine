#ifndef PLNAE_H
#define PLNAE_H
#pragma once

#include "Line.h"
#include "Vector.h"

template<class dtype>
class Plane
{
public:
	Plane<dtype>();
	Plane<dtype>(dtype a, dtype b, dtype c, dtype d);
	Plane<dtype>(const Vector<dtype, 3>& normal, const Vector<dtype, 3>& point);
	Vector<dtype, 3> getNormal() const;
	dtype getA() const;
	dtype getB() const;
	dtype getC() const;
	dtype getD() const;

	Vector<dtype, 3> getIntersection(const Line<dtype>& line) const;

private:
	dtype _a, _b, _c, _d;
};

#include "Plane.cpp"

#endif // !PLNAE_H
