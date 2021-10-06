#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"

// Constructors
template<class dtype, size_t size>
Vector<dtype, size>::Vector()
	: _content(std::array<dtype, size>())
{
}

template<class dtype, size_t size>
Vector<dtype, size>::Vector(dtype filled_value)
	: Vector<dtype, size>()
{
	_content.fill(filled_value);
}

template<class dtype, size_t size>
Vector<dtype, size>::Vector(const std::array<dtype, size>& content)
	: Vector<dtype, size>()
{
	_content = content;
}

template<class dtype, size_t size>
Vector<dtype, size>::Vector(const Vector<dtype, size>& vec)
	: Vector<dtype, size>(vec._content)
{
}

template<class dtype, size_t size>
template<Dtyped<dtype> ...T>
Vector<dtype, size>::Vector(dtype c, T ...components)
	: Vector<dtype, size>()
{
	static_assert(sizeof...(components) + 1 == size, "Number of components must be equal to vector size");
	_content = { c, components... };
}

// Casts
template<class dtype>
Quaternion<dtype> quaternion_cast(const Vector<dtype, 3>& v)
{
	return Quaternion<dtype>(static_cast<dtype>(0), v[0], v[1], v[2]);
}

template<class dtype>
Quaternion<dtype> quaternion_cast(const Vector<dtype, 4>& v)
{
	return Quaternion<dtype>(v[3], v[0], v[1], v[2]);
}

template<class dtype>
Vector<dtype, 4> vector4_cast(const Vector<dtype, 3>& v)
{
	return Vector<dtype, 4>(v[0], v[1], v[2], 1.0f);
}

template<class dtype>
Vector<dtype, 3> vector3_cast(const Vector<dtype, 4>& v)
{
	return Vector<dtype, 3>(v[0], v[1], v[2]);
}

template<class dtype, size_t size, size_t new_size>
Vector<dtype, new_size> resize(const Vector<dtype, size>& v, dtype filled_element)
{
	Vector<float, new_size> result;
	if (size > new_size) {
		for (unsigned int i = 0; i < new_size; i++) {
			result[i] = v[i];
		}
	}
	else if(size < new_size){
		for (unsigned int i = 0; i < size; i++) {
			result[i] = v[i];
		}
		for (unsigned int i = size + 1; i < new_size; i++) {
			result[i] = filled_element;
		}
	}
	return result;
}

// Accessors
template<class dtype, size_t size>
std::array<size_t, 1> Vector<dtype, size>::shape() const
{
	return std::array<size_t, 1> {size};
}

template<class dtype, size_t size>
dtype& Vector<dtype, size>::operator[](unsigned int x)
{
	return _content.at(x);
}

template<class dtype, size_t size>
const dtype& Vector<dtype, size>::operator[](unsigned int x) const
{
	return _content.at(x);
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator+(const Vector<dtype, size>& other) const
{
	return Vector<dtype, size>(elementSum(_content, other._content));
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator-(const Vector<dtype, size>& other) const
{
	return Vector<dtype, size>(elementSubstraction(_content, other._content));
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator+(const dtype x) const
{
	return Vector<dtype, size>(constantSum(_content, x));
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator-(const dtype x) const
{
	return Vector<dtype, size>(constantSubstraction(_content, x));

}

// * /
template<class dtype, size_t size>
template<size_t cols>
Vector<dtype, cols> Vector<dtype, size>::matmul(const Matrix<dtype, size, cols>& other) const
{
	Vector<dtype, size> result;
	for (unsigned int j = 0; j < cols; j++) {
		for (unsigned int k = 0; k < size; k++) {
			result[j] += (*this)[k] * other(k, j);
		}
	}
	return Vector<dtype, size>(result);
}

template<class dtype, size_t size>
template<size_t cols>
Vector<dtype, cols> Vector<dtype, size>::operator*(const Matrix<dtype, size, cols>& other) const
{
	return this->matmul(other);
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator*(const Vector<dtype, size>& other) const
{
	return Vector<dtype, size>(elementProduct(_content, other._content));
}


template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator/(const Vector<dtype, size>& other) const
{
	return Vector<dtype, size>(elementDivision(_content, other._content));
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator*(const dtype x) const
{
	return Vector<dtype, size>(constantProduct(_content, x));
}

template<class dtype, size_t size>
Vector<dtype, size> Vector<dtype, size>::operator/(const dtype x) const
{
	return Vector<dtype, size>(constantDivision(_content, x));
}

// Asignement ops
template<class dtype, size_t size>
void Vector<dtype, size>::operator=(const Vector<dtype, size>& v)
{
	_content = v._content;
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator+=(const Vector<dtype, size>& other)
{
	this->operator=((*this) + other);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator-=(const Vector<dtype, size>& other)
{
	this->operator=((*this) - other);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator+=(const dtype x)
{
	this->operator=((*this) + x);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator-=(const dtype x)
{
	this->operator=((*this) - x);
}

template<class dtype, size_t size>
template<size_t cols>
void Vector<dtype, size>::operator*=(const Matrix<dtype, size, cols>& other)
{
	this->operator=(this->matmul(other));
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator*=(const Vector<dtype, size>& other)
{
	this->operator=((*this) * other);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator/=(const Vector<dtype, size>& other)
{
	this->operator=((*this) / other);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator*=(const dtype x)
{
	this->operator=((*this) * x);
}

template<class dtype, size_t size>
void Vector<dtype, size>::operator/=(const dtype x)
{
	this->operator=((*this) / x);
}

// Misc
template<class dtype, size_t size>
Vector<dtype, 3> Vector<dtype, size>::cross_product(const Vector<dtype, 3>& other) const
{
	return Vector<dtype, 3>(_content[1] * other[2] - _content[2] * other[1],
							_content[2] * other[0] - _content[0] * other[2],
							_content[0] * other[1] - _content[1] * other[0]);
}

template<class dtype, size_t size>
dtype Vector<dtype, size>::inner_product(const Vector<dtype, size>& other) const
{	
	return sum(((*this) * other)._content);
}

template<class dtype, size_t size>
dtype Vector<dtype, size>::norm() const
{
	return sqrt(this->inner_product(*this));
}

template<class dtype, size_t size>
dtype Vector<dtype, size>::fastNorm() const
{
	return static_cast<dtype>(1) / fast_rsqrt(this->inner_product(*this));
}

template<class dtype, size_t size>
Vector<float, size> Vector<dtype, size>::normalized() const
{
	return (*this) / this->norm();
}

template<class dtype, size_t size>
void Vector<dtype, size>::normalize()
{
	this->operator/=(this->norm());
}

template<class dtype, size_t size>
Vector<float, size> Vector<dtype, size>::fastNormalized() const
{
	return (*this) * fast_rsqrt(this->inner_product(*this));
}

template<class dtype, size_t size>
void Vector<dtype, size>::fastNormalize()
{
	this->operator*=(fast_rsqrt(this->inner_product(*this)));
}

template<class dtype, size_t size>
void Vector<dtype, size>::print() const
{
	tensor_print(_content, shape());
}

#endif


