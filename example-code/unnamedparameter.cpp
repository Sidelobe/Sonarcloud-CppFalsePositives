/** Examples to replicate Sonarqube applying CPP rules to C code
 * https://github.com/Sidelobe/Sonarcloud-CppFalsePositives */

#include <vector>
#include <functional>
#include <memory>

class Parent
{
public:
    Parent(float a) {}
};

class Child : public Parent
{
public:
    Child(float a, float b) : Parent(a) {}
};


class ParentDerived : public Parent
{
public:
    ParentDerived(float a) : Parent(a) {}
};
class ChildDerived : public Child
{
public:
    ChildDerived(float a, float b) : Child(a, b) {}
};



using CreatorFunction = std::function<std::unique_ptr<Parent>(float a, float b)>;


template<typename U, typename std::enable_if_t<!std::is_constructible<U, float, float>::value, int> = 0>
static std::unique_ptr<Parent> create_node(float a, float)
{
    // Triggers: cpp:S926 "Parameters in a function prototype should be named"
    // BUT, if I name it, it will trigger cpp:S1172 "Remove the unused parameter or make it unnamed"

    return std::make_unique<U>(a);
}

template<typename U, typename std::enable_if_t<std::is_constructible<U, float, float>::value, int> = 0>
static std::unique_ptr<Parent> create_node(float a, float b)
{
    return std::make_unique<U>(a, b);
}

void unnamedparameter()
{
    std::vector<CreatorFunction> functions;
    functions.push_back([](float a, float b) { return create_node<ParentDerived>(a, b); });
    functions.push_back([](float a, float b) { return create_node<ChildDerived>(a, b); });
}
