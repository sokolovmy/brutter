
#ifndef _BRUTGEN_HPP_
#define _BRUTGEN_HPP_

#include <string>
#include <string_view>
#include <vector>
#include "common.hpp"


/* 
class BrutGen1 {
    std::string curPwd;
    public:
    unsigned char getCharNo(){//current charNo in last char of pwd
        return curPwd[curPwd.size()-1] - bdm::StartValidChar;
    }
    int getVCLen(){
        return bdm::EndValidChar - bdm::StartValidChar;//bdm::ValidChars.length();
    }
    unsigned char getLength(){//current Pwd Length
        return curPwd.size();
    }
    BrutGen1(){
        curPwd.reserve(bdm::MaxPwdLen);
        curPwd.push_back(bdm::StartValidChar);
    }
    bool get(std::string &str) noexcept {//do not checking maxPwdLen for faster code
        bool overflow = true;
        for(auto &n : curPwd) {
            if (overflow) ++n;
            overflow =  n >= bdm::EndValidChar;
            if (overflow) n = bdm::StartValidChar;
        }
        if (overflow) curPwd.push_back(bdm::StartValidChar);
        str = curPwd;
        return true;
    }
};
 */
class  BrutGen{
    std::vector<std::uint_fast8_t> counters;
    std::string curPwd;
#ifdef DEBUG_TO_FILE
    std::ofstream myfile;
#endif
public:
    unsigned char getCharNo(){//current charNo in last char of pwd
        return counters[counters.size()-1];
    }
    int getVCLen(){
        return bdm::ValidChars.size();
    }
    unsigned char getLength(){//current Pwd Length
        return counters.size();
    }
    BrutGen(){
        counters.reserve(bdm::MaxPwdLen);
        curPwd.reserve(bdm::MaxPwdLen);
        //counters.push_back(0);
#ifdef DEBUG_TO_FILE
    myfile.open("brutgen.txt");
#endif
    }
    ~BrutGen() {
#ifdef DEBUG_TO_FILE
    myfile.close();
#endif
    }
    const std::string & get() noexcept {
        bool overflow = true;
        uint_fast8_t i = 0;
        while(i < counters.size()) {
            ++counters[i];
            overflow = counters[i] == bdm::ValidChars.size();
            if(overflow) {
                counters[i] = 0;
                curPwd[i] = bdm::ValidChars[0];
            } else  {
                curPwd[i] = bdm::ValidChars[counters[i]];
                break;
            }
            ++i;
        };
        if (overflow) {
            counters.push_back(0);
            curPwd.push_back(bdm::ValidChars[0]);
        }
#ifdef DEBUG_TO_FILE
        myfile << curPwd << std::endl;
#endif
        return curPwd;
    }
};


#endif

