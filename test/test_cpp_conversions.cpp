#include "str2num.hpp"
#include <iostream>
#include <assert.h>

class asdsad{
    public:
    asdsad(){
        std::cout << "Testing conversion to int\n";
        test_conversion();
        std::cout << "Test complete\n\n";
    }
    private:
    void test_conversion(){
        std::string str = "123";
        auto result = s2n::safe_stoi(str);
        assert(result.has_value() && result.value() == 123);
    }
};

int main(){
    asdsad();
}