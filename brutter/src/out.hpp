#ifndef __OUT_HPP__
#define __OUT_HPP__

// #include <cstdio>
// #include <limits>
// #include <cstdint>
// #include <cinttypes>
#include <chrono>
#include <thread>
#include <ctime>
#include "thr.hpp"
#include "brutgen.hpp"
#include <list>


using namespace std;

class Out {
    ArrayThr thrs;
    BrutGen *bg;
    // bool mainLoop = true;
    time_t startTime;
public:
    Out(ArrayThr aThrs, BrutGen * abg){
        thrs = aThrs;
        time(&startTime);
        bg = abg;        
    }
    void stopThread(){
        // mainLoop = false;
    }
    const char * convertTime(char * buf, size_t buflen, time_t * time){
        unsigned long int t = *time;
        int seconds =  t % 60;
        t /= 60;
        int minutes = t % 60;
        t /= 60;
        unsigned long int hours = t % 60;
        snprintf(buf, buflen, "%02lu:%02i:%02i", hours, minutes, seconds);
        return buf;
    }
    
    const char* toStr(char * buf, size_t buflen, int num){
        snprintf(buf, buflen, "%03d", num);
        return buf;
    }
    std::string injSep(size_t num){
        char cbuf[5];
        list<int> stk;
        size_t i = num;
        int ost;
        while(i > 0) {
            ost = i % 1000;
            i /= 1000;
            stk.push_front(ost);
        };
        
        if (stk.size()) {
            std::string buf = std::to_string(stk.front());
            stk.pop_front();
            for (auto i : stk){
                buf.append("'");
                buf.append(toStr(cbuf, sizeof(cbuf), i));
            }
            return buf;
        } else return bdm::EmptyStr;
    }
        
    size_t getCounter() {
        size_t cCounter = 0;
        for (auto thr : thrs) 
            cCounter += thr->getCounter();
        return cCounter;
    }
    size_t getPersent(size_t counter){
        size_t t = bdm::ValidChars.size() + 1;
        size_t t1 = bdm::ValidChars.size() * bdm::ValidChars.size() * bdm::ValidChars.size();
        size_t t2 = 1;
        for (int i = 0; i< bg->getLength(); ++i)
            t2 *= t;
        t2 /=100;
        t2 *= t1;
        return counter  / t2;
    }
   
    void result(std::string resultPwd){
        char buf[100];
        time_t stopTime;
        time(&stopTime);
        printf("==========================================================\n");
        printf("==========================================================\n");
        printf("Password found: \"%s\"\n", resultPwd.c_str());
        strftime(buf, sizeof(buf), "%F %T", localtime(&startTime));
        printf("Started at %s\n", buf);
        strftime(buf, sizeof(buf), "%F %T", localtime(&stopTime));
        printf("Stopped at %s\n", buf);
        stopTime -= startTime;
        printf("Time Processed %s\n", convertTime(buf, sizeof(buf), &stopTime));
        printf("Passwords processed: %s\n", injSep(getCounter()).c_str());
        printf("==========================================================\n");
        printf("==========================================================\n");
    }
    void run(){  

        time_t diff;
        char timeStartedStr[20];   
        char buf[100];
        
        strftime(timeStartedStr, sizeof(timeStartedStr), "%F %T", localtime(&startTime));
        //std::this_thread::sleep_for(200ms);
        while (!bdm::founded.stop) {
            time(&diff);
            diff -= startTime;
            size_t counter = getCounter();
            printf("\033c");
            printf("==========================================================\n");
            printf("| Started at           %s\n", timeStartedStr);
            printf("| Time:                %s\n", convertTime(buf, sizeof(buf), &diff));
            printf("| Passwords processed: %s\n", injSep(counter).c_str());
            printf("| %% of cur pwd len:    %lu%%\n", getPersent(counter));
            printf("==========================================================\n");
            printf("|%5s| %27s| %20s|\n",
                "Thr#",
                "Pwd Processed",
                "Curr Pwd"            );
            for (auto thr : thrs) {
                printf("|%5d| %27s| %20s|\n",
                    thr->getId(),
                    injSep(thr->getCounter()).c_str(),
                    // thr->getCounter(),
                    thr->getCurPwd().c_str()
                );
            }
            std::this_thread::sleep_for(100ms);
        }
    }

};

#endif