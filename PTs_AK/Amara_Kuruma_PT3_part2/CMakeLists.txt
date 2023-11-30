cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(pt_3_part2
    VERSION 1.0
    DESCRIPTION "Practice work #3 part 2. Evaluating the effectiveness of the algorithms"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra -O2")

add_executable(splay_tree src/generate_keys.c src/splay_tree.c src/splay_tree_main.c)
add_executable(hash_table src/generate_keys.c src/hash_table.c src/hash_table_main.c)
