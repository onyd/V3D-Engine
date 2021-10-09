#ifndef QUATERNION_CPP
#define QUATERNION_CPP

#include "Quaternion.h"

// Constructors
template<class dtype>
inline Quaternion<dtype>::Quaternion()
	: a(static_cast<dtype>(0)), b(static_cast<dtype>(0)), c(static_cast<dtype>(0)), d(static_cast<dtype>(0))
{
}

template<class dtype>
Quaternion<dtype>::Quaternion(dtype _a, dtype _b, dtype _c, dtype _d)
	: a(_a), b(_b), c(_c), d(_d)
{
}

template<class dtype>
Quaternion<dtype>::Quaternion(const dtype _a, const Vector<dtype, 3>& v)
	: a(_a), b(v[0]), c(v[1]), d(v[2])
{
}

template<class dtype>
Quaternion<dtype>::Quaternion(const Quaternion<dtype>& q)
	: a(q.a), b(q.b), c(q.c), d(q.d)
{
}

// Casts
template<class dtype>
Vector<dtype, 4> vector_cast(const Quaternion<dtype>& q)
{
	return Vector<dtype, 4>(q.b, q.c, q.d, q.a);
}

template <class dtype> 
Matrix<dtype, 4, 4> rot_matrix_cast(const Quaternion<dtype>& q)
{
	Matrix<dtype, 4, 4> result;
	dtype ab = q.a * q.b;
	dtype ac = q.a * q.c;
	dtype ad = q.a * q.d;
	dtype bc = q.b * q.c;
	dtype bd = q.b * q.d;
	dtype cd = q.c * q.d;

	dtype mbb = -q.b * q.b;
	dtype mcc = -q.c * q.c;
	dtype mdd = -q.d * q.d;

	result(0, 0) = static_cast<dtype>(1) + static_cast<dtype>(2) * (mcc + mdd);
	result(0, 1) = static_cast<dtype>(2) * (bc - ad);
	result(0, 2) = static_cast<dtype>(2) * (ac - bd);

	result(1, 0) = static_cast<dtype>(2) * (ad + bc);
	result(1, 1) = static_cast<dtype>(1) + static_cast<dtype>(2) * (mbb + mdd);
	result(1, 2) = static_cast<dtype>(2) * (cd - ab);

	result(2, 0) = static_cast<dtype>(2) * (bd - ac);
	result(2, 1) = static_cast<dtype>(2) * (ab + cd);
	result(2, 2) = static_cast<dtype>(1) + static_cast<dtype>(2) * (mbb + mcc);

	result(3, 3) = static_cast<dtype>(1);

	return result;
}

// Casts
template<class dtype>
Quaternion<dtype> quaternion_cast(const Matrix<dtype, 4, 4>& m)
{
	dtype a = sqrt(static_cast<dtype>(1) + m(0, 0) + m(1, 1) + m(2, 2)) / static_cast<dtype>(2);
	dtype a4 = static_cast<dtype>(4) * a;
	Quaternion<dtype> result(
		a,
		(m(2, 1) - m(2, 1)) / a4,
		(m(0, 2) - m(2, 0)) / a4,
		(m(1, 0) - m(0, 1)) / a4
	);
	return result;
}

// Accessors
template<class dtype>
dtype Quaternion<dtype>::scalar() const
{
	return a;
}

template<class dtype>
Vector<dtype, 3> Quaternion<dtype>::vector() const
{
	return Vector<dtype, 3>(std::array<dtype, 3> {b, c, d});
}

// Misc
template<class dtype>
dtype Quaternion<dtype>::norm() const
{
	return sqrt(squared_norm());
}

