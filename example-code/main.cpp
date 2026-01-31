/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include "exampleTests.hpp"

int main()
{
    if (runTests()) {
        return 0;
    }
    return 1;
}
