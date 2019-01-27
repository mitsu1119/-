#include "parser.h"

Parser::Parser(std::vector<Token> tokens):formula(tokens),currentPos(0) {
}

bool Parser::consume(tokenType type) {
	if((unsigned int)this->currentPos >= this->formula.size()) return false;
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
	AST *node = power();
	for(;;) {
		if(consume(mulOp)) {
			node = new AST(MUL_OP, node, power());
		} else if(consume(divOp)) {
			node = new AST(DIV_OP, node, power());
		} else {
			return node;
		}
	}
}

AST *Parser::power() {
	AST *node = factor();
	if(consume(powOp)) {
		node = new AST(POW_OP, node, factor());
	}
	return node;
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