
#include <iostream>
#include "common.hpp"
#include"brutter.hpp"



int main(int argc, char* argv[])
{



	for(size_t i = 0; i < brut::seq2chars.wordLength(); ++i){
		brut::word_t &b = brut::seq2chars.word(i);
		std::cout << b.chr[0] << b.chr[1] << std::endl;
	}


}
