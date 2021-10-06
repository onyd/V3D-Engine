#ifndef MATRIX_H
#define MATRIX_H
#pragma once

#include <iostream>
#include "ArrayOps.h"

template <class dtype, size_t size>
class Vector;

template <class dtype, size_t rows, size_t cols>
class Matrix
{
public:
	// Constructors
	Matrix<dtype, rows, cols>();
	Matrix<dtype, rows, cols>(const dtype filled_value);

	Matrix<dtype, rows, cols>(const Matrix<dtype, rows, cols>& mat);
	Matrix<dtype, rows, cols>(const std::array<dtype, rows*cols>& content);

	// Accessors
	std::array<unsigned int, 2> shape() const;
	dtype& operator()(size_t i, size_t j);
	const dtype& operator()(size_t i, size_t j) const;

	// Misc
	void transpose();

	// Rotations
	static Matrix<dtype, 4, 4> lookAtMatrix(const Vector<dtype, 3>& direction, const Vector<dtype, 3>& up);

	// + -
	Matrix<dtype, rows, cols> operator+(const Matrix<dtype, rows, cols>& other) const;
	Matrix<dtype, rows, cols> operator-(const Matrix<dtype, rows, cols>& other) const;

	Matrix<dtype, rows, cols> operator+(const dtype x) const;
	Matrix<dtype, rows, cols> operator-(const dtype x) const;

	// * /
	template <size_t cols_2>
	Matrix<dtype, rows, cols_2> matmul(const Matrix<dtype, cols, cols_2>& other) const;
	Vector<dtype, rows> matmul(const Vector<dtype, cols>& other) const;

	Vector<dtype, rows> operator*(const Vector<dtype, cols>& other) const; // matmul

	Matrix<dtype, rows, cols> operator*(const Matrix<dtype, rows, cols>& other) const;
	Matrix<dtype, rows, cols> operator/(const Matrix<dtype, rows, cols>& other) const;

	Matrix<dtype, rows, cols> operator*(const dtype x) const;
	Matrix<dtype, rows, cols> operator/(const dtype x) const;

	// asignement op
	void operator=(const Matrix<dtype, rows, cols>& m);

	void operator+=(const Matrix<dtype, rows, cols>& other);
	void operator-=(const Matrix<dtype, rows, cols>& other);

	void operator+=(const dtype x);
	void operator-=(const dtype x);

	void operator*=(const Vector<dtype, cols>& other); // matmul

	void operator*=(const Matrix<dtype, rows, cols>& other);
	void operator/=(const Matrix<dtype, rows, cols>& other);

	void operator*=(const dtype x);
	void operator/=(const dtype x);


	dtype inner_product(const Matrix<dtype, rows, cols>& other) const;

	void print() const;
private:
	std::array<dtype, rows * cols> _content;
	bool _transposed;
};

template <class dtype, size_t N>
Matrix<dtype, N, N> identityMatrix();

#include "Matrix.cpp"
#endif
