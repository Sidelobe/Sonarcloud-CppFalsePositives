/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#ifndef EXAMPLE1_H
#define EXAMPLE1_H

#include <stdint.h>

#define N 10

static inline int exampleFunction1(void)
{
    int32_t k, result = 0;
    for (k=0; k < N; ++k) {
        result += 2*k;
    }
    return result;
}

#endif // EXAMPLE1_H
