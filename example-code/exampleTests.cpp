/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include "exampleTests.hpp"

extern "C" {
#include "example1.h"
}

bool runTests()
{
    if (exampleFunction1() > N) {
        return true;
    }
    
    return false;
}
