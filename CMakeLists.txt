cmake_minimum_required(VERSION 3.10)
project(EventSystem)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# Add all the .cpp files in the src directory to the build
file(GLOB SOURCES "src/*.cpp" tests.cpp)

# Add the executable
add_executable(runTests ${SOURCES})



