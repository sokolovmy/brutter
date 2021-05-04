/*
 * thread.h
 *
 *  Created on: 4 мая 2021 г.
 *      Author: holse
 */

#ifndef SRC_THREAD_H_
#define SRC_THREAD_H_

#include "thr.hpp"

namespace brut {

class test2: public Thread {
public:
	test2();
	virtual ~test2();
	test2(const test2 &other) = default;
	test2(test2 &&other) = default;
	test2& operator=(const test2 &other) = default;
	test2& operator=(test2 &&other) = default;
};

} /* namespace brut */

#endif /* SRC_THREAD_H_ */
