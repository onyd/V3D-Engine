#ifndef LINE_CPP
#define LINE_CPP

#include "Line.h"


template<class dtype>
Line<dtype>::Line(const Vector<dtype, 3>& p1, const Vector<dtype, 3>& p2)
	: _direction(p2 - p1), _point(p1)
{
}

template<class dtype>
Vector<dtype, 3> Line<dtype>::getPoint() const
{
	return _point;
}

template<class dtype>
Vector<dtype, 3> Line<dtype>::getDirection() const
{
	return _direction;
}

template<class dtype>
Vector<dtype, 3> Line<dtype>::intersect(const Line<dtype>& line) const
{
	return Vector<dtype, 3>();
}

#endif 
