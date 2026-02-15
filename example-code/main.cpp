/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include "exampleTests.hpp"
#include "unnamedparameter.hpp"

int main()
{
    unnamedparameter();
    
    if (runTests()) {
        return 0;
    }

    return 1;
}
    
