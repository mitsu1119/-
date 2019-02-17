#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "execute.h"
#include "multiprecision.h"
#include "fft.h"

int main() {
	std::string formula;
	Lexer *lexer;
	Parser *parser;
	Execute *execute;

	std::cout << "Let's calculation!" << std::endl;

	while(true) {
		BigInt a;
		std::cin >> a;
		int b;
		std::cin >> b;

		a *= b;

		std::cout << a << std::endl;

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