gcc -c src/generate_keys.c -Wall -Wpedantic -Wextra -o src/generate_keys.o
gcc -c src/hash_table.c -Wall -Wpedantic -Wextra -o src/hash_table.o
gcc -c src/hash_table_main.c -Wall -Wpedantic -Wextra -o src/hash_table_main.o
gcc src/generate_keys.o src/hash_table.o src/hash_table_main.o -Wall -Wpedantic -Wextra -o hash_table

gcc -c src/splay_tree.c -Wall -Wpedantic -Wextra -o src/splay_tree.o
gcc -c src/splay_tree_main.c -Wall -Wpedantic -Wextra -o src/splay_tree_main.o
gcc src/generate_keys.o src/splay_tree.o src/splay_tree_main.o -Wall -Wpedantic -Wextra -o splay_tree

rm src/*.o
