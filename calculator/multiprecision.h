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
constexpr int MAX_DIGIT_INDEX = 2;		// 一つの要素内の最大桁
constexpr int MAX_DIGITS = 100;	// digitの数

class BigInt {
private:
	std::vector<unsigned long> digits;
	bool nan;

	void resize(size_t size);
	void pushUp(unsigned long num);
	void pushDown(unsigned long num);
	void rShift(size_t cnt);
	void lShift(size_t cnt);

	// 上位桁の0を消去
	void normalize();

	// 一つの桁での最大値を超えていたら次の桁を足して合わせる
	void align();

	// x以上の2^nを探す
	size_t getNextPow2(size_t x);

	// 演算
	void unsignedAdd(const BigInt &num);
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

	BigInt &operator+=(const BigInt &num) {
		unsignedAdd(num);
		return *this;
	}
	BigInt &operator*=(const BigInt &num) {
		unsignedMul(num);
		return *this;
	}

	friend bool operator==(const BigInt &left, const BigInt &right) {
		return left.isEqual(right);
	}
};