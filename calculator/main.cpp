#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "execute.h"

int main() {
	std::string formula;
	Lexer *lexer;
	Parser *parser;
	Execute *execute;

	std::cout << "Let's calculation!" << std::endl << std::endl;

	while(true) {
		std::cout << "> ";
		std::cin >> formula;

		lexer = new Lexer(formula);
		// lexer->lexAndPrint();

		parser = new Parser(lexer->lex());
		
		
		execute = new Execute(parser->parse());

		std::cout << "result: " << execute->run() << std::endl;

		delete execute;
		delete parser;
		delete lexer;
	}
	return 0;
}