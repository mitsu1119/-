#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#define NOMINMAX

constexpr long long BASE_MULTI = 10000000000000000;	// base
constexpr long long MAX_DIGIT_INDEX = 16;		// ˆê‚Â‚Ì—v‘f“à‚ÌÅ‘åŒ…
constexpr long long MAX_DIGITS = 100;	// digit‚Ì”

class BigInt {
private:
	std::vector<long long> digit;
	long long size;

	BigInt abs() const;

	void add(const BigInt& num);
	static bool isLeftLargeRight(const BigInt& left, const BigInt& right);
	static bool isRightLargeLeft(const BigInt& left, const BigInt& right);
	static bool isEqual(const BigInt& left, const BigInt& right);

public:
	BigInt(std::string value);
	BigInt();

	BigInt& operator=(const BigInt& num) {
		if(this != &num) {
			this->size = num.size;
			this->digit = num.digit;
		}
		return *this;
	}

	BigInt& operator+=(const BigInt& right) {
		add(right);
		return *this;
	}

	friend BigInt operator+(BigInt left, const BigInt& right) {
		left += right;
		return left;
	}

	friend bool operator>(const BigInt& left, const BigInt& right) {
		return isLeftLargeRight(left, right);
	}

	friend bool operator<(const BigInt& left, const BigInt& right) {
		return isRightLargeLeft(left, right);
	}

	friend bool operator>=(const BigInt& left, const BigInt& right) {
		return (left == right) || (left > right);
	}

	friend bool operator<=(const BigInt& left, const BigInt& right) {
		return (left == right) || (left < right);
	}

	friend bool operator==(const BigInt& left, const BigInt& right) {
		return isEqual(left, right);
	}

	friend std::ostream& operator<<(std::ostream &o, const BigInt &num) {
		for(long long i = num.size - 1; i>=0; i--) {
			o << num.digit[i];
		}
		return o;
	}

	void print();
};