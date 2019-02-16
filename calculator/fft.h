#pragma once
#include <iostream>
#include "Complex.h"
#include <vector>
#include <algorithm>
#define NOMINMAX

#define PI  3.141592653589793238460

class FFT {
private:
	std::vector<Complex> x;

	void Fft(bool isInverse);
	void bitRev(size_t n);

public:
	FFT(std::vector<Complex> x);

	std::vector<Complex> fft();
	std::vector<Complex> ifft();

	size_t size();

	// 項別演算
	friend FFT operator*(FFT x, FFT y) {
		size_t max = std::max(x.x.size(), y.x.size());
		std::vector<Complex> mul(max);
		for(size_t i = 0; i < max; i++) {
			if(i >= x.x.size() || i >= y.x.size()) mul[i] = 0;
			else mul[i] = x.x[i] * y.x[i];
		}
		
		return FFT(mul);
	}

	// アクセス
	Complex operator[](size_t n) {
		return this->x[n];
	}
};
