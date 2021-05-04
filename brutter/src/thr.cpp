/*
 * thread.cpp
 *
 *  Created on: 3 мая 2021 г.
 *      Author: holse
 */

#include "thr.hpp"


#include <cstring>
#include <string_view>
#include <iostream>
#include <algorithm>

namespace brut {


size_t Thread::sCounter = 0;

bool Thread::CheckPwd(const std::string_view &pwd) {
	++Thread::sCounter;
	if (Thread::sCounter >= 4900*70) {
		std::cout << pwd << "\r";
		Thread::sCounter = 0;
	}
	if (pwd.compare("++++++") == 0) {
		std::cout << "\n" << "Founded" << pwd << "\n";
		std::terminate();
	}
	return false;
}

void ThreadFirst3Symbols::run() {

	for(std::uint_fast8_t i = 0; i< brut::ValidChars.size(); ++i)
		for(std::uint_fast8_t j = 0; j< brut::ValidChars.size(); ++j)
			for(std::uint_fast8_t k = 0; k< brut::ValidChars.size(); ++k) {
				curPwd[0] = brut::ValidChars[k];
				curPwd[1] = brut::ValidChars[j];
				curPwd[2] = brut::ValidChars[i];
				checkPwdFunc(curPwd);
			}

}

void Thread4Symbols::run() {

	char c[5];
	c[4] = 0;
	//const char * c = curPwd.c_str();
	for(std::uint_fast16_t i = 0; i < brut::seq2chars.wordLength(); ++i)
		for(std::uint_fast16_t j = 0; j < brut::seq2chars.wordLength(); ++j) {
			memcpy(&c[0], &seq2chars.word(j).word, 2);
			memcpy(&c[2], &seq2chars.word(i).word, 2);
			checkPwdFunc(std::string_view(c));
		}
}

void Thread6Symbols::run() {
	char c[7];
	c[6] = 0;
	for(std::uint_fast16_t i = 0; i < brut::seq2chars.wordLength(); ++i)
		for(std::uint_fast16_t j = 0; j < brut::seq2chars.wordLength(); ++j)
			for(std::uint_fast16_t k = 0; k < brut::seq2chars.wordLength(); ++k){
				memcpy(&c[0], &seq2chars.word(k).word, 2);
				memcpy(&c[2], &seq2chars.word(j).word, 2);
				memcpy(&c[4], &seq2chars.word(i).word, 2);
				checkPwdFunc(std::string_view(c));
			}
}

} //namespace brut

