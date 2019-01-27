#include "AST.h"

AST::AST(astType type, AST *left, AST *right):type(type),left(left),right(right) {
}

AST::AST(int value) : type(NUMBER), value(value) {
}