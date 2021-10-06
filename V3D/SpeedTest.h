#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <random>

using namespace std;
using namespace std::chrono;


static class SpeedTest {
public:
	static void startPoint(const string& name) {
		start = high_resolution_clock::now();
	};

	static void stopPoint(const string& name) {
		dt = duration_cast<microseconds>(high_resolution_clock::now() - start).count();
	};

	static void printTime(const string& name) {
		cout << "The time taken for : " << name << "SpeedTest is " << dt << " microseconds" << endl;
	};

	template<class T>
	static void amortizedTime(function<void(T)> f, const string& name, T min, T max, unsigned int N = 100) {
		default_random_engine generator;
		uniform_real_distribution<T> distribution(min, max);

		long time = 0;
		for (unsigned int i = 0; i < N; i++) {
			T x = distribution(generator);
			auto t1 = high_resolution_clock::now();
			f(x);
			auto t2 = high_resolution_clock::now();
			time += duration_cast<microseconds>(t2 - t1).count();
		}
		cout << "The time taken by function: " << name << " is " << time / N << " microseconds" << endl;
	};

	template<class T, size_t N>
	static void accumulatedTime(function<void(T)> f, const string& name, T min, T max) {
		default_random_engine generator;
		uniform_real_distribution<T> distribution(min, max);

		array<T, N> values;
		for (unsigned int i = 0; i < N; i++) {
			values[i] = distribution(generator);
		}

		auto t1 = high_resolution_clock::now();
		for (unsigned int i = 0; i < N; i++) {
			f(values[i]);
		}
		auto t2 = high_resolution_clock::now();

		cout << "The time taken by function: " << name << " is " << duration_cast<microseconds>(t2 - t1).count() << " microseconds" << endl;
	};

private:
	static string name;
	static long dt;
	static time_point<high_resolution_clock> start;

};