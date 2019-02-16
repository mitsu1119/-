#include "Complex.h"

Complex Comp::exp(Complex x) {
	if(x.isRealNum()) return Complex(std::exp(x.real()), 0);

	return Complex(std::exp(x.real()) * std::cos(x.imag()), std::exp(x.real()) * std::sin(x.imag()));
}

Complex::Complex():re(0), im(0) {
}

Complex::Complex(long double real, long double imag) : re(real), im(imag) {
}

long double Complex::real() const {
	return this->re;
}

long double Complex::imag() const {
	return this->im;
}

bool Complex::isRealNum() {
	return (imag() == 0);
}

bool Complex::isPurelyImagNum() {
	return (real() == 0);
}
