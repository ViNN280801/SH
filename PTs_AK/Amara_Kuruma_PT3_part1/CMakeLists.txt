cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(pt_3_part1
    VERSION 1.0
    DESCRIPTION "Practice work #3 part 1. Evaluating the effectiveness of the algorithms"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-lm -Wall -Wpedantic -Wextra -O2")

add_executable(main sorts.c test.c)
