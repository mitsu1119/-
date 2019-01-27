#include "lexer.h"

Lexer::Lexer(std::string formula):formula(formula) {
	this->tokens = std::vector<Token>();
}

std::vector<Token> Lexer::lex() {
	int currentPos = 0;
	char c;

	while(currentPos < this->formula.size()) {
		c = this->formula[currentPos++];
		if(std::isspace(c)) continue;		// スペースの読み飛ばし

		switch(c) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
			this->tokens.emplace_back(c);
			continue;
		}

		if(std::isdigit(c)) {
			int n = 0;
			do {
				n = n*10 + c - '0';
				c = this->formula[currentPos++];
			} while(isdigit(c));
			currentPos--;
			this->tokens.emplace_back(n);
			continue;
		}
	}
	return this->tokens;
}

void Lexer::lexAndPrint() {
	std::vector<Token> tokens = this->lex();

	for(auto i: tokens) {
		i.print();
	}
}