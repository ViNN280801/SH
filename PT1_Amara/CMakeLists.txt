cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(pt1_amara
    VERSION 1.0
    DESCRIPTION "Practical task 1. 9 variant. Amara Kuruma"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(task1 task1.c)
add_executable(task2 task2.c)
