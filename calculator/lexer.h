#pragma once
#include <iostream>
#include <string>
#include "token.h"
#include <cctype>
#include <vector>

class Lexer {
private:
	std::string formula;
	std::vector<Token> tokens;

public:
	Lexer(std::string formula);

	std::vector<Token> lex();

	void lexAndPrint();	// debug
};