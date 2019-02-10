#include "fft.h"

FFT::FFT(std::valarray<Complex> x):x(x) {
}

void FFT::setx(std::valarray<Complex> x) {
	this->x = x;
}

// �𒼂ȍċAFFT
void FFT::Fft(std::valarray<Complex> &x) {
	const size_t N = x.size();
	if(N <= 1) return;

	std::valarray<Complex> even = x[std::slice(0, N/2, 2)];
	std::valarray<Complex> odd = x[std::slice(1, N/2, 2)];

	Fft(even);
	Fft(odd);

	for(size_t k = 0; k < N/2; k++) {
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

void FFT::Ifft(std::valarray<Complex> &x) {
	x = x.apply(std::conj);
	Fft(x);

	x = x.apply(std::conj);
	x /= x.size();
}


std::valarray<Complex> FFT::fft() {
	Fft(this->x);
	return this->x;
}

std::valarray<Complex> FFT::ifft() {
	Ifft(this->x);
	return this->x;
}
