#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#define NOMINMAX

constexpr long long BASE_MULTI = 10000000000;	// base
constexpr long long MAX_DIGIT_INDEX = 10;		// ˆê‚Â‚Ì—v‘f“à‚ÌÅ‘åŒ…
constexpr long long MAX_DIGITS = 100;	// digit‚Ì”

class BigInt {
private:
	long long digit[MAX_DIGITS];
	long long size;

public:
	BigInt(std::string value);

	BigInt add(BigInt num);

	void print();
};