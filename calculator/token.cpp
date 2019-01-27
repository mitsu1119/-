#include "token.h"

Token::Token(char str):str(std::string() + str) {
	switch(str) {
	case '+':
		this->type = plusOp;
		break;
	case '-':
		this->type = minusOp;
		break;
	case '*':
		this->type = mulOp;
		break;
	case '/':
		this->type = divOp;
		break;
	case '^':
		this->type = powOp;
		break;
	case '(':
		this->type = lpToken;
		break;
	case ')':
		this->type = rpToken;
		break;
	default:
		std::cerr << "Unknown token: " << str << std::endl;
		this->type = unknownToken;
		break;
	}
}

Token::Token(int value) : type(number), value(value), str(std::to_string(value)) {
}

int Token::getValue() {
	if(this->type != number) {
		std::cerr << "error: token " << str << " doesn't have value." << std::endl;
		return 0;
	}
	return this->value;
}

tokenType Token::getType() {
	return this->type;
}

void Token::print() {
	std::cout << std::left << std::setw(10) << enumTokenName[this->type] << " : " << this->str << std::endl;
}

