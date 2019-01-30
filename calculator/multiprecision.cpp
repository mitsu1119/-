#include "multiprecision.h"

BigInt::BigInt() {
	this->size = 1;
	this->digit.emplace_back(0);
}

BigInt::BigInt(std::string value) {
	if(value.size() % MAX_DIGIT_INDEX == 0) {
		this->size = value.size() / MAX_DIGIT_INDEX;
	} else {
		this->size = value.size() / MAX_DIGIT_INDEX + 1;
	}

	this->digit = std::vector<long long>(this->size);

	for(long long i = 0; i < this->size; i++) {
		if(i == this->size  - 1) {
			this->digit[i] = std::stoll(value);
		} else {
			this->digit[i] = std::stoll(value.substr(value.size() - MAX_DIGIT_INDEX, MAX_DIGIT_INDEX));
			value.erase(value.end() - MAX_DIGIT_INDEX, value.end());
		}
	}
}

BigInt BigInt::abs() const {
	BigInt res;
	res.digit = this->digit;
	res.size = this->size;
	return res;
}

void BigInt::add(const BigInt& num) {
	long long bufa, bufb, carry;
	BigInt res, thisabs, numabs;

	res.size = std::max(this->size, num.size);
	res.digit = std::vector<long long>(res.size);

	carry = 0;	// ŒJ‚èã‚ª‚è—p
	for(long long i = 0; i < res.size; i++) {
		bufa = (i < this->size) ? this->digit[i] : 0;
		bufb = (i < num.size) ? num.digit[i] : 0;
		res.digit[i] = bufa + bufb + carry;
		carry = res.digit[i] / BASE_MULTI;
		res.digit[i] = res.digit[i] % BASE_MULTI;
	}

	if(carry != 0) {
		res.size++;
		res.digit.emplace_back(carry);
	}

	this->digit = res.digit;
	this->size = res.size;
}

bool BigInt::isLeftLargeRight(const BigInt& left, const BigInt& right) {
	long long sizes = left.size - right.size;
	long long buf;

	for(long long i = left.size - 1; i>=0; i--) {
		buf = left.digit[i] - right.digit[i];
		if(buf > 0) return true;
		if(buf < 0) return false;
	}
	// “™‚µ‚¢
	return false;
}

bool BigInt::isRightLargeLeft(const BigInt& left, const BigInt& right) {
	long long sizes = left.size - right.size;
	long long buf;

	for(long long i = left.size - 1; i>=0; i--) {
		buf = left.digit[i] - right.digit[i];
		if(buf > 0) return false;
		if(buf < 0) return true;
	}
	// “™‚µ‚¢
	return false;
}

bool BigInt::isEqual(const BigInt& left, const BigInt& right) {
	if(left.size != right.size) return false;

	for(long long i = left.size - 1; i>=0; i--) {
		if(left.digit[i] != right.digit[i]) return false;
	}

	// “™‚µ‚¢
	return true;
}

void BigInt::print() {
	for(long long i = this->size - 1; i>=0; i--) {
		std::cout << this->digit[i];
	}
	std::cout << std::endl;
}