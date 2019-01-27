#include "AST.h"

AST::AST(astType type, AST *left, AST *right):type(type),left(left),right(right) {
}

AST::AST(int value) : type(NUMBER), value(value) {
}

astType AST::getType() {
	return this->type;
}

AST *AST::getLeft() const {
	return this->left;
}

AST *AST::getRight() const {
	return this->right;
}

int AST::getValue() {
	if(this->getType() != NUMBER) {
		std::cerr << "no value..." << std::endl;
		return 0;
	}
	return this->value;
}