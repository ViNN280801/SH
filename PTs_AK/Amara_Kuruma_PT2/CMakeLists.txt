cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(pt_2
    VERSION 1.0
    DESCRIPTION "Practice work #2. Nonlinear data structure"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra -O2")

add_executable(digger src/digger_list.c src/digger_matrix.c src/main.c)
