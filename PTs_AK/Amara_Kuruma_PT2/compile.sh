gcc -c src/digger_list.c -Wall -Wpedantic -Wextra -o src/digger_list.o
gcc -c src/digger_matrix.c -Wall -Wpedantic -Wextra -o src/digger_matrix.o
gcc -c src/main.c -Wall -Wpedantic -Wextra -o src/main.o
gcc src/digger_list.o src/digger_matrix.o src/main.o -Wall -Wpedantic -Wextra -o digger

rm src/*.o
