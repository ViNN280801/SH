cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(cw3_fares_cpp
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(main sort.cpp main.cpp)
