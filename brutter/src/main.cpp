
#include <iostream>
#include "common.hpp"
#include "brutter.hpp"
#include "thr.hpp"


int main(int argc, char* argv[])
{
	//brut::ThreadFirst3Symbols *thr = new brut::ThreadFirst3Symbols();
	auto * thr = new brut::Thread6Symbols();
	thr->run();
	std::cout << std::endl;
/*
	for(size_t i = 0; i < brut::seq2chars.wordLength(); ++i){
		brut::word_t &b = brut::seq2chars.word(i);
		std::cout << b.chr[0] << b.chr[1] << std::endl;
	}*/


}
