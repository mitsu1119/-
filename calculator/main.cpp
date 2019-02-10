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
		// std::cout << "> ";
		std::vector<Complex> a = {93, 97, 58, 53, 0, 0, 0, 0};
		std::vector<Complex> b = {95, 27, 83, 33, 0, 0, 0, 0};

		FFT ffta(a);
		ffta.fft();

		FFT fftb(b);
		fftb.fft();

		ffta = ffta * fftb;

		std::vector<Complex> c = ffta.ifft();

		for(const auto &i : c) std::cout << i;
		std::cout << std::endl;
		while(1);

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