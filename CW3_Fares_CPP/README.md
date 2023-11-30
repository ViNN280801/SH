# Some sorting methods on matrix

## Description

### Rus

Необходимо составить программу для сортировки массива данных методами: пузырьковая, выбором, вставками, Шелла и быстрая. Вывести на экран неупорядоченный (1 раз) и упорядоченные (для каждого из методов) массивы данных. Составить сравнительную таблицу эффективности методов, в которой необходимо указать число сравнений и перестановок переменных в каждом методе сортировки.
Неупорядоченная матрица из N строк и M столбцов задается и заполняется один раз (с клавиатуры, из файла или случайными числами), далее она используется для каждого из методов сортировки.
Реализовать абстрактный базовый класс ISort, содержащий чистый виртуальный метод sort и необходимые счетчики, от которого наследовать подклассы для реализации сортировок.
Упорядочить каждую четную строку по возрастанию, затем каждый четный столбец по возрастанию.

### Eng

It is necessary to create a program for sorting the data array using the following methods: bubble, selection, inserts, Shell and fast. Display unordered (1 time) and ordered (for each of the methods) data arrays. Make a comparative table of the effectiveness of the methods, in which it is necessary to specify the number of comparisons and permutations of variables in each sorting method.
An unordered matrix of N rows and M columns is set and filled in once (from the keyboard, from a file, or with random numbers), then it is used for each of the sorting methods.
Implement an abstract ISort base class containing a pure virtual sort method and the necessary counters from which to inherit subclasses for implementing sorts.
Arrange each even row in ascending order, then each even column in ascending order.

## Program

As the basis of the array or matrix (2d array) were taken std::vector<> and std::vector<std::vector<>> correspondingly. Classes "InsertionSort", "ShellSort" and "QuickSort" use tricky movement - at first, there each of methods converts matrix to an array, sorting it and then converts array back to the matrix.
For example, following lines demonstrates it:

```cpp
arrInt arr(matrixIntToArray(matrix));
qsort(arr, 0, arr.size() - 1);
matrix = arrIntToMatrix(arr, matrix.size(), matrix.at(0).size());
```

"arrInt" is the type alias defined in "sort.hpp" header file, that corresponds to std::vector<int>:

```cpp
using size_t = std::size_t;
using arrInt = std::vector<int>;
using matrixInt = std::vector<std::vector<int>>;
```

## Compiling

Compiling with CMake:

```console
$ cmake .
-- The CXX compiler identification is GNU 12.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.7s)
-- Generating done (0.0s)
-- Build files have been written to: $PATH
$ cmake --build .
[ 33%] Building CXX object CMakeFiles/main.dir/sort.cpp.o
[ 66%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
$
```

Command "cmake --build ." can replaced by "make":

```console
$ cmake .
-- The CXX compiler identification is GNU 12.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.7s)
-- Generating done (0.0s)
-- Build files have been written to: $PATH
$ make
[ 33%] Building CXX object CMakeFiles/main.dir/sort.cpp.o
[ 66%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
$
```

Or use commands of compiler GNU GCC:

```console
$ gcc -c sort.cpp -o sort.o
$ gcc -c main.cpp -o main.o
$ gcc -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra sort.o main.o -o main
$ ./main
```

## Examples

There is some examples of sorting methods with 1 matrix and summarize results in the table.

#### Original matrix

```
Original matrix: 
49	41	46	14	71	98	
92	82	45	25	11	55	
46	53	39	88	22	11	
99	87	42	50	96	34	
32	37	30	29	68	27
```

#### Bubble sort

```
After bubble sort: 
11	11	14	22	25	27	
29	30	32	34	37	39	
41	42	45	46	46	49	
50	53	55	68	71	82	
87	88	92	96	98	99	
Count of compares: 276
Count of substitutions: 276
```

#### Selection sort

```
After selection sort: 
11	11	14	22	25	27	
29	30	32	34	37	39	
41	42	45	46	46	49	
50	53	55	68	71	82	
87	88	92	96	98	99	
Count of compares: 69
Count of substitutions: 30
```

#### Insertion sort

```
After insertion sort: 
11	11	14	22	25	27	
29	30	32	34	37	39	
41	42	45	46	46	49	
50	53	55	68	71	82	
87	88	92	96	98	99	
Count of compares: 248
Count of substitutions: 29
```

#### Shell sort

```
After Shell sort: 
11	11	14	22	25	27	
29	30	32	34	37	39	
41	42	45	46	46	49	
50	53	55	68	71	82	
87	88	92	96	98	99	
Count of compares: 67
Count of substitutions: 120
```

#### Quick sort

```
After quick sort: 
11	11	14	22	25	27	
29	30	32	34	37	39	
41	42	45	46	46	49	
50	53	55	68	71	82	
87	88	92	96	98	99	
Count of compares: 73
Count of substitutions: 47
```

Sorting was also done with others matrix which sizes was (2x2, 3x3, 5x4, 5x5, 5x6, 7x7, 8x9, 10x9, 10x10). Below is presented performance table which is show how many compares and substitutions did take any one sorting method or another.

### Summarize results

```
-----------------------------------------------------------------------------------------
| Matrix size | Bubble sort | Selection sort | Insertion sort | Shell sort | Quick sort |
-----------------------------------------------------------------------------------------
|Rows     Cols|Comps    Subs|Comps       Subs|Comps       Subs|Comps   Subs|Comps  Subs |
|2           3|14         14|6              6|8              5|6         12|10         6|
|3           3|29         29|10             9|15             8|9         27|16        10|
|5           4|107       107|35            20|94            19|32        80|47        29|
|5           5|147       147|45            25|144           24|58       100|55        33|
|5           6|209       209|63            30|190           29|62       120|68        43|
|7           7|584       584|123           49|653           48|151      245|118       78|
|8           9|1091     1091|196           72|1356          71|197      432|188      128|
|10          9|1522     1522|258           90|1974          89|307      540|253      173|
|10         10|1748     1748|277          100|2380          99|365      600|279      189|
-----------------------------------------------------------------------------------------
* Cols - count of columns in a matrix
** Comps - count of the compares in each type of sort
*** Subs - count of the substitions in each type of sort
```
