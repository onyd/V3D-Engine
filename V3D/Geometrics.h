#ifndef GEOMETRICS_H
#define GEOMETRICS_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "Vector.h"
#include "Quaternion.h"
#include "olcPixelGameEngine.h"

class Triangle
{
public:
	Triangle() {
		p[0] = Vector<float, 3>();
		p[1] = Vector<float, 3>();
		p[2] = Vector<float, 3>();

		c = olc::Pixel(0, 0, 0);
	};

	Triangle(const Vector<float, 3>* points, olc::Pixel color = olc::Pixel(0, 0, 0)) {
		p[0] = points[0];
		p[1] = points[1];
		p[2] = points[2];

		c = color;
	};

	Triangle(const Triangle& t) {
		p[0] = t.p[0];
		p[1] = t.p[1];
		p[2] = t.p[2];

		c = t.c;
	}
	
	Triangle operator+(const Vector<float, 3>& translation) {
		Vector<float, 3> points[] = { p[0] + translation, p[1] + translation, p[2] + translation };
		return Triangle(points, c);
	};

	Triangle operator-(const Vector<float, 3>& translation) {
		Vector<float, 3> points[] = { p[0] - translation, p[1] - translation, p[2] - translation };
		return Triangle(points, c);
	};

	void operator+=(const Vector<float, 3>& translation) {
		p[0] += translation;
		p[1] += translation;
		p[2] += translation;
	};

	void operator*=(const Vector<float, 3>& scale) {
		p[0] *= scale;
		p[1] *= scale;
		p[2] *= scale;
	};

	void matmul(const Matrix<float, 4, 4>& m) {
		p[0] = vector3_cast(vector4_cast(p[0]) * m);
		p[1] = vector3_cast(vector4_cast(p[1]) * m);
		p[2] = vector3_cast(vector4_cast(p[2]) * m);
	}

	Vector<float, 3> get_normal()
	{
		return (p[1] - p[0]).cross_product(p[2] - p[0]);
	};

	Vector<float, 3> p[3];
	olc::Pixel c;
};

class Mesh {
public:
	Mesh();
	Mesh(const std::vector<Triangle>& t);

	std::vector<Triangle>& getTriangles();
	Triangle& operator[](size_t i);

	static Mesh load_from_file(const std::string& file_name);
private:
	std::vector<Triangle> _t;
};

#endif 
