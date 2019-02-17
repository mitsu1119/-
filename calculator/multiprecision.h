#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <valarray>
#include <iomanip>
#include "fft.h"
#include "Complex.h"
#define NOMINMAX

constexpr unsigned long BASE_MULTI = 100;	// base
constexpr int MAX_DIGIT_INDEX = 2;		// ˆê‚Â‚Ì—v‘f“à‚ÌÅ‘åŒ…
constexpr int MAX_DIGITS = 100;	// digit‚Ì”

class BigInt {
private:
	std::vector<unsigned long> digits;
	bool nan;

	void resize(size_t size);
	void pushUp(unsigned long num);
	void pushDown(unsigned long num);
	void rShift(size_t cnt);
	void lShift(size_t cnt);

	// ãˆÊŒ…‚Ì0‚ğÁ‹
	void normalize();

	// ˆê‚Â‚ÌŒ…‚Å‚ÌÅ‘å’l‚ğ’´‚¦‚Ä‚¢‚½‚çŸ‚ÌŒ…‚ğ‘«‚µ‚Ä‡‚í‚¹‚é
	void align();

	// xˆÈã‚Ì2^n‚ğ’T‚·
	size_t getNextPow2(size_t x);

	// ‰‰Z
	template <typename T>
	void unsignedAdd(const T &num);
	template <typename T>
	void unsignedMul(const T &num);

	template <>
	void unsignedAdd(const BigInt &num);
	template <>
	void unsignedMul(const BigInt &num);

	bool isEqual(const BigInt &num) const;

public:
	BigInt();
	BigInt(std::string i);

	void clear();
	bool isNan() const;
	size_t size() const;

	// operators
	friend std::ostream &operator<<(std::ostream &os, BigInt x) {
		if(x.isNan()) os << "NaN";
		else {
			os << x.digits[x.size() - 1];
			for(int i = (int)x.size() - 2; i >= 0; i--) os << std::setw(MAX_DIGIT_INDEX) << std::setfill('0') << x.digits[i];
		}
		return os;
	}

	friend std::istream &operator>>(std::istream &is, BigInt &x) {
		std::string s;
		is >> s;
		x = BigInt(s);
		return is;
	}

	template <typename T>
	BigInt &operator+=(const T &num) {
		unsignedAdd(num);
		return *this;
	}

	template <>
	BigInt &operator+=(const BigInt &num) {
		unsignedAdd(num);
		return *this;
	}

	template <typename T>
	BigInt &operator*=(const T &num) {
		unsignedMul(num);
		return *this;
	}

	template <>
	BigInt &operator*=(const BigInt &num) {
		unsignedMul(num);
		return *this;
	}

	friend bool operator==(const BigInt &left, const BigInt &right) {
		return left.isEqual(right);
	}
};

template <typename T>
void BigInt::unsignedAdd(const T &num) {
	if(isNan()) return;
	if(num == 0) return;

	this->digits[0] += num;
	align();
}

template <>
void BigInt::unsignedAdd(const BigInt &num) {
	if(isNan() || num.isNan()) return;
	if(num == BigInt("0")) return;

	if(size() < num.size()) resize(num.size());
	unsigned long buf, carry = 0;
	for(size_t i = 0; i < size(); i++) {
		buf = this->digits[i] + num.digits[i] + carry;
		carry = buf / BASE_MULTI;
		this->digits[i] = buf % BASE_MULTI;
	}

	if(carry != 0) pushUp(carry);
}

// •MZ‚ÌƒAƒ‹ƒSƒŠƒYƒ€
/*
void BigInt::unsignedMul(const BigInt &num) {
	if(isNan() || num.isNan()) return;

	BigInt res;
	res.clear();

	unsigned long long buf, rbuf, lbuf, carry;
	BigInt tmp;
	tmp.clear();
	tmp.resize(size() + num.size());
	for(size_t i = 0; i < num.size(); i++) {
		carry = 0;
		rbuf = num.digits[i];
		if(i > 0) tmp.digits[i-1] = 0;

		for(size_t j = 0; j < size(); j++) {
			lbuf = this->digits[j];
			buf = lbuf * rbuf + carry;
			tmp.digits[i+j] = (unsigned long)(buf % BASE_MULTI);
			carry = (unsigned long)(buf / BASE_MULTI);
		}

		if(carry != 0) {
			tmp.normalize();
			tmp.pushUp((unsigned long)carry);
		}
		res += tmp;
	}
	res.normalize();
	*this = res;
}
*/

template <typename T>
void BigInt::unsignedMul(const T &num) {
	if(isNan()) return;
	if(num == 0) {
		clear();
		return;
	}

	for(size_t i = 0; i < size(); i++)	this->digits[i] *= num;
	normalize();
	align();
}

template <>
void BigInt::unsignedMul(const BigInt &num) {
	if(isNan() || num.isNan()) return;

	BigInt numc = num;

	// Œ…”‚ğ2^n‚É’¼‚µAŒã”¼‚ğ0‚Å–„‚ß‚é
	size_t n = getNextPow2(std::max(size(), num.size())) * 2;
	resize(n);
	numc.resize(n);

	std::vector<Complex> a(n);
	std::vector<Complex> b(n);

	for(size_t i = 0; i < n; i++) {
		a[i] = this->digits[i];
		b[i] = numc.digits[i];
	}

	FFT ffta(a);
	FFT fftb(b);

	ffta.fft();
	fftb.fft();
	ffta = ffta * fftb;
	ffta.ifft();

	std::vector<unsigned long> res(ffta.size());
	for(size_t i = 0; i < res.size(); i++) res[i] = (unsigned long)std::round(ffta[i].real());

	this->digits = res;
	normalize();
	align();
}
