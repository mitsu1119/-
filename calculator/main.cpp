#include <iostream>
#include <string>
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
		std::string test1, test2;

		std::cout << "> ";
		std::cin >> test1 >> test2;
		BigInt a(test1);
		BigInt b(test2);

		std::cout << "a: ";
		a.print();
		std::cout << "b: ";
		b.print();
		std::cout << "a+b: ";
		a.add(b).print();

		// std::cin >> formula;

		// lexer = new Lexer(formula);
		// lexer->lexAndPrint();

		// parser = new Parser(lexer->lex());
		
		
		// execute = new Execute(parser->parse());

		// std::cout << "result: " << execute->run() << std::endl;

		// delete execute;
		// delete parser;
		// delete lexer;
	}
	return 0;
}