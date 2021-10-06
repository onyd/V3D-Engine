#ifndef FFT_CPP
#define FFT_CPP

#include "FFT.h"

int reverseBits(int q, int k)
{
    int m = 0;
    for (int b = 0; b < q; b++) {
        m = m | (k & 1);
        m = m << 1;
        k = k >> 1;
    }
    m = m >> 1;
    return m;
}

void sortReversedBits(int q, std::vector<std::complex<double>> &x, std::vector<std::complex<double>>& y)
{
    int N = pow(2, q);
    for (int k = 0; k < N; k++) {
        int m = reverseBits(q, k);
        y[m] = x[k];
    }

}

void fftStep(std::vector<std::complex<double>>& x, std::vector<std::complex<double>>& y, int q, int e)
{
    int ne = pow(2, e);
    int nem1 = ne / 2;
    for (int k = 1; k < nem1; k++) {
        double phi = 2 * PI * k / ne;
        std::complex<double> W(cos(phi), sin(phi));
        for (int i = 0; i < pow(2, (q - e)); i++) { // boucle sur les paquets de ne termes
            int h = i * ne; // premier indice du paquet
            y[h + k] = x[h + k] + W * x[h + k + nem1];
            y[h + ne - k] = x[h + ne - k - nem1] + conj(W) * x[h + ne - k];
        }
    }

    for (int i = 0; i < pow(2, (q - e)); i++) {
        int h = i * ne;
        y[h] = x[h] + x[h + nem1];
        y[h + nem1] = x[h] - x[h + nem1];
    }
}

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &u, int q)
{
    std::vector<std::complex<double>> x = u;
    std::vector<std::complex<double>> y(pow(2, q), std::complex<double>(0., 0.));
    sortReversedBits(q, x, y);
    std::vector<std::complex<double>> z = x;
    x = y;
    y = z;
    for (int e = 1; e < q + 1; e++) {
        fftStep(x, y, q, e);
        z = x;
        x = y;
        y = z;
    }
    return x;
}

#endif 
