#include "multiprecision.h"

BigInt::BigInt():nan(true) {
}

BigInt::BigInt(std::string i) {
	// •‰”‚Í–³Œø’l
	if(i.size() == 0 || i[0] == '-') {
		this->nan = true;
		return;
	}
	nan = false;

	if(i[0] == '+') i.erase(i.begin());

	while(i.size() > MAX_DIGIT_INDEX) {
		pushUp(std::stoul(i.substr(i.size() - MAX_DIGIT_INDEX, MAX_DIGIT_INDEX)));
		i.erase(i.end() - MAX_DIGIT_INDEX, i.end());
	}
	pushUp(std::stoul(i));
}

void BigInt::resize(size_t size) {
	this->digits.resize(size, unsigned long());
}

void BigInt::pushUp(unsigned long num) {
	this->digits.emplace_back(num);
}

void BigInt::pushDown(unsigned long num) {
	rShift(1);
	this->digits[0] = num;
}

void BigInt::rShift(size_t cnt) {
	for(size_t i = 1; i < this->digits.size(); i++) this->digits[i-1] = this->digits[i];
	this->digits.pop_back();
}

void BigInt::lShift(size_t cnt) {
	resize(this->digits.size() + 1);
	for(size_t i = 0; i < this->digits.size() - 1; i++) this->digits[i+1] = this->digits[i];
	this->digits[0] = 0;
}

void BigInt::normalize() {
	while(true) {
		if(this->digits[this->digits.size() - 1] == 0) this->digits.pop_back();
		else break;
	}
}

void BigInt::align() {
	for(size_t i = 0; i < this->digits.size() - 1; i++) {
		if(this->digits[i] / BASE_MULTI != 0) {
			this->digits[i + 1] += this->digits[i] / BASE_MULTI;
			this->digits[i] %= BASE_MULTI;
		}
	}
	if(this->digits[this->digits.size() - 1] / BASE_MULTI != 0) {
		this->pushUp(this->digits[this->digits.size() - 1] / BASE_MULTI);
		this->digits[this->digits.size() - 2] %= BASE_MULTI;
	}
}

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

// •MŽZ‚ÌƒAƒ‹ƒSƒŠƒYƒ€
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


bool BigInt::isEqual(const BigInt &num) const {
	if(isNan() || num.isNan()) return false;
	if(size() != num.size()) return false;

	for(int i = 0; i < (int)size(); i++) {
		if(this->digits[i] != num.digits[i]) return false;
	}
	return true;
}


void BigInt::clear() {
	this->digits.clear();
	pushUp(0);
	this->nan = false;
}

bool BigInt::isNan() const {
	return this->nan;
}

size_t BigInt::size() const {
	return this->digits.size();
}

