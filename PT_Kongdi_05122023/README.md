# Square Matrix Arrangement Program

This C program takes user input to create a square matrix based on the size provided. It arranges the elements in a specific pattern using the input real numbers.

## Description

The program includes several functions:

1. `get_matrix_size()`: Prompts the user to input the size of the square matrix. It ensures the size is within the range (less than 8) and returns the specified size.

2. `get_real_numbers(int n)`: Allocates memory for an array of real numbers based on the input count. It prompts the user to input each real number, ensuring successful memory allocation and returns the array.

3. `arrange_nums_in_matrix(double const *const nums, int n)`: Arranges the provided real numbers in a square matrix based on a specified pattern. The matrix elements are arranged based on the zigzag pattern (alternating between filling downwards and upwards).

4. `print_sqmatrix(double const *const *const p, int n)`: Prints the square matrix with elements of type `double`.

5. `main()`: Executes the program, taking user input for the size of the square matrix and the real numbers to fill the matrix. It prints the elements provided by the user, constructs and prints the arranged square matrix, and deallocates the allocated memory to prevent memory leaks.

## Usage

1. Compile the C program using a C compiler (e.g., GCC).

```bash
gcc main.c -Wall -Wpedantic -Wextra -o main
```

2. Run

```bash
./main
```

3. Follow the prompts to input the size of the square matrix and the real numbers to arrange within the matrix.

4. The program will display the elements provided by the user and the arranged square matrix based on the specified pattern.

## Memory leaks

Using [valgrind](https://valgrind.org) tool for check of any memory leaks or errors in a program:

```console
==62337== Memcheck, a memory error detector
==62337== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==62337== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==62337== Command: ./main
==62337== 
Enter size of the square matrix (size < 8): 4
nums[0] = -5
nums[1] = 5
nums[2] = 7
nums[3] = 1
nums[4] = 9
nums[5] = 6
nums[6] = -6
nums[7] = -2347.6589
nums[8] = 1
nums[9] = 3
nums[10] = -1
nums[11] = -3
nums[12] = 567
nums[13] = 96
nums[14] = -2.234
nums[15] = -0.0000005
Elements:
-5.000000 5.000000 7.000000 1.000000 9.000000 6.000000 -6.000000 -2347.658900 1.000000 3.000000 -1.000000 -3.000000 567.000000 96.000000 -2.234000 -0.000000 

Matrix:
-5.000000	-2347.658900	1.000000	-0.000000	
5.000000	-6.000000	3.000000	-2.234000	
7.000000	6.000000	-1.000000	96.000000	
1.000000	9.000000	-3.000000	567.000000	
==62337== 
==62337== HEAP SUMMARY:
==62337==     in use at exit: 0 bytes in 0 blocks
==62337==   total heap usage: 8 allocs, 8 frees, 2,336 bytes allocated
==62337== 
==62337== All heap blocks were freed -- no leaks are possible
==62337== 
==62337== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If you want to use valgrind with full check and with lists of errors, run following command:

```console
valgrind --leak-check=full -s ./main
```

If you want to redirect valgrind checking to a file, use command below:

```console
valgrind --leak-check=full -s --log-file="memory.log" ./main
```

As you can see, there is no any problems associated with memory.
