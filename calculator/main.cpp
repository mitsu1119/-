#include <iostream>
#include <string>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "execute.h"
#include "multiprecision.h"
#include "fft.h"
#include <valarray>

int main() {
	std::string formula;
	Lexer *lexer;
	Parser *parser;
	Execute *execute;

	std::cout << "Let's calculation!" << std::endl;

	while(true) {
		// std::cout << "> ";
		std::valarray<std::complex<double>> a = {93, 97, 58, 53, 0, 0, 0, 0};
		std::valarray<std::complex<double>> b = {95, 27, 83, 33, 0, 0, 0, 0};

		FFT ffta(a);
		ffta.fft();
		
		FFT fftb(b);
		fftb.fft();

		ffta *= fftb;
		a = ffta.ifft();

		std::vector<unsigned long> c(a.size(), 0);
		for(size_t i = 0; i < a.size(); i++) c.emplace_back(a[i].real());
		std::cout << std::endl;

		while(true) {
			if(c[c.size() - 1] == 0) c.pop_back();
			else break;
		}
		while(true) {
			if(c[0] == 0) c.erase(c.begin());
			else break;
		}

		for(size_t i = 0; i < c.size() - 1; i++) {
			if(c[i] / 100 != 0) {
				c[i + 1] += c[i] / 100;
				c[i] = c[i] % 100;
			}
		}

		std::cout << c[c.size() - 1];
		for(int i = c.size() - 2; i >= 0; i--) std::cout << std::setw(2) << std::setfill('0') << c[i];

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