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

typedef struct MyStruct {
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
    if (e->b != 9) {
      return false;
    }
    
    return true;
}

static inline float exampleFunction3(int i)
{
    return (float)(i) / 3.0f; // "C-style and functional notation casts should not be used cpp:S871"
}

static inline void exampleFunction4_clearly_longer_than_the_31chars_allowed(void)
{
    // Identifiers should not be longer than 31 characters cpp:S799
    
    // NOTE: Rule c:S799 is still applicable!
}

#endif // EXAMPLE1_H
