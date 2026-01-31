cmake_minimum_required(VERSION 3.10)

project(ExampleProject LANGUAGES C CXX)

# Set C and C++ standards
set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 17)

# Collect all C and C++ source files in example-code/
file(GLOB EXAMPLE_SOURCES
    example-code/*.[c,h]*
)

# Create an executable from all collected sources 
add_executable(example-app ${EXAMPLE_SOURCES})