template<class dtype>
dtype Quaternion<dtype>::squared_norm() const
{
	return a * a + b * b + c * c + d * d;
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::get_conjugate() const
{
	return Quaternion<dtype>(a, -b, -c, -d);
}

// Rotations
template<class dtype>
Quaternion<dtype> Quaternion<dtype>::rotate_quaternion(const Vector<dtype, 3>& axis, const dtype angle)
{
	dtype s = static_cast<dtype>(sin(angle / 2));
	return 	Quaternion<dtype>(cos(angle / 2), axis.normalized() * s);
}

template<class dtype>
Quaternion<float> Quaternion<dtype>::getRotationQuaternion(float pitch, float yaw, float roll)
{

	double cy = cos(roll * 0.5);
	double sy = sin(roll * 0.5);
	double cp = cos(yaw * 0.5);
	double sp = sin(yaw * 0.5);
	double cr = cos(pitch * 0.5);
	double sr = sin(pitch * 0.5);

	Quaternion<float> result(
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy);

	return result;
}

template<class dtype>
Matrix<float, 4, 4> Quaternion<dtype>::getRotationMatrix(float pitch, float yaw, float roll)
{
	return rot_matrix_cast(getRotationQuaternion(pitch, yaw, roll));
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::setLookAtQuaternion(const Vector<float, 3>& direction, const Vector<float, 3>& up)
{
	return Quaternion<dtype>();
}

template<class dtype>
dtype Quaternion<dtype>::pitch()
{
	return static_cast<dtype>(
		atan2(static_cast<dtype>(2) * (a * b + c * d), 
			  static_cast<dtype>(1) - static_cast<dtype>(2) * (b * b + c * c)));
}

template<class dtype>
dtype Quaternion<dtype>::yaw()
{
	dtype sinp = static_cast<dtype>(2) * (a * c - d * b);
	if (abs(sinp) >= static_cast<dtype>(1))
		return static_cast<dtype>(copysign(static_cast<dtype>(PI / 2.0f), sinp)); // use 90 degrees if out of range
	else
		return static_cast<dtype>(asin(sinp));
}

template<class dtype>
dtype Quaternion<dtype>::roll()
{
	return static_cast<dtype>(
		atan2(static_cast<dtype>(2) * (a * d + b * c), 
			  static_cast<dtype>(1) - static_cast<dtype>(2) * (c * c + d * d)));
}

// + -
template<class dtype>
inline Quaternion<dtype> Quaternion<dtype>::operator+(const dtype x) const
{
	return Quaternion<dtype>(a + x, b, c, d);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator-(const dtype x) const
{
	return Quaternion<dtype>(a - x, b, c, d);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator+(const Quaternion<dtype>& x) const
{
	return Quaternion<dtype>(a + x.a, b + x.b, c + x.c, d + x.d);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator-(const Quaternion<dtype>& x) const
{
	return Quaternion<dtype>(a - x.a, b - x.b, c - x.c, d - x.d);
}

// * /
template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator*(const dtype x) const
{
	return Quaternion<dtype>(a * x, b * x, c * x, d * x);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator/(const dtype x) const
{
	return Quaternion<dtype>(a / x, b / x, c / x, d / x);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator*(const Quaternion<dtype>& x) const
{
	return Quaternion<dtype>(
		a * x.a - b * x.b - c * x.c - d * x.d, 
		a * x.b + b * x.a + c * x.d - d * x.c, 
		a * x.c - b * x.d + c * x.a + d * x.b, 
		a * x.d + b * x.c - c * x.b + d * x.a);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator/(const Quaternion<dtype>& x) const
{
	return this->operator*(x.inverse());
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::operator*(const Matrix<dtype, 4, 4>& m) const
{
	return quaternion_cast(vector_cast(*this) * m);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::cross_product(const Quaternion<dtype>& x) const
{
	//return ((*this) * x - x * (*this)) * (1 / 2);
	return Quaternion<dtype>(a * x.a, c * x.d - d * x.c, d * x.b - b * x.d, b * x.c - c * x.b);
}

template<class dtype>
Quaternion<dtype> Quaternion<dtype>::inverse() const
{
	return this->get_conjugate() / squared_norm();
}

// Asignement op
template<class dtype>
void Quaternion<dtype>::operator+=(const dtype x)
{
	a += x;
}

template<class dtype>
void Quaternion<dtype>::operator-=(const dtype x)
{
	a -= x;
}

template<class dtype>
void Quaternion<dtype>::operator+=(const Quaternion<dtype>& x)
{
	a += x.a;
	b += x.b;
	c += x.c;
	d += x.d;
}

template<class dtype>
void Quaternion<dtype>::operator-=(const Quaternion<dtype>& x)
{
	a -= x.a;
	b -= x.b;
	c -= x.c;
	d -= x.d;
}

template<class dtype>
void Quaternion<dtype>::operator*=(const Quaternion<dtype>& x)
{
	a = a * x.a - b * x.b - c * x.c - d * x.d;
	b = a * x.b + b * x.a + c * x.d - d * x.c;
	c = a * x.c - b * x.d + c * x.a + d * x.b;
	d = a * x.d + b * x.c - c * x.b + d * x.a;
}

template<class dtype>
void Quaternion<dtype>::operator/=(const Quaternion<dtype>& x)
{
	(*this) *= x.inverse();
}

template<class dtype>
void Quaternion<dtype>::operator*=(const dtype x)
{
	a *= x;
	b *= x;
	c *= x;
	d *= x;
}

template<class dtype>
void Quaternion<dtype>::operator/=(const dtype x)
{
	a /= x;
	b /= x;
	c /= x;
	d /= x;
}

template<class dtype>
void Quaternion<dtype>::operator=(const Quaternion<dtype>& x)
{
	a = x.a;
	b = x.b;
	c = x.c;
	d = x.d;
}

template<class dtype>
void Quaternion<dtype>::conjugate()
{
	b = -b;
	c = -c;
	d = -d;
}

// Usual quaternion
template<class dtype>
constexpr Quaternion<dtype> Quaternion<dtype>::i()
{
	return Quaternion<dtype>(0, 1, 0, 0);
}

template<class dtype>
constexpr Quaternion<dtype> Quaternion<dtype>::j()
{
	return Quaternion<dtype>(0, 0, 1, 0);
}

template<class dtype>
constexpr Quaternion<dtype> Quaternion<dtype>::k()
{
	return Quaternion<dtype>(0, 0, 0, 1);
}

template<class dtype>
void Quaternion<dtype>::print() const
{
	std::cout << a << " + " << "i."<< b << " + j."<< c << " + k." << d << std::endl;
}


#endif // !QUATERNION_CPP
