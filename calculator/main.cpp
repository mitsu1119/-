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
		std::cout << "> ";
		std::string test1, test2;

		std::cin >> test1>> test2;
		BigInt a(test1);
		BigInt b(test2);
	
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
		std::cout << "a+b: " << a+b << std::endl;
		std::cout << "a>b: " << std::boolalpha << (a>b) << std::endl;
		std::cout << "a<b: " << std::boolalpha << (a<b) << std::endl;
		std::cout << "a==b: " << std::boolalpha << (a==b) << std::endl;

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