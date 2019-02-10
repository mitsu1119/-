#pragma once
#include <iostream>
#include <complex>
#include <valarray>
#include <algorithm>

#define PI  3.141592653589793238460

typedef std::complex<double> Complex;

class FFT {
private:
	std::valarray<Complex> x;

	void Fft(std::valarray<Complex> &x);
	void Ifft(std::valarray<Complex> &x);

public:
	FFT(std::valarray<Complex> x);

	void setx(std::valarray<Complex> x);
	std::valarray<Complex> fft();
	std::valarray<Complex> ifft();

	void operator*=(FFT y) {
		this->x *= y.x;
	}
};
