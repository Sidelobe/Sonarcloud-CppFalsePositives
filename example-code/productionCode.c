/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include <stddef.h>
#include <stdbool.h>
#include "example1.h"

bool myCFunction(void)
{
    if (exampleFunction1() > 2) {
        return true;
    }
    if (exampleFunction2(NULL) == false) {
        return true;
    }
    if (MyCStyleEnum_COUNT + exampleFunction1() > 2) {
        return true;
    }
    
}
