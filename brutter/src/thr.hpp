/*
 * thread.hpp
 *
 *  Created on: 3 мая 2021 г.
 *      Author: holse
 */

#ifndef SRC_THR_HPP_
#define SRC_THR_HPP_

#include <stdint.h>
#include <string>
#include <string_view>
#include <thread>
#include "common.hpp"
#include "brutter.hpp"

namespace brut {

typedef bool (*CheckPwdFunc_t)(const std::string_view &pwd);

class Thread {
protected:
	static size_t sCounter;
	static bool CheckPwd(const std::string_view &pwd);
	std::uint_fast64_t counter = 0;
	std::string curPwd { brut::EmptyStr };
	std::jthread *thr = nullptr;
	CheckPwdFunc_t checkPwdFunc;
public:
	virtual void run() = 0;
	Thread(size_t pwdLength, CheckPwdFunc_t aCheckPwdFunc = &CheckPwd) {
		curPwd.reserve(pwdLength);
		checkPwdFunc = aCheckPwdFunc;
	}
	virtual ~Thread() {
		if (thr != nullptr && thr->joinable()) {
			thr->join();
			delete thr;
		}

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

class ThreadFirst3Symbols: public Thread {
public:
	ThreadFirst3Symbols(CheckPwdFunc_t aCheckPwdFunc = &CheckPwd) : Thread(3, aCheckPwdFunc){
		;
	}
	virtual void run();
};

class Thread4Symbols: public Thread {
public:
	Thread4Symbols(CheckPwdFunc_t aCheckPwdFunc = &CheckPwd) : Thread(4, aCheckPwdFunc){
		;
	}
	virtual void run();
};

class Thread6Symbols: public Thread {
public:
	Thread6Symbols(CheckPwdFunc_t aCheckPwdFunc = &CheckPwd) : Thread(6, aCheckPwdFunc){
		;
	}
	virtual void run();
};


} /* namespace brut */

#endif /* SRC_THR_HPP_ */

