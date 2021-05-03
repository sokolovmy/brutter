/*
 * thread.hpp
 *
 *  Created on: 3 мая 2021 г.
 *      Author: holse
 */

#ifndef SRC_THREAD_HPP_
#define SRC_THREAD_HPP_
#include <stdint.h>
#include "common.hpp"
#include <string>


namespace brut {

class Thread {
	std::uint_fast64_t counter = 0;
	std::string curPwd { brut::EmptyStr };
public:
	Thread() {
		// TODO Auto-generated constructor stub

	}
	virtual ~Thread() {
		// TODO Auto-generated destructor stub
	}
	Thread(const Thread &other) = default;
	Thread(Thread &&other) = default;
	Thread& operator=(const Thread &other) = default;
	Thread& operator=(Thread &&other) = default;

	std::uint_fast64_t getCounter() const {
		return counter;
	}

	const std::string& getCurPwd() const {
		return curPwd;
	}
};

class ThreadFirst3Symbols : public Thread {
	ThreadFirst3Symbols(){

	}
};

} /* namespace brut */

#endif /* SRC_THREAD_HPP_ */
