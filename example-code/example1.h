/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#ifndef EXAMPLE1_H
#define EXAMPLE1_H

#include <stdint.h>
#include <stddef.h>

#define N 10
#define MYMACRO(x) ((x) + 1)

typedef bool MyBoolType;

typedef enum MyCStyleEnum {
    MyCStyleEnum_Option1 = 0,
    MyCStyleEnum_Option2,
    MyCStyleEnum_COUNT
} MyCStyleEnum;

static inline int exampleFunction1(void)
{
    int32_t k, result = 0;
    for (k=0; k < N; ++k) {
        result +=  MYMACRO(2)*k;
    }
    return result;
}


static inline MyBoolType exampleFunction2(void* ptr)
{
    if (ptr == NULL) {
        return false;
    }
    return true;
}

#endif // EXAMPLE1_H
