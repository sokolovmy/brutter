#include <iostream>
#include <thread>
#include <chrono>

#include "common.hpp"
#include "brutgen.hpp"
#include "thr.hpp"
#include "out.hpp"

using namespace std;

ArrayThr lthrs;

list<thread*> lthreads;



int main(){
    std::cout << "Starting!" << endl;
    BrutGen bg;
    
    for (int i = 0; i < MAX_THREADS; i++){
      auto thr = new Thr(&bdm::founded, i);
      lthrs[i] = thr;
      /* lthreads[i] =new  */
      lthreads.push_back(new thread(&Thr::threadFunc, thr));
    }
    Out * outThr = new Out(lthrs, &bg);
    /* thread * outThread = new  */
    lthreads.push_back(new thread(&Out::run, outThr));
    int curThread = 0;
    
    while(!bdm::founded.stop) {
      const std::string & str = bg.get();
      bool bbb = false;
      int i = 0;
         while(!bbb) {
          bbb = lthrs[curThread]->try_push(str);
          curThread++;
          curThread %= MAX_THREADS;
          if (bdm::founded.stop) break;
          ++i;
          if (i == MAX_THREADS) {
            i = 0;
            std::this_thread::sleep_for(5ms);
          }
         }
    } 
     


    for (auto thr : lthrs)
      thr->stopThread();
    outThr->stopThread();

    //for (auto thr : lthreads) 
    //  thr->join();
//    std::this_thread::sleep_for(2000ms);

    outThr->result(bdm::founded.foundedPwd);
}