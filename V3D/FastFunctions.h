#ifndef FASTFUNCTIONS_H
#define FASTFUNCTIONS_H
#pragma once

#include <algorithm>
#include "Constants.h"

float fast_rsqrt(float number);
float fast_sqrt(float number);

template<class T>
float fast_pow(T number, size_t n);
template<class T>
T fast_exp(T x);

template<class T>
T taylor_cos(const T x);
template<class T>
T fast_cos(const T x);
template<class T>
T fast_sin(const T x);

#include "FastFunctions.cpp"

#endif 
