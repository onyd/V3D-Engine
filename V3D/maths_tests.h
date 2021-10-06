#include "fft.h"
#include "vector.h"
#include "matrix.h"
#include "Quaternion.h"
#include "SpeedTest.h"
//#include "FastFunctions.h"

#include <string>
#include <iostream>
#include <chrono>
#include <array>

using namespace std::chrono;
using namespace std;

void fft_test() {
	int q = 8;
	int n = pow(2, q);
	vector<complex<double>> u(n, complex<double>(0., 0.));
	for (int k = 0; k < n; k++) {
		u[k] = sin(2 * PI * k / n) + 0.5 * sin(
			4 * PI * k / n) + 0.25 * cos(10 * PI * k / n);
	}
	vector<complex<double>> tfd = fft(u, q);

	for (int i = 0; i < tfd.size(); i++) {
		cout << abs(tfd[i]) << ", ";
	}
	cout << endl;
}

void vector_tests() {
	Vector<int, 4> t1;
	Vector<int, 4> t2(2);

	t1[0] = 4;
	t1[1] = 4;
	t1[2] = 4;

	cout << "t1 = " << endl;
	t1.print();
	cout << "t2 = " << endl;
	t2.print();

	cout << endl << "Add two vectors: " << endl;
	Vector<int, 4> t_add = t1 + t2;
	t_add.print();

	cout << "Substract two vectors: " << endl;
	Vector<int, 4> tc_sub = t1 - t2;
	tc_sub.print();

	cout << "Constant mult vector by 2: " << endl;
	Vector<int, 4> tc_mult = t1 * 2;
	tc_mult.print();

	cout << "Constant div vector by 2: " << endl;
	Vector<int, 4> tc_div = t1 / 2;
	tc_div.print();

	cout << "Vector element-wise mult: " << endl;
	Vector<int, 4> tt_mult = t1 * t2;
	tt_mult.print();

	cout << "Vector element-wise div: " << endl;
	Vector<int, 4> tt_div = t1 / t2;
	tt_div.print();

}

void matrix_tests() {
	Matrix<int, 4, 4> t1;
	Matrix<int, 4, 4> t2(2);
	Vector<int, 4> v = array<int, 4> {1, 2, 3, 4};

	t1(0, 0) = 4;
	t1(1, 0) = 4;
	t1(2, 0) = 4;

	cout << "t1 = " << endl;
	t1.print();
	cout << "t2 = " << endl;
	t2.print();
	cout << "v = " << endl;
	v.print();

	cout << endl << "Add two matricies: " << endl;
	Matrix<int, 4, 4> t_add = t1 + t2;
	t_add.print();

	cout << "Substract two matricies: " << endl;
	Matrix<int, 4, 4> tc_sub = t1 - t2;
	tc_sub.print();

	cout << "Constant mult matrix(t1) by 2: " << endl;
	Matrix<int, 4, 4> tc_mult = t1 * 2;
	tc_mult.print();

	cout << "Constant div matrix(t1) by 2: " << endl;
	Matrix<int, 4, 4> tc_div = t1 / 2;
	tc_div.print();

	cout << "Matrix element-wise mult: " << endl;
	Matrix<int, 4, 4> tt_mult = t1 * t2;
	tt_mult.print();

	cout << "Matrix element-wise div: " << endl;
	Matrix<int, 4, 4> tt_div = t1 / t2;
	tt_div.print();

	cout << "Matrix(t2) matmul Vector: " << endl;
	Vector<int, 4> tt_matv = t2 * v;
	tt_matv.print();

	cout << "Vector matmul(t2) Matrix(t2): " << endl;
	Vector<int, 4> tt_vmat = v * t2;
	tt_vmat.print();

	cout << "Matrix matmul Matrix: " << endl;
	Matrix<int, 4, 4> tt_mmat = t1.matmul(t2);
	tt_mmat.print();

}

void quaternion_tests() {
	Quaternion<float> q1(1, 1, 1, 1);
	Quaternion<float> q2(1, 2, 3, 4);

	cout << endl << "Add two Quaternions: " << endl;
	Quaternion<float> q_add = q1 + q2;
	q_add.print();

	cout << endl << "Sub two Quaternions: " << endl;
	Quaternion<float> q_sub = q1 - q2;
	q_sub.print();

	cout << endl << "Mult two Quaternions: " << endl;
	Quaternion<float> q_mult = q1 * q2;
	q_mult.print();

	cout << endl << "Div two Quaternions: " << endl;
	Quaternion<float> q_div = q1 / q2;
	q_div.print();

	cout << endl << "Mult Quaternion by const: " << endl;
	Quaternion<float> q_cmult = q2 * 2;
	q_cmult.print();

	cout << endl << "Div Quaternions by const: " << endl;
	Quaternion<float> q_cdiv = q2 / 2;
	q_cdiv.print();

	cout << endl << "Cross product Quaternions: " << endl;
	Quaternion<float> q_cross = q2.cross_product(q1);
	q_cross.print();
	cout << q_cross.vector().inner_product((q2.vector())) << endl;;

	cout << endl << "Re: " << endl;
	cout << q2.scalar() << endl;

	cout << endl << "Im: " << endl;
	q2.vector().print();

	cout << endl << "Norm: " << endl;
	cout << q2.norm() << endl;

}


void matmul_speed_tests() {
	Matrix<float, 10, 10> m1(1.0f);

	// Matrix
	auto start = high_resolution_clock::now();
	// Start code
	Matrix<float, 10, 10> r1 = m1.matmul(m1);
	// End code
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by Matrix: "
		<< duration.count() << " microseconds" << endl;
}

void fast_functions_tests() {
	/*cout << "fast_rsqrt(10.0): " << fast_rsqrt(10.0f) << endl;
	cout << "rsqrt(10.0): " << 1.0f / sqrtf(10.0f) << endl;

	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		1.0f / sqrtf(x);
		}, "rsqrt", 1.0f, 1000.0f);
	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		fast_rsqrt(x);
		}, "fast_rsqrt", 1.0f, 1000.0f);

	cout << endl << "fast_cos(10.0): " << fast_cos(10.0f) << endl;
	cout << "cos(10.0): " << cos(10.0f) << endl;

	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		cosf(x);
		}, "cos", 1.0f, 1000.0f);
	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		fast_cos(x);
		}, "fast_cos", 1.0f, 1000.0f);
	
	cout << endl << "fast_sin(10.0): " << fast_sin(10.0f) << endl;
	cout << "sin(10.0): " << sin(10.0f) << endl;

	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		sinf(x);
		}, "sin", 1.0f, 1000.0f);
	SpeedTest::accumulatedTime<float, 100000>([](float x) {
		fast_sin(x);
		}, "fast_sin", 1.0f, 1000.0f);*/
}