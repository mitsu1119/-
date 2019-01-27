#include <iostream>
#include <string>
#include "parser.h"
#include "lexer.h"

int main() {
	std::string formula;
	Parser *parser;
	Lexer *lexer;

	std::cout << "Let's calculation!" << std::endl << std::endl;

	while(true) {
		std::cout << "> ";
		std::cin >> formula;

		lexer = new Lexer(formula);
		lexer->lexAndPrint();

		delete lexer;
	}
	return 0;
}