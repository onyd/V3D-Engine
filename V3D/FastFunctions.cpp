#ifndef FASTFUNCTIONS_CPP
#define FASTFUNCTIONS_CPP

#include "FastFunctions.h"

// Fast inverse square root from Quake3 algorithm
inline float fast_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y; // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1); // what the fuck?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	//	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

	return y;
}

inline float fast_sqrt(float number)
{
	return 1 / fast_rsqrt(number);
}

template<class T>
float fast_pow(T number, unsigned int n)
{
	int result = 1;
	while (n > 0) {
		// Odd
		if (result & 1)
			result *= number;

		n = n << 1; // halves n
		number *= number;
	}
	return result;
}

template<class T>
T fast_exp(T x)
{
	// Use exp approxiamation with limited development
	if (x > 0 && x < 1)
		return 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25 * (1.0f + x * 0.2f))));

	const float integerPart = floor(x);
	const float floatPart = x - integerPart;

	return fast_exp(floatPart) * fast_pow(e, integerPart);
}

// cos from Taylor series (from glm)
template<class T>
T taylor_cos(const T x)
{
	T x2 = x * x;
	return (T(0.9999932946) + x2 * (T(-0.4999124376) + x2 * (T(0.0414877472) + x2 * T(-0.0012712095))));
}

template<class T>
T fast_cos(const T x)
{
	T const angle(fmod(x, two_PI));

	if (angle < half_PI)
		return taylor_cos(angle);
	if (angle < PI)
		return -taylor_cos(PI - angle);
	if (angle < (T(3) * half_PI))
		return -taylor_cos(angle - PI);

	return taylor_cos(two_PI - angle);
}

template<class T>
T fast_sin(const T x)
{
	return fast_cos(half_PI - x);
}

#endif