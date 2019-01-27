#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "token.h"
#include "AST.h"

class Parser {
private:
	std::vector<Token> formula;
	std::stack<int> stack;
	int currentPos;

	AST *expression();
	AST *term();
	AST *factor();

	bool consume(tokenType type);		// ���̃g�[�N�������҂����^�̂Ƃ����͂�1�g�[�N���i�߂�true

public:
	Parser(std::vector<Token> tokens);

	AST *parse();
};