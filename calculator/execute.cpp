#include "execute.h"

Execute::Execute(AST *body):body(body) {
}

int Execute::exeAST(AST *ast) {
	switch(ast->getType()) {
	case PLUS_OP:
		return exeAST(ast->getLeft()) + exeAST(ast->getRight());
	case MINUS_OP:
		return exeAST(ast->getLeft()) - exeAST(ast->getRight());
	case MUL_OP:
		return exeAST(ast->getLeft()) * exeAST(ast->getRight());
	case DIV_OP:
		return exeAST(ast->getLeft()) / exeAST(ast->getRight());
	case POW_OP:
		return std::pow(exeAST(ast->getLeft()), exeAST(ast->getRight()));
	case NUMBER:
		return ast->getValue();
	}
	std::cerr << "syntax error." << std::endl;
}

int Execute::run() {
	return exeAST(body);
}