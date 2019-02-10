#include "fft.h"

FFT::FFT(std::vector<Complex> x):x(x) {
}

void FFT::Fft(bool isInverse) {
	size_t n = this->x.size();
	double angle = 2 * (isInverse ? -1 : 1) * PI / n;

	bitRev(n);
	for(size_t m, mh = 1; (m = mh << 1) <= n; mh = m) {
		int irev = 0;
		for(size_t i = 0; i < n; i += m) {
			Complex w = std::exp(Complex(0, angle*irev));
			for(size_t k = n >> 2; k >(irev ^= k); k >>= 1);
			for(size_t j = i; j < mh + i; j++) {
				size_t k = j + mh;
				Complex xx = this->x[j] - this->x[k];
				this->x[j] += this->x[k];
				this->x[k] = w * xx;
			}
		}
	}
}

void FFT::bitRev(size_t n) {
	for(int i = 0, j = 1; j < n - 1; j++) {
		for(size_t k = n >> 1; k > (i ^= k); k >>= 1);
		if(j < i) std::swap(this->x[i], this->x[j]);
	}
}

std::vector<Complex> FFT::fft() {
	Fft(false);
	return this->x;
}

std::vector<Complex> FFT::ifft() {
	Fft(true);
	for(size_t i = 0; i < this->x.size(); i++) this->x[i] /= (double)this->x.size();
	return this->x;
}

size_t FFT::size() {
	return this->x.size();
}
