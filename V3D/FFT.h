#ifndef FFT_H
#define FFT_H
#pragma once

#include <vector>
#include <complex>
#include <cmath>
#include "Constants.h"

int reverseBits(int q, int k);
void sortReversedBits(int q, std::vector<std::complex<double>>& x, std::vector<std::complex<double>>& y);
void fftStep(std::vector<std::complex<double>>& x, std::vector<std::complex<double>>& y, int q, int e);
std::vector<std::complex<double>> fft(std::vector<std::complex<double>>& u, int q);




#endif // !FFT_H
