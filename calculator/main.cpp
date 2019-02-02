#include <iostream>
#include <string>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "execute.h"
#include "multiprecision.h"

int main() {
	std::string formula;
	Lexer *lexer;
	Parser *parser;
	Execute *execute;

	std::cout << "Let's calculation!" << std::endl << std::endl;

	while(true) {
		// std::cout << "> ";
		BigInt a, b;
		
		std::cout << "a: ";
		std::cin >> a;
		std::cout << "b: ";
		std::cin >> b;
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
		a *= b;
		std::cout << "a*b: " << a << std::endl;


		/*
		std::cout << "> ";

		 std::cin >> formula;
	
		 lexer = new Lexer(formula);
		 lexer->lexAndPrint();
		
		parser = new Parser(lexer->lex());
		
		
		execute = new Execute(parser->parse());
		
		std::cout << "result: " << execute->run() << std::endl;

		delete execute;
		delete parser;
		delete lexer;
		*/
	}
	return 0;
}