//  SPDX-FileCopyrightText: 2022 Kish Jadhav
//  SPDX-License-Identifier: MIT License
#ifndef TEST_FLOATING_HPP
#define TEST_FLOATING_HPP
#include "str2num.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> sinputs {
    {""," ", "asdasd"}, // INCONVERTIBLE
    {"1e550","1e600"}, //OVERFLOW
    {"-1e550","-1e600"}, //UNDERFLOW
    { "120.1423", "1230.213 as", ".010101" } // SUCCESS
};

class testDouble{
    public:
    testDouble(){
        std::cout << "Testing conversion to doubles\n";
        std::cout << "1. Inconvertible string inputs\n";
        for(auto input : sinputs[0]){
            double result = 0;
            assert(str2d(&result, input.c_str(), nullptr) == STR2NUM_INCONVERTIBLE);
        }

        std::cout << "2. OverFlow string inputs\n";
        for(auto input : sinputs[1]){
            double result = 0;
            char ** inputPtr = nullptr;
            assert(str2d(&result, input.c_str(), inputPtr) == STR2NUM_OVERFLOW);
            assert(str2d(&result, input.c_str()) == STR2NUM_OVERFLOW);
        }

        std::cout << "3. UnderFlow string inputs\n";
        for(auto input : sinputs[2]){
            double result = 0;
            char ** inputPtr = nullptr;
            assert(str2d(&result, input.c_str(), inputPtr) == STR2NUM_UNDERFLOW);
            assert(str2d(&result, input.c_str()) == STR2NUM_UNDERFLOW);
        }

        std::cout << "4. Successful string inputs\n";
        for(auto input : sinputs[3]){
            double result = 0;
            char ** inputPtr = nullptr;
            char ** checkPtr = nullptr;
            assert(str2d(&result, input.c_str(), inputPtr) == STR2NUM_SUCCESS);
            assert( ( result == strtod(input.c_str(), checkPtr) ) && (checkPtr == inputPtr) );
        }
        std::cout << "Test complete\n\n";
    }
};

class testFloat{
    public:
    testFloat(){
        std::cout << "Testing conversion to floats\n";
        std::cout << "1. Inconvertible string inputs\n";
        for(auto input : sinputs[0]){
            float result = 0;
            assert(str2f(&result, input.c_str(), nullptr) == STR2NUM_INCONVERTIBLE);
        }

        std::cout << "2. OverFlow string inputs\n";
        for(auto input : sinputs[1]){
            float result = 0;
            char ** inputPtr = nullptr;
            assert(str2f(&result, input.c_str(), inputPtr) == STR2NUM_OVERFLOW);
            assert(str2f(&result, input.c_str()) == STR2NUM_OVERFLOW);
        }

        std::cout << "3. UnderFlow string inputs\n";
        for(auto input : sinputs[2]){
            float result = 0;
            char ** inputPtr = nullptr;
            assert(str2f(&result, input.c_str(), inputPtr) == STR2NUM_UNDERFLOW);
            assert(str2f(&result, input.c_str()) == STR2NUM_UNDERFLOW);
        }

        std::cout << "4. Successful string inputs\n";
        for(auto input : sinputs[3]){
            float result = 0;
            char ** inputPtr = nullptr;
            char ** checkPtr = nullptr;
            assert(str2f(&result, input.c_str(), inputPtr) == STR2NUM_SUCCESS);
            assert( ( result == strtof(input.c_str(), checkPtr) ) && (checkPtr == inputPtr) );
        }
        std::cout << "Test complete\n\n";
    }
};
#endif