#include "multiprecision.h"

BigInt::BigInt(std::string value) {
	if(value.size() % MAX_DIGIT_INDEX == 0) {
		this->size = value.size() / MAX_DIGIT_INDEX;
	} else {
		this->size = value.size() / MAX_DIGIT_INDEX + 1;
	}

	for(int i = 0; i < this->size; i++) {
		if(i == this->size  - 1) {
			this->digit[i] = std::stoull(value);
		} else {
			this->digit[i] = std::stoull(value.substr(value.size() - MAX_DIGIT_INDEX, MAX_DIGIT_INDEX));
			value.erase(value.end() - MAX_DIGIT_INDEX, value.end());
		}
	}
}

BigInt BigInt::add(BigInt num) {
	long long bufa, bufb, carry;
	BigInt res("0");
	res.size = std::max(this->size, num.size);

	carry = 0;	// ŒJ‚èã‚ª‚è—p
	for(long long i = 0; i < res.size; i++) {
		bufa = (i < this->size) ? this->digit[i] : 0;
		bufb = (i < num.size) ? num.digit[i] : 0;
		res.digit[i] = bufa + bufb + carry;
		carry = res.digit[i] / BASE_MULTI;
		res.digit[i] = res.digit[i] % BASE_MULTI;
	}

	if(carry != 0) res.digit[res.size++] = carry;
	return res;
}

void BigInt::print() {
	for(long long i = this->size - 1; i>=0; i--) {
		std::cout << this->digit[i];
	}
	std::cout << std::endl;
}