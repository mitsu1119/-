#include "multiprecision.h"

BigInt::BigInt() {
	this->digit.emplace_back(0);
}

BigInt::BigInt(std::string value) {
	this->digit = std::vector<long long>(MAX_DIGITS, 0);

	for(auto &digit: this->digit) {
		if(value.size() <= MAX_DIGIT_INDEX) {
			digit = std::stoll(value);
			break;
		}
		digit = std::stoll(value.substr(value.size() - MAX_DIGIT_INDEX, MAX_DIGIT_INDEX));
		value.erase(value.end() - MAX_DIGIT_INDEX, value.end());
	}
}

BigInt BigInt::abs() const {
	BigInt res;
	res.digit = this->digit;
	return res;
}

void BigInt::add(const BigInt& num) {
	long long bufa, bufb, carry;
	BigInt res, thisabs, numabs;

	res.digit = std::vector<long long>(std::max(digit.size(), num.digit.size()), 0);

	long long i;
	carry = 0;	// åJÇËè„Ç™ÇËóp
	for(i = 0; i < res.digit.size(); i++) {
		bufa = digit[i];
		bufb = num.digit[i];
		res.digit[i] = bufa + bufb + carry;
		carry = res.digit[i] / BASE_MULTI;
		res.digit[i] = res.digit[i] % BASE_MULTI;
	}

	if(carry != 0) {
		res.digit[res.getTopIndex()] = carry;
	}

	this->digit = res.digit;
}

bool BigInt::isLeftLargeRight(const BigInt& left, const BigInt& right) {
	long long buf;

	if(left.digit.size() > right.digit.size()) return true;
	if(left.digit.size() < right.digit.size()) return false;

	for(long long i = left.digit.size() - 1; i >= 0; i--) {
		buf = left.digit[i] - right.digit[i];
		if(buf > 0) return true;
		if(buf < 0) return false;
	}

	// ìôÇµÇ¢
	return false;
}

bool BigInt::isRightLargeLeft(const BigInt& left, const BigInt& right) {
	long long buf;

	if(left.digit.size() > right.digit.size()) return false;
	if(left.digit.size() < right.digit.size()) return true;

	for(long long i = left.digit.size() - 1; i >= 0; i--) {
		buf = left.digit[i] - right.digit[i];
		if(buf > 0) return false;
		if(buf < 0) return true;
	}

	// ìôÇµÇ¢
	return false;
}

bool BigInt::isEqual(const BigInt& left, const BigInt& right) {
	if(left.digit.size() != right.digit.size()) return false;

	for(long long i = left.digit.size() - 1; i>=0; i--) {
		if(left.digit[i] != right.digit[i]) return false;
	}

	// ìôÇµÇ¢
	return true;
}

int BigInt::getTopIndex() const {
	int buf = 0;
	for(int i = digit.size() - 1; i >= 0; i--) {
		if(digit[i] != 0) break;
		buf++;
	}
	return digit.size() - 1 - buf;
}
