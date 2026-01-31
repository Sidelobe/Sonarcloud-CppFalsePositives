/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include "exampleTests.hpp"
#include <iostream>

extern "C" {
#include "example1.h"
}

bool runTests()
{
    if (exampleFunction1() > 2) {
        return true;
    }
    if (exampleFunction2(nullptr) == false) {
        return true;
    }
    if (MyCStyleEnum_COUNT + exampleFunction1() > 2) {
        return true;
    }
        
    std::cout << "All tests passed." << std::endl;
    
    return false;
}
