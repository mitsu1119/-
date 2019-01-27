#pragma once
#include "AST.h"
#include <iostream>

class Execute {
private:
	AST *body;

	int exeAST(AST *ast);

public:
	Execute(AST *body);

	int run();
};