//#ifndef TENSOR_CPP
//#define TENSOR_CPP
//
//#include "Tensor.h"
//
//using namespace std;
//
//// Constructors
//template<class dtype, size_t ...shape>
//Tensor<dtype, shape...>::Tensor()
//	: shape_array(array<size_t, sizeof...(shape)>{shape...}), content(array<dtype, product(shape...)>())
//{
//	permutation = array<unsigned int, sizeof...(shape)>();
//	for (unsigned int i = 0; i < sizeof...(shape); i++) {
//		permutation[i] = i;
//	}
//}
//
//template<class dtype, size_t ... shape>
//Tensor<dtype, shape...>::Tensor(dtype filled_element)
//	: Tensor<dtype, shape...>()
//{
//	this->content.fill(filled_element);
//}
//
//template<class dtype, size_t ... shape>
//Tensor<dtype, shape...>::Tensor(const array<dtype, product(shape...)>& content)
//	: shape_array(array<size_t, sizeof...(shape)>{shape...}), content(content)
//{
//	permutation = array<unsigned int, sizeof...(shape)>();
//	for (unsigned int i = 0; i < sizeof...(shape); i++) {
//		permutation[i] = i;
//	}
//}
//
//template<class dtype, size_t ... shape>
//Tensor<dtype, shape...>::Tensor(const Tensor<dtype, shape...>& tensor)
//	: Tensor<dtype, shape...>(tensor.content)
//{
//}
//
//// Misc
//template<class dtype, size_t ...shape>
//void Tensor<dtype, shape...>::transpose(array<size_t, 2>& _permutation)
//{
//	static_assert(sizeof...(shape) == 2, "Transposition is only supported by Matrix like object.");
//	permutation = _permutation;
//}
//
//// Accessors
//template<class dtype, size_t ... shape>
//array<unsigned int, sizeof...(shape)> Tensor<dtype, shape...>::getShape() const
//{
//	return shape_array;
//}
//
////template<class dtype, size_t ...shape>
////template <size_t index_size>
////dtype& Tensor<dtype, shape...>::get(const array<unsigned int, index_size>& indexes)
////{
////	unsigned int d = sizeof...(shape);
////	unsigned int index = 0;
////	// Compute the position in the content
////	unsigned int current = 1;
////	for (int i = d-1; i >= 0; i--) {
////		index += indexes[permutation[i]] * current;
////		current *= shape_array[i];
////	}
////	return this->content[index];
////}
////
////template<class dtype, size_t ...shape>
////template<size_t index_size>
////const dtype& Tensor<dtype, shape...>::get(const array<size_t, index_size>& indexes) const
////{
////	unsigned int d = sizeof...(shape);
////	unsigned int index = 0;
////	// Compute the position in the content
////	unsigned int current = 1;
////	for (int i = d - 1; i >= 0; i--) {
////		index += indexes[permutation[i]] * current;
////		current *= shape_array[i];
////	}
////	return this->content[index];
////}
////
////template<class dtype, size_t ...shape>
////template <Indexes ...I>
////dtype& Tensor<dtype, shape...>::get(I ...indexes)
////{	
////	array <unsigned int, sizeof...(indexes)> arr = { indexes... };
////	return this->get(arr);
////}
////
////template<class dtype, size_t ...shape>
////template<Indexes ...I>
////const dtype& Tensor<dtype, shape...>::get(I ...indexes) const
////{
////	array <unsigned int, sizeof...(indexes)> arr = { indexes... };
////	return this->get(arr);
////}
////
////template<class dtype, size_t ... shape>
////template<Indexes ...I>
////dtype& Tensor<dtype, shape...>::operator()(I ...indexes)
////{
////	return this->get(indexes...);
////}
////
////template<class dtype, size_t ...shape>
////template<Indexes ...I>
////const dtype& Tensor<dtype, shape...>::operator()(I ...indexes) const
////{
////	return this->get(indexes...);
////}
//
//// + -
//template<class dtype, size_t ...shape>
//template <template <typename, size_t ...> class T>
//T<dtype, shape...> Tensor<dtype, shape...>::operator+(const T<dtype, shape...>& other) const
//{
//	T<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = this->content[i] + other.content[i];
//	}
//
//	return T<dtype, shape...>(result); // Not very cool but it works
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//T<dtype, shape...> Tensor<dtype, shape...>::operator-(const T<dtype, shape...>& other) const
//{
//	T<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = content[i] - other.content[i];
//	}
//	return T<dtype, shape...>(result);
//}
//
//// * /
//template <class dtype, size_t ... shape>
//Tensor<dtype, shape...> Tensor<dtype, shape...>::operator*(const dtype x) const
//{
//	Tensor<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = this->content[i] * x;
//	}
//	return Tensor<dtype, shape...>(result);
//}
//
//template<class dtype, size_t ...shape>
//template <template <typename, size_t ...> class T>
//T<dtype, shape...> Tensor<dtype, shape...>::operator*(const T<dtype, shape...>& other) const
//{
//	T<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = this->content[i] * other.content[i];
//	}
//
//	return T<dtype, shape...>(result);
//}
//
//template <class dtype, size_t ... shape>
//Tensor<dtype, shape...> Tensor<dtype, shape...>::operator/(const dtype x) const
//{
//	Tensor<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = this->content[i] / x;
//	}
//
//	return Tensor<dtype, shape...>(result);
//}
//
//template<class dtype, size_t ...shape>
//template <template <typename, size_t ...> class T>
//T<dtype, shape...> Tensor<dtype, shape...>::operator/(const T<dtype, shape...>& other) const
//{
//	T<dtype, shape...> result;
//	for (int i = 0; i < this->content.size(); i++) {
//		result.content[i] = this->content[i] / other.content[i];
//	}
//
//	return T<dtype, shape...>(result);
//}
//
//// Asignement ops
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//bool Tensor<dtype, shape...>::operator==(const T<dtype, shape...>& other) const
//{
//	return this->getShape() == other.getShape() && content == other.content;
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T, class dtype_2, size_t ... shape_2>
//bool Tensor<dtype, shape...>::operator!=(const T<dtype_2, shape_2...>& other) const
//{
//	return this->getShape() != other.getShape() || content != other.content;
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//void Tensor<dtype, shape...>::operator=(T<dtype, shape...>& other)
//{
//	content = other.content;
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//void Tensor<dtype, shape...>::operator+=(const T<dtype, shape...>& other)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] += other.content[i];
//	}
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//void Tensor<dtype, shape...>::operator-=(const T<dtype, shape...>& other)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] -= other.content[i];
//	}
//}
//
//template <class dtype, size_t ... shape>
//void Tensor<dtype, shape...>::operator*=(const dtype x)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] *= x;
//	}
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//void Tensor<dtype, shape...>::operator*=(const T<dtype, shape...>& other)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] *= other.content[i];
//	}
//}
//
//template <class dtype, size_t ... shape>
//void Tensor<dtype, shape...>::operator/=(const dtype x)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] /= x;
//	}
//}
//
//template <class dtype, size_t ... shape>
//template <template <typename, size_t ...> class T>
//void Tensor<dtype, shape...>::operator/=(const T<dtype, shape...>& other)
//{
//	for (unsigned int i = 0; i < this->content.size(); i++) {
//		this->content[i] /= other.content[i];
//	}
//}
//
//// Display
//template <class dtype, size_t ... shape>
//void Tensor<dtype, shape...>::print()
//{
//	unsigned int d = this->getShape().size();
//
//	// Store the "advancement" of shape
//	array<unsigned int, sizeof...(shape)> state = {0};
//
//	// Open all necessary brackets
//	for (int _ = 0; _ < d; _++) {
//		cout << "[";
//	}
//
//	for (int i = 0; i < this->content.size(); i++) {
//		cout << this->get(state);
//		state[d - 1] += 1;
//		if (state[d - 1] % this->getShape()[d-1] != 0) { // this->permutations[d - 1]
//			cout << ", ";
//		}
//		// Check if a shape is ending
//		int k = d-1;
//		int c = 0;
//		while (k > 0 && (state[k] != 0) && (state[k] % this->getShape()[k] == 0)) { // this->permutations[k]
//			state[k] = 0;
//			state[k - 1] += 1;
//			cout << "]";
//			k--;
//			c++;
//		}
//		if (c > 0 && (state[0] == 0 || state[0] % this->getShape()[0] != 0)) { // this->permutations[0]
//			cout << endl;
//		}
//		for (int _ = 0; _ < c; _++) {
//			if (state[0] == 0 || state[0] % this->getShape()[0] != 0) { // this->permutations[0]
//				cout << "[";
//			}
//		}
//	}
//	cout << "]" << endl;
//}
//
//#endif