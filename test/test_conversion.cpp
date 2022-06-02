//  SPDX-FileCopyrightText: 2022 Kish Jadhav
//  SPDX-License-Identifier: MIT License
#include "str2num.h"
#include <iostream>
#include <assert.h>
#include "test_floating.hpp"
class TestINT{
    public:
    TestINT(){
        std::cout << "Testing conversion to int\n";
        test_conversion();
        test_overflow();
        test_underflow();
        test_incovertible();
        std::cout << "Test complete\n\n";
    }
    private:
    void test_conversion(){
        int result = 0;
        str2int(&result, "123", nullptr, 10);
        assert(result == 123);
        std::string str = "2030300 This is test";
        char *ptr;
        str2int(&result, str.c_str(), &ptr, 10);
        assert(result == 2030300);
        assert(std::string(ptr) == " This is test");
    }
    void test_overflow(){
        std::string str = "9999999999";
        int result = 0;
        str2num_errno error_int = str2int(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_OVERFLOW );
    }

    void test_underflow(){
        std::string str = "-9999999999";
        int result = 0;
        str2num_errno error_int = str2int(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_UNDERFLOW );
    }
    void test_incovertible(){
        std::string str = "";
        int result = 0;
        str2num_errno error_int = str2int(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_INCONVERTIBLE );
    }
};

class TestUINT{
    public:
    TestUINT(){
        std::cout << "Testing conversion to uint\n";
        test_conversion();
        test_overflow();
        test_underflow();
        test_incovertible();
        std::cout << "Test complete\n\n";
    }
    private:
    void test_conversion(){
        unsigned int result = 0;
        str2uint(&result, "123", nullptr, 10);
        assert(result == 123);
        std::string str = "2030300 This is test";
        char *ptr;
        str2uint(&result, str.c_str(), &ptr, 10);
        assert(result == 2030300);
        assert(std::string(ptr) == " This is test");
    }
    void test_overflow(){
        std::string str = "9999999999";
        unsigned int result = 0;
        str2num_errno error_int = str2uint(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_OVERFLOW );
    }

    void test_underflow(){
        std::string str = "-9999999999";
        unsigned int  result = 0;
        str2num_errno error_int = str2uint(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_UNDERFLOW );
    }
    void test_incovertible(){
        std::string str = "";
        unsigned int  result = 0;
        str2num_errno error_int = str2uint(&result, str.c_str(), nullptr, 10);
        assert(error_int == STR2NUM_INCONVERTIBLE );
    }
};

int main(){
    // TestINT();
    // TestUINT();
    testDouble();
    testFloat();
    return 0;
}