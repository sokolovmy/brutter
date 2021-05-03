/*
 * brutter.hpp
 *
 *  Created on: 3 мая 2021 г.
 *      Author: holse
 */

#ifndef SRC_BRUTTER_HPP_
#define SRC_BRUTTER_HPP_

#include <stdint.h>
#include <stddef.h>
#include <string_view>
#include "common.hpp"


namespace brut {

class Seq2Chars;
extern Seq2Chars seq2chars;



typedef union __packed__{
	std::uint16_t word;
	char chr[2];
} word_t;

class Seq2Chars {
	word_t * wordBuf;
	size_t length;
	void generate(){
		size_t idx = 0;
		char * c = chr();
		for(size_t i = 0; i < brut::ValidChars.size(); ++i){
			for(size_t j = 0; j < brut::ValidChars.size(); ++j){
				c[idx] = brut::ValidChars[j];
				c[idx + 1] = brut::ValidChars[i];
				idx += 2;
			}
		}
	}
	char *chr(){
		return (char*)wordBuf;
	}
	size_t chrLength(){
		return length * 2;
	}
public:
	Seq2Chars(size_t aLength = ValidChars.size()*ValidChars.size()) {
		length = aLength;
		wordBuf = new word_t[length];
		generate();
	}
	word_t &word(size_t idx){
		return wordBuf[idx];
	}
	size_t wordLength(){
		return length;
	}
	virtual ~Seq2Chars() {
		delete[] wordBuf;
	}
	Seq2Chars(const Seq2Chars &other) = default;
	Seq2Chars(Seq2Chars &&other) = default;
	Seq2Chars& operator=(const Seq2Chars &other) = default;
	Seq2Chars& operator=(Seq2Chars &&other) = default;
};





class Brutter {
public:
	Brutter() {
		// TODO Auto-generated constructor stub

	}
	virtual ~Brutter() {
		// TODO Auto-generated destructor stub
	}
	Brutter(const Brutter &other) = default;
	Brutter(Brutter &&other) = default;
	Brutter& operator=(const Brutter &other) = default;
	Brutter& operator=(Brutter &&other) = default;
};

} /* namespace brut */


#endif /* SRC_BRUTTER_HPP_ */

