#ifndef VECTOR_H
#define VECTOR_H
#pragma once

#include <iostream>
#include "ArrayOps.h"
#include "FastFunctions.h"

template <class dtype, size_t row, size_t cols>
class Matrix;

template <class dtype, size_t size>
class Vector;

template <class dtype>
class Quaternion;

template<class dtype, class T>
concept Dtyped = std::is_convertible<T, dtype>::value;

template<class dtype, size_t size, size_t new_size> 
Vector<dtype, new_size> resize(const Vector<dtype, size>& v, dtype filled_element = 0);

template <class dtype, size_t size>
class Vector
{
public:
	// Constructors
	Vector<dtype, size>();
	Vector<dtype, size>(dtype filled_value);

	Vector<dtype, size>(const std::array<dtype, size>& content);
	Vector<dtype, size>(const Vector<dtype, size>& vec);

	template<Dtyped<dtype> ...T>
	Vector<dtype, size>(dtype c, T ...components);

	// Casts
	friend Quaternion<dtype> quaternion_cast<dtype>(const Vector<dtype, 3>& v);
	friend Quaternion<dtype> quaternion_cast<dtype>(const Vector<dtype, 4>& v);
	
	friend Vector<dtype, 4> vector4_cast<dtype>(const Vector<dtype, 3>& v);
	friend Vector<dtype, 3> vector3_cast<dtype>(const Vector<dtype, 4>& v);

	// Accessors
	std::array<size_t, 1> shape() const;
	dtype& operator[](size_t x);
	const dtype& operator[](size_t x) const;

	// + -
	Vector<dtype, size> operator+(const Vector<dtype, size>& other) const;
	Vector<dtype, size> operator-(const Vector<dtype, size>& other) const;

	Vector<dtype, size> operator+(const dtype x) const;
	Vector<dtype, size> operator-(const dtype x) const;

	// * /
	template <size_t cols>
	Vector<dtype, cols> matmul(const Matrix<dtype, size, cols>& other) const;
	template <size_t cols>
	Vector<dtype, cols> operator*(const Matrix<dtype, size, cols>& other) const;

	Vector<dtype, size> operator*(const Vector<dtype, size>& other) const;
	Vector<dtype, size> operator/(const Vector<dtype, size>& other) const;

	Vector<dtype, size> operator*(const dtype x) const;
	Vector<dtype, size> operator/(const dtype x) const;

	// Asignement op
	void operator=(const Vector<dtype, size>& v);

	void operator+=(const Vector<dtype, size>& other);
	void operator-=(const Vector<dtype, size>& other);

	void operator+=(const dtype x);
	void operator-=(const dtype x);

	template <size_t cols>
	void operator*=(const Matrix<dtype, size, cols>& other);

	void operator*=(const Vector<dtype, size>& other);
	void operator/=(const Vector<dtype, size>& other);

	void operator*=(const dtype x);
	void operator/=(const dtype x);

	// Misc
	Vector<dtype, 3> cross_product(const Vector<dtype, 3>& other) const;
	dtype inner_product(const Vector<dtype, size>& other) const;

	dtype norm() const;
	dtype fastNorm() const;

	Vector<float, size> normalized() const;
	void normalize();

	Vector<float, size> fastNormalized() const;
	void fastNormalize();

	void print() const;
private:
	std::array<dtype, size> _content;
};

#include "Vector.cpp"
#endif
