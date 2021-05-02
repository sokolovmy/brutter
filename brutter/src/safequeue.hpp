#ifndef __SAFEQUEUE_HPP__
#define __SAFEQUEUE_HPP__

#include <queue>
#include <string>
#include <mutex>
#include "common.hpp"


class SafeQueue {
    std::mutex m;
    std::queue<std::string> q;
    size_t maxQSize;
public:
    SafeQueue(size_t aMaxQSize = 500) {
        maxQSize = aMaxQSize;
    }
    bool try_push(const std::string & str){
        //std::lock_guard<std::mutex> lg(m);
        if (!m.try_lock()) return false;
        if (q.size() >= maxQSize) {
            m.unlock();
            return false;
        }
        q.push(str);
        m.unlock();
        return true;
    }
    const std::string & pop(){
        std::lock_guard<std::mutex> lg(m);
        if (q.empty()) {
            return bdm::EmptyStr;
        }
        std::string &str = q.front();
        q.pop();
        return str;

    }
/*     bool pop(std::string &str){
        std::lock_guard<std::mutex> lg(m);
        if (q.empty()) {
            return false;
        }
        str = q.front();
        q.pop();
        return true;
    }
 */    bool empty(){
        std::lock_guard<std::mutex> lg(m);
        return q.empty();
    }
    bool full(){
        std::lock_guard<std::mutex> lg(m);
        return q.size() >= maxQSize;
    }

}


;
#endif