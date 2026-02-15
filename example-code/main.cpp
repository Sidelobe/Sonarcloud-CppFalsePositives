/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include "exampleTests.hpp"
#include <functional>

float InlineFunction(float a, float b)
{
    return a + b;
}
float InlineFunction2(float, float b)
{
    // Triggers: cpp:S926 "Parameters in a function prototype should be named"
    // BUT, if I name it, it will trigger cpp:S1172 "Remove the unused parameter or make it unnamed"
    return b;
}

int main()
{
    // unrelated:
    std::vector<std::function<float(float, float)>> functions;
    functions.push_back(InlineFunction);
    functions.push_back(InlineFunction2);
    
    // Main: replicated Cpp rules to C code
    if (runTests()) {
        return 0;
    }
    return 1;
}
    
