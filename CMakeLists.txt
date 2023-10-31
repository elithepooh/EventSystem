cmake_minimum_required(VERSION 3.10)
project(EventSystem)

set(CMAKE_CXX_STANDARD 11)


# Your source files
set(SOURCE_FILES event_system.cpp player.cpp tests.cpp)

add_executable(EventSystem ${SOURCE_FILES})
