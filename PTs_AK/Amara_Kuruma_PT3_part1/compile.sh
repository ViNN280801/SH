gcc -c sorts.c -lm -Wall -Wpedantic -Wextra -o sorts.o
gcc -c test.c -lm -Wall -Wpedantic -Wextra -o test.o
gcc sorts.o test.o -lm -Wall -Wpedantic -Wextra -O2 -o main

rm *.o
