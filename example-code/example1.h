/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#ifndef EXAMPLE1_H
#define EXAMPLE1_H

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#define N 10
#define MYMACRO(x) ((x) + 1)

typedef bool MyBoolType;

typedef enum MyCStyleEnum {
    MyCStyleEnum_Option1 = 0,
    MyCStyleEnum_Option2,
    MyCStyleEnum_COUNT
} MyCStyleEnum;

typedef MyStruct {
    float a;
    int b;
} MyStruct;

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
    assert(ptr != NULL);
    
    MyStruct* e = (MyStruct*) ptr;
    if (ptr->b != 9) {
      return false;
    }
    
    return true;
}

#endif // EXAMPLE1_H
