#ifndef ARRAYOPS_H
#define ARRAYOPS_H
#pragma once

#include <array>
#include <iostream>

// Product of elements
template<class T, size_t N>
constexpr size_t product(const std::array<T, N>& t);

// Sum of elements
template<class T, size_t N>
constexpr T sum(const std::array<T, N>& t);

// Ops with constant
template<class T, size_t N>
constexpr std::array<T, N> constantSum(const std::array<T, N>& t1, const T value);

template<class T, size_t N>
constexpr std::array<T, N> constantSubstraction(const std::array<T, N>& t1, const T value);

template<class T, size_t N>
constexpr std::array<T, N> constantProduct(const std::array<T, N>& t1, const T value);

template<class T, size_t N>
constexpr std::array<T, N> constantDivision(const std::array<T, N>& t1, const T value);

// Element wise + - * /
template<class T, size_t N>
constexpr std::array<T, N> elementSum(const std::array<T, N>& t1, const std::array<T, N>& t2);

template<class T, size_t N>
constexpr std::array<T, N> elementSubstraction(const std::array<T, N>& t1, const std::array<T, N>& t2);

template<class T, size_t N>
constexpr std::array<T, N> elementProduct(const std::array<T, N>& t1, const std::array<T, N>& t2);

template<class T, size_t N>
constexpr std::array<T, N> elementDivision(const std::array<T, N>& t1, const std::array<T, N>& t2);

// Tensor like display std::array with row-major convention
template <class T, size_t N, size_t S>
inline T rowMajorGet(const std::array<T, N>& t, const std::array<size_t, S>& array_shape, const std::array<size_t, S>& indexes);

template <class T, size_t N, size_t S>
void tensor_print(const std::array<T, N>& t, const std::array<size_t, S>& array_shape);

// ------Implementations------
template<class T, size_t N>
inline constexpr size_t product(const std::array<T, N>& t)
{
	T result;
	for (size_t i = 0; i < N; i++) {
		result *= t[i];
	}
}

template<class T, size_t N>
inline constexpr T sum(const std::array<T, N>& t)
{
	T result = 0;
	for (int i = 0; i < N; i++) {
		result += t[i];
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> constantSum(const std::array<T, N>& t1, const T value)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] + value;
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> constantSubstraction(const std::array<T, N>& t1, const T value)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] - value;
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> constantProduct(const std::array<T, N>& t1, const T value)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] * value;
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> constantDivision(const std::array<T, N>& t1, const T value)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] / value;
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> elementSum(const std::array<T, N>& t1, const std::array<T, N>& t2)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] + t2[i];
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> elementSubstraction(const std::array<T, N>& t1, const std::array<T, N>& t2)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] - t2[i];
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> elementProduct(const std::array<T, N>& t1, const std::array<T, N>& t2)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] * t2[i];
	}
	return result;
}

template<class T, size_t N>
inline constexpr std::array<T, N> elementDivision(const std::array<T, N>& t1, const std::array<T, N>& t2)
{
	std::array<T, N> result;
	for (size_t i = 0; i < N; i++) {
		result[i] = t1[i] / t2[i];
	}
	return result;
}

template<class T, size_t N, size_t S>
inline T rowMajorGet(const std::array<T, N>& t, const std::array<size_t, S>& array_shape, const std::array<size_t, S>& indexes)
{
	size_t index = 0;
	// Compute the position in the content
	size_t current = 1;
	for (int i = S - 1; i >= 0; i--) {
		index += indexes[i] * current;
		current *= array_shape[i];
	}
	return t[index];
}

// Display
template <class T, size_t N, size_t S>
void tensor_print(const std::array<T, N>& t, const std::array<size_t, S>& array_shape)
{
	// Store the "advancement" of indexes
	std::array<size_t, S> state = { 0 };

	// Open all necessary brackets
	for (int _ = 0; _ < S; _++) {
		std::cout << "[";
	}

	for (int i = 0; i < N; i++) {
		std::cout << rowMajorGet(t, array_shape, state);
		state[S - 1] += 1;
		if (state[S - 1] % array_shape[S - 1] != 0) { 
			std::cout << ", ";
		}
		// Check if a shape is ending
		int k = S - 1;
		int c = 0;
		while (k > 0 && (state[k] != 0) && (state[k] % array_shape[k] == 0)) { 
			state[k] = 0;
			state[k - 1] += 1;
			std::cout << "]";
			k--;
			c++;
		}
		if (c > 0 && (state[0] == 0 || state[0] % array_shape[0] != 0)) { 
			std::cout << std::endl;
		}
		for (size_t _ = 0; _ < c; _++) {
			if (state[0] == 0 || state[0] % array_shape[0] != 0) { 
				std::cout << "[";
			}
		}
	}
	std::cout << "]" << std::endl;
}
#endif
