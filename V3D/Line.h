#ifndef LINE_H
#define LINE_H
#pragma once

#include "Vector.h"

template<class dtype>
class Line
{
public:
	Line<dtype>(const Vector<dtype, 3>& p1, const Vector<dtype, 3>& p2);
	Vector<dtype, 3> getPoint() const;
	Vector<dtype, 3> getDirection() const;

	//Vector<dtype, 3> intersect(const Line<dtype>& line) const;

private:
	Vector<dtype, 3> _direction;
	Vector<dtype, 3> _point;
};

#include "Line.cpp"

#endif // !LINE_H
