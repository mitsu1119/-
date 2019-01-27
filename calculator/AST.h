#pragma once
#include <iostream>

enum astType {
	NUMBER, PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, POW_OP
};

class AST {
private:
	astType type;
	int value;
	AST *left, *right;

public:
	AST(astType type, AST *left, AST *right);
	AST(int value);

	astType getType();
	AST *getLeft() const;
	AST *getRight() const;
	int getValue();
};