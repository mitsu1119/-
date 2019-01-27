#include "parser.h"

Parser::Parser(std::vector<Token> tokens):formula(tokens),currentPos(0) {
}

bool Parser::consume(tokenType type) {
	if(this->formula[this->currentPos].getType() == type) {
		this->currentPos++;
		return true;
	}
	return false;
}

AST *Parser::expression() {
	AST *node = term();

	for(;;) {
		if(consume(plusOp)) {
			node = new AST(PLUS_OP, node, term());
		} else if(consume(minusOp)) {
			node = new AST(MINUS_OP, node, term());
		} else {
			return node;
		}
	}
}

AST *Parser::term() {
	AST *node = factor();

	for(;;) {
		if(consume(mulOp)) {
			node = new AST(MUL_OP, node, factor());
		} else if(consume(divOp)) {
			node = new AST(DIV_OP, node, factor());
		} else {
			return node;
		}
	}
}

AST *Parser::factor() {
	if(consume(lpToken)) {
		AST *node = expression();
		if(!consume(rpToken)) {
			std::cerr << "')' is not found." << std::endl;
		}
		return node;
	}

	if(formula[currentPos].getType() == number) {
		return new AST(formula[currentPos++].getValue());
	}

	std::cerr << "syntax error." << std::endl;
	return nullptr;
}

AST *Parser::parse() {
	return expression();
}