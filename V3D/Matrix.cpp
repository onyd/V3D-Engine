#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"

// Constructors
template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols>::Matrix()
	: _content(std::array<dtype, rows*cols>()), _transposed(false)
{
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols>::Matrix(const dtype filled_value)
	: Matrix<dtype, rows, cols>()
{
	_content.fill(filled_value);
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols>::Matrix(const std::array<dtype, rows* cols>& content)
	: Matrix<dtype, rows, cols>()
{
	_content = content;
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols>::Matrix(const Matrix<dtype, rows, cols>& mat)
	: Matrix<dtype, rows, cols>(mat._content)
{
}

// Accesors
template<class dtype, size_t rows, size_t cols>
std::array<unsigned int, 2> Matrix<dtype, rows, cols>::shape() const
{
	return std::array<unsigned int, 2> {rows, cols};
}

template<class dtype, size_t rows, size_t cols>
dtype& Matrix<dtype, rows, cols>::operator()(size_t i, size_t j)
{
	if (_transposed == false)
		return this->_content[i * cols + j];
	else 
		return this->_content[j * cols + i];
}

template<class dtype, size_t rows, size_t cols>
const dtype& Matrix<dtype, rows, cols>::operator()(size_t i, size_t j) const
{
	if (_transposed == false)
		return this->_content[i * cols + j];
	else
		return this->_content[j * cols + i];
}

// Misc
template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::transpose()
{
	_transposed = not _transposed;
}

template<class dtype, size_t N>
Matrix<dtype, N, N> identityMatrix()
{
	Matrix<float, N, N> result;
	for (unsigned int i = 0; i < N; i++) {
		result(i, i) = static_cast<dtype>(1);
	}
	return result;
}

// Rotations
template<class dtype, size_t rows, size_t cols>
Matrix<dtype, 4, 4> Matrix<dtype, rows, cols>::lookAtMatrix(const Vector<dtype, 3>& direction, const Vector<dtype, 3>& up)
{
	Vector<float, 3> x_axis = up.cross_product(direction);
	x_axis.normalize();
	Vector<float, 3> y_axis = direction.cross_product(x_axis);
	y_axis.normalize();

	Matrix<float, 4, 4> rot;

	rot(0, 0) = x_axis[0];
	rot(0, 1) = x_axis[1];
	rot(0, 2) = x_axis[2];

	rot(1, 0) = y_axis[0];
	rot(1, 1) = y_axis[1];
	rot(1, 2) = y_axis[2];

	rot(2, 0) = x_axis[0];
	rot(2, 1) = x_axis[1];
	rot(2, 2) = x_axis[2];

	rot(3, 3) = static_cast<dtype>(1);

	return rot;
}

// + -
template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator+(const Matrix<dtype, rows, cols>& other) const
{
	return Matrix<dtype, rows, cols>(elementSum(_content, other._content));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator-(const Matrix<dtype, rows, cols>& other) const
{
	return Matrix<dtype, rows, cols>(elementSubstraction(_content, other._content));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator+(const dtype x) const
{
	return Matrix<dtype, rows, cols>(constantSum(_content, x));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator-(const dtype x) const
{
	return Matrix<dtype, rows, cols>(constantSubstraction(_content, x));
}

// * /
template<class dtype, size_t rows, size_t cols>
template <size_t cols_2>
Matrix<dtype, rows, cols_2> Matrix<dtype, rows, cols>::matmul(const Matrix<dtype, cols, cols_2>& other) const
{
	Matrix<dtype, rows, cols_2> result;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols_2; j++) {
			for (unsigned int k = 0; k < cols; k++) {
				result(i, j) += (*this)(i, k) * other(k, j);
			}
		}
	}
	return result;
}

template<class dtype, size_t rows, size_t cols>
Vector<dtype, rows> Matrix<dtype, rows, cols>::matmul(const Vector<dtype, cols>& other) const 
{
	Vector<dtype, rows> result;
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int k = 0; k < cols; k++) {
			result[i] += (*this)(i, k) * other[k];
		}
	}
	return result;
}

template<class dtype, size_t rows, size_t cols>
Vector<dtype, rows> Matrix<dtype, rows, cols>::operator*(const Vector<dtype, cols>& other) const
{
	return this->matmul(other);
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator*(const Matrix<dtype, rows, cols>& other) const
{
	return Matrix<dtype, rows, cols>(elementProduct(_content, other._content));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator/(const Matrix<dtype, rows, cols>& other) const
{
	return Matrix<dtype, rows, cols>(elementDivision(_content, other._content));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator*(const dtype x) const
{
	return Matrix<dtype, rows, cols>(constantProduct(_content, x));
}

template<class dtype, size_t rows, size_t cols>
Matrix<dtype, rows, cols> Matrix<dtype, rows, cols>::operator/(const dtype x) const
{
	return Matrix<dtype, rows, cols>(constantDivision(_content, x));

}

// asignement op
template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator=(const Matrix<dtype, rows, cols>& m)
{
	_content = m._content;
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator+=(const Matrix<dtype, rows, cols>& other)
{
	this->operator=((*this) + other);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator-=(const Matrix<dtype, rows, cols>& other)
{
	this->operator=((*this) - other);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator+=(const dtype x)
{
	this->operator=((*this) + x);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator-=(const dtype x)
{
	this->operator=((*this) - x);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator*=(const Vector<dtype, cols>& other)
{
	this->operator=(this->matmul(other));

}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator*=(const Matrix<dtype, rows, cols>& other)
{
	this->operator=((*this) * other);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator/=(const Matrix<dtype, rows, cols>& other)
{
	this->operator=((*this) / other);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator*=(const dtype x)
{
	this->operator=((*this) * x);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::operator/=(const dtype x)
{
	this->operator=((*this) / x);
}

template<class dtype, size_t rows, size_t cols>
dtype Matrix<dtype, rows, cols>::inner_product(const Matrix<dtype, rows, cols>& other) const
{
	return sum(((*this) * other)._content);
}

template<class dtype, size_t rows, size_t cols>
void Matrix<dtype, rows, cols>::print() const
{
	tensor_print(_content, shape());
}

#endif

