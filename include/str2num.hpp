#ifndef STR2NUM_HPP
#define STR2NUM_HPP
#include "str2num.h"
#include <cstddef>
#include <optional>
#include <string>
#include <iostream>

//Exception Free wrappers for the following
/*
stoi
stol
stoul
stoll
stoull
*/
namespace s2n{
    //stoi
    std::optional<int> safe_stoi( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        int out;
        char* endptr = nullptr;
        if(str2int(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stol
    std::optional<long> safe_stol( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        long out;
        char* endptr = nullptr;
        if(str2long(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stoul
    std::optional<unsigned long> safe_stoul( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        unsigned long out;
        char* endptr = nullptr;
        if(str2ulong(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stoll
    // std::optional<long long> safe_stoll( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
    //     long long out;
    //     char* endptr = nullptr;
    //     if(str2ll(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
    //         {   
    //             if(pos != nullptr)
    //                 *pos = endptr - str.c_str();
    //             return out;
    //         }
    //     else return std::nullopt;
    // }
};

#endif
