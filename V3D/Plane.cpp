#ifndef PLANE_CPP
#define PLANE_CPP

#include "Plane.h"

template<class dtype>
Plane<dtype>::Plane()
	: _a(0), _b(0), _c(1), _d(0)
{
}

template<class dtype>
Plane<dtype>::Plane(dtype a, dtype b, dtype c, dtype d)
	: _a(a), _b(b), _c(c), _d(d)
{
}

template<class dtype>
Plane<dtype>::Plane(const Vector<dtype, 3>& normal, const Vector<dtype, 3>& point)
{
	Vector<float, 3> n = normal.normalized();
	_a = n[0];
	_b = n[1];
	_c = n[2];
	_d = -n.inner_product(point);
}

template<class dtype>
Vector<dtype, 3> Plane<dtype>::getNormal() const
{
	return Vector<dtype, 3>(_a, _b, _c);
}

template<class dtype>
dtype Plane<dtype>::getA() const
{
	return _a;
}

template<class dtype>
dtype Plane<dtype>::getB() const
{
	return _b;
}

template<class dtype>
dtype Plane<dtype>::getC() const
{
	return _c;
}

template<class dtype>
dtype Plane<dtype>::getD() const
{
	return _d;
}

template<class dtype>
Vector<dtype, 3> Plane<dtype>::getIntersection(const Line<dtype>& line) const
{
	Vector<dtype, 3> U = line.getDirection();
	Vector<dtype, 3> N = this->getNormal();
	dtype NU = N.inner_product(U);
	Vector<dtype, 3> P = line.getPoint();
	return  P + U * -(_d + N.inner_product(P)) / NU;
}

#endif // !PLANE_CPP
