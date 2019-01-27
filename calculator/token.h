#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

class enumName {
private:
	std::vector<std::string> args;
	std::string buf = "";

	void argSplit(std::string str) {	// split ','
		char charactor;
		int currentPos = 0;
		while((unsigned int)currentPos < str.size()) {
			charactor = str[currentPos++];
			if(std::isspace(charactor)) continue;
			if(currentPos == str.size()) {
				buf += charactor;
				args.emplace_back(buf);
				break;
			}
			if(charactor != ',') buf += charactor;
			else {
				args.emplace_back(buf);
				buf = "";
			}
		}
	}
public:
	enumName(std::string enums) {
		argSplit(enums);
	}
	std::string operator[](int i) {
		return args[i];
	}
};

#define DECLARE_ENUM(enumname, enumstr, ...) \
enum enumname { __VA_ARGS__ }; \
static enumName enumstr(#__VA_ARGS__); 

DECLARE_ENUM(tokenType, enumTokenName, number, plusOp, minusOp, mulOp, divOp, lpToken, rpToken, unknownToken);

class Token {
private:
	tokenType type;

	int value;	// number only
	std::string str; // for error

public:
	Token(char str);
	Token(int value);

	int getValue();
	tokenType getType();
	void print();
};