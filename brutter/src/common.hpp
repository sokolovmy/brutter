/*
 * common.hpp
 *
 *  Created on: 3 мая 2021 г.
 *      Author: holse
 */

#ifndef SRC_COMMON_HPP_
#define SRC_COMMON_HPP_


namespace brut {




//                                                1         2         3         4         5         6         7
//                                       1234567890123456789012345678901234567890123456789012345678901234567890
constexpr std::string_view ValidChars { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$^&-=+" };
constexpr std::uint_fast8_t MaxPwdLen { 12 };
constexpr std::string_view  EmptyStr { "" };



}  // namespace brut




#endif /* SRC_COMMON_HPP_ */
