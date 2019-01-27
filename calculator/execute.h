#pragma once
#include "AST.h"
#include <iostream>
#include <cmath>

class Execute {
private:
	AST *body;

	int exeAST(AST *ast);

public:
	Execute(AST *body);

	int run();
};