#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>
#define NOMINMAX

constexpr unsigned long BASE_MULTI = 100000000;	// base
constexpr int MAX_DIGIT_INDEX = 8;		// ˆê‚Â‚Ì—v‘f“à‚ÌÅ‘åŒ…
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

	// ‰‰Z
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