#ifndef QUATERNION_H
#define QUATERNION_H
#pragma once

#include <iostream>
#include "Constants.h"
#include "Vector.h"
#include "Matrix.h"

template <class dtype>
class Quaternion
{
public:
	// Constructors
	Quaternion<dtype>();
	Quaternion<dtype>(dtype _a, dtype _b=0, dtype _c=0, dtype _d=0);

	Quaternion<dtype>(const dtype _a, const Vector<dtype, 3>& v);
	Quaternion<dtype>(const Quaternion<dtype>& q);

	// Casts 
	friend Vector<dtype, 4> vector_cast<dtype>(const Quaternion<dtype>& q);
	friend Matrix<dtype, 4, 4> rot_matrix_cast<dtype>(const Quaternion<dtype>& q);
	friend Quaternion<dtype> quaternion_cast<dtype>(const Matrix<dtype, 4, 4>& m);

	// Accessors
	dtype scalar() const;
	Vector<dtype, 3> vector() const;

	// Misc
	dtype norm() const;
	dtype squared_norm() const;
	Quaternion<dtype> get_conjugate() const;

	// Rotations
	static Quaternion<dtype> rotate_quaternion(const Vector<dtype, 3>& axis, const dtype angle);
	static Quaternion<float> getRotationQuaternion(float pitch, float yaw, float roll);
	static Matrix<float, 4, 4> getRotationMatrix(float pitch, float yaw, float roll);

	static Quaternion<dtype> lookAtQuaternion(const Vector<float, 3>& direction, const Vector<float, 3>& up);

	dtype pitch();
	dtype yaw();
	dtype roll();

	// + -
	Quaternion<dtype> operator+(const dtype x) const;
	Quaternion<dtype> operator-(const dtype x) const;

	Quaternion<dtype> operator+(const Quaternion<dtype>& x) const;
	Quaternion<dtype> operator-(const Quaternion<dtype>& x) const;

	// * /
	Quaternion<dtype> operator*(const dtype x) const;
	Quaternion<dtype> operator/(const dtype x) const;

	Quaternion<dtype> operator*(const Quaternion<dtype>& x) const;
	Quaternion<dtype> operator/(const Quaternion<dtype>& x) const;

	Quaternion<dtype> operator*(const Matrix<dtype, 4, 4>& m) const;
	Quaternion<dtype> cross_product(const Quaternion<dtype>& x) const;

	Quaternion<dtype> inverse() const;

	// Asignement op
	void operator+=(const dtype x);
	void operator-=(const dtype x);

	void operator+=(const Quaternion<dtype>& x);
	void operator-=(const Quaternion<dtype>& x);

	void operator*=(const Quaternion<dtype>& x);
	void operator/=(const Quaternion<dtype>& x);

	void operator*=(const dtype x);
	void operator/=(const dtype x);

	void operator=(const Quaternion<dtype>& x);

	void conjugate();

	// Usual quaternion
	static constexpr Quaternion<dtype> i();
	static constexpr Quaternion<dtype> j();
	static constexpr Quaternion<dtype> k();

	// print
	void print() const;
private:
	dtype a, b, c, d;
};

#include "Quaternion.cpp"

#endif