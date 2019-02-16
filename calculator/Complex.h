#pragma once
#include <ostream>
#include <cmath>

class Complex {
private:
	long double re, im;

	template <typename T>
	void add(const T &x) {
		this->re += x;
	}

	template <typename T>
	void sub(const T &x) {
		this->re -= x;
	}

	template <typename T>
	void mul(const T &x) {
		this->re *= x;
	}
	
	template <typename T>
	void div(const T &x) {
		this->re /= x;
	}

	template <>
	void add(const Complex &x) {
		this->re += x.real();
		this->im += x.imag();
	}

	template <>
	void sub(const Complex &x) {
		this->re -= x.real();
		this->im -= x.imag();
	}

	template <>
	void mul(const Complex &x) {
		long double a = real();
		long double b = imag();

		this->re = a * x.real() - b * x.imag();
		this->im = a * x.imag() + b * x.real();
	}

	template <>
	void div(const Complex &x) {
		Complex xx = x;
		xx.im = -xx.imag();
		mul(xx);
		this->re /= (x.real() * x.real() + x.imag() * x.imag());
		this->im /= (x.real() * x.real() + x.imag() * x.imag());
	}

public:
	Complex(long double real, long double imag);
	Complex();

	long double real() const;
	long double imag() const;

	bool isRealNum();
	bool isPurelyImagNum();

	friend std::ostream &operator<<(std::ostream &os, Complex x) {
		os << x.real() << "+" << x.imag() << "i";
		return os;
	}

	template <typename T>
	Complex operator+=(const T &x) {
		add(x);
		return *this;
	}

	template <typename T>
	Complex operator-=(const T &x) {
		sub(x);
		return *this;
	}

	template <typename T>
	Complex operator*=(const T &x) {
		mul(x);
		return *this;
	}

	template <typename T>
	Complex operator/=(const T &x) {
		div(x);
		return *this;
	}

	template <typename T>
	friend Complex operator+(T x, const T &y) {
		x.add(y);
		return x;
	}

	template <typename T>
	friend Complex operator-(T x, const T &y) {
		x.sub(y);
		return x;
	}

	template <typename T>
	friend Complex operator*(T x, const T &y) {
		x.mul(y);
		return x;
	}

	template <typename T>
	friend Complex operator/(T x, const T &y) {
		x.div(y);
		return x;
	}

	template <typename T>
	void operator=(const T &x) {
		this->re = (long double)x;
		this->im = 0;
	}

	template <>
	void operator=(const Complex &x) {
		this->re = x.real();
		this->im = x.imag();
	}
};

namespace Comp {
	Complex exp(Complex x);
}
