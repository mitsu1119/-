#pragma once

enum astType {
	NUMBER, PULS_OP, MINUS_OP, MUL_OP, DIV_OP
};

class AST {
private:
	astType type;
	int value;
	AST *left, *right;

public:
	AST(astType type, AST *left, AST *right);
	AST(int value);
};