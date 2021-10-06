//#ifndef TENSOR_H
//#define TENSOR_H
//#pragma once
//
//#include "Utils.h"
//#include <array>
//#include <iostream>
//#include <stdexcept>
//
//using namespace std;
//
//template <class dtype, size_t size>
//class Vector;
//
//template <class dtype, size_t rows, size_t cols>
//class Matrix;
//
//template <class dtype, size_t ... shape>
//class Tensor;
//
//template<typename T>
//concept Indexes = is_convertible<T, size_t>::value;
//
//template <class dtype, size_t ... shape>
//class Tensor
//{ 
//public:
//	// Constructors
//	Tensor<dtype, shape...>(); 
//	Tensor<dtype, shape...>(dtype filled_element);
//	Tensor<dtype, shape...>(const array<dtype, product(shape...)>& content);
//	Tensor<dtype, shape...>(const Tensor<dtype, shape...> &tensor);
//
//	// Misc
//	void transpose(array<size_t, 2>& _permutation);
//
//	// Accessors	
//	array<unsigned int, sizeof...(shape)> getShape() const;
//
//	/*template <size_t index_size>
//	dtype& get(const array<size_t, index_size>& indexes);
//
//	template <size_t index_size>
//	const dtype& get(const array<size_t, index_size>& indexes) const;
//
//	template <Indexes ...I>
//	dtype& get(I ...indexes);
//
//	template <Indexes ...I>
//	const dtype& get(I ...indexes) const;
//
//	template <Indexes ...I>
//	dtype& operator()(I ...indexes);
//
//	template <Indexes ...I>
//	const dtype& operator()(I ...indexes) const;*/
//
//	// + -
//	template <template <typename, size_t ...> class T>
//	T<dtype, shape...> operator+(const T<dtype, shape...>& other) const;
//
//	template <template <typename, size_t ...> class T>
//	T<dtype, shape...> operator-(const T<dtype, shape...>& other) const;
//
//	// * /
//	Tensor<dtype, shape...> operator*(const dtype x) const;
//	template <template <typename, size_t ...> class T>
//	T<dtype, shape...> operator*(const T<dtype, shape...>& other) const;
//
//	Tensor<dtype, shape...> operator/(const dtype x) const;
//	template <template <typename, size_t ...> class T>
//	T<dtype, shape...> operator/(const T<dtype, shape...>& other) const;
//
//	// equals
//	template <template <typename, size_t ...> class T>
//	bool operator==(const T<dtype, shape...>& other) const;
//
//	template <template <typename, size_t ...> class T, class dtype_2, size_t ... shape_2>
//	bool operator!=(const T<dtype_2, shape_2...>& other) const;
//
//	template <template <typename, size_t ...> class T>
//	void operator=(T<dtype, shape...>& other);
//
//	// asignement op
//	template <template <typename, size_t ...> class T>
//	void operator+=(const T<dtype, shape...>& other);
//
//	template <template <typename, size_t ...> class T>
//	void operator-=(const T<dtype, shape...>& other);
//
//	void operator*=(dtype x);
//	template <template <typename, size_t ...> class T>
//	void operator*=(const T<dtype, shape...>& other);
//
//	void operator/=(dtype x);
//	template <template <typename, size_t ...> class T>
//	void operator/=(const T<dtype, shape...>& other);
//
//	// Display
//	void print();
//protected:
//	template <template <typename, size_t ...> class T, size_t ...shape_2>
//
//	array<unsigned int, sizeof...(shape)> shape_array;
//	array<dtype, product(shape...)> content;
//	array<unsigned int, sizeof...(shape)> permutation;
//};
//
//#include "Tensor.cpp"
//#endif
