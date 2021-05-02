#ifndef __THR_HPP__
#define __THR_HPP__

#include <string>
#include <string_view>
#include "common.hpp"
#include "safequeue.hpp"
#include "myldap.hpp"


constexpr std::string_view ThreeDots { "..." };

class Thr;
typedef std::array<Thr*, MAX_THREADS> ArrayThr;


using namespace std;
class Thr {
    SafeQueue *q;
    int maxQSize;
    size_t counter = 0;
    std::string curPwd;
    std::string aPwd;
    CheckPwd *checkPwd;
    int id;
    bdm::Founded * founded;
public:
    Thr(bdm::Founded *aFounded, int aId, int aMaxQueueSize = 100){
        maxQSize = aMaxQueueSize;
        checkPwd = new CheckPwd();
        id = aId;
        founded = aFounded;
        curPwd.reserve(bdm::MaxPwdLen);
        aPwd.reserve(bdm::MaxPwdLen + 3);
        aPwd.append(ThreeDots);
    }
    ~Thr(){
        delete q;
        delete checkPwd;
    }
    bool try_push(const std::string &str){
        if (q)
            return q->try_push(str);
        else return false;
    }
    size_t getCounter(){
        return counter;
    }
    const std::string & getCurPwd(){
        aPwd.resize(3);
        aPwd.append(curPwd);
        return aPwd;
    }
    int getId(){
        return id;
    }
    void stopThread(){
        // mainLoop = false;
    }
    void threadFunc(){
        q = new SafeQueue(maxQSize);
        do {
            curPwd = q->pop();
            if (curPwd != bdm::EmptyStr){
                std::string str;
                str.reserve(curPwd.size() + 3);
                str += '\000';
                str += '\000';
                str += '\000';
                str += curPwd;
                for (auto &fc1 : bdm::ValidChars){
                     for (auto &fc2 : bdm::ValidChars){
                         for (auto &fc3 : bdm::ValidChars){
                            str[0] = fc3;
                            str[1] = fc2;
                            str[2] = fc1;
                            counter++;
                            if (checkPwd->checkPwdFunc(str)) {
                                founded->foundedPwd = str;
                                founded->stop = true;
                                break;
                            }
                         }
                    }
                }
            }
        } while (!founded->stop);
    }
};


#endif