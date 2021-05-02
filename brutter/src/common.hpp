#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <string>
#include <string_view>

//#define DEBUG_TO_FILE 1


#ifdef DEBUG_TO_FILE
#include <iostream>
#include <fstream>
#endif

#define test

namespace bdm
{
  
  //                                                1         2         3         4         5         6         7
  //                                       1234567890123456789012345678901234567890123456789012345678901234567890
  constexpr std::string_view ValidChars { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$^&-=+" };
  constexpr std::uint_fast8_t MaxPwdLen { 12 - 3 };
  const std::string & EmptyStr { "" };

  /* const char StartValidChar = '!';
  const char EndValidChar = '~'; */
  #define MAX_THREADS 30

  #define LDAP_URL "ldap://10.214.99.124/"
  #define LDAP_BIND_DN "cn=directory manager"


  struct Founded {
    bool stop = false;
    std::string foundedPwd = "";
  };

  static struct Founded founded;

} // namespace bdm


#endif
