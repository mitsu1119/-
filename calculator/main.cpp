#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"

int main() {
	std::string formula;
	Lexer *lexer;
	Parser *parser;

	std::cout << "Let's calculation!" << std::endl << std::endl;

	while(true) {
		std::cout << "> ";
		std::cin >> formula;

		lexer = new Lexer(formula);
		lexer->lexAndPrint();

		parser = new Parser(lexer->lex());
		parser->parse();

		delete parser;
		delete lexer;
	}
	return 0;
}