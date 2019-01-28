#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#define NOMINMAX

constexpr long long BASE_MULTI = 10000000000;	// base
constexpr long long MAX_DIGIT_INDEX = 10;		// 一つの要素内の最大桁
constexpr long long MAX_DIGITS = 100;	// digitの数

class BigInt {
private:
	long long digit[MAX_DIGITS];
	long long size;

public:
	BigInt(std::string value);

	BigInt add(BigInt num);

	void print();
};