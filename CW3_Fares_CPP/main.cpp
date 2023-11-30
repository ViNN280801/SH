#include <iostream>
#include <ctime>
#include <iomanip>
#include <iterator>

#include "sort.hpp"

static const int SORT_TYPES{5};

// Increase this variable if your table contents many rows (30+)
static const size_t RANGE_TO_FIND{100UL};

// Returns matrix of integers that is filled with random numbers
// Gets rows as a first parameter and columns as a second
// Third param - offset, fourth - range
matrixInt fillMatrixRandom(size_t const &rows, size_t const &cols,
                           int const &offset = 1, int const &range = 100)
{
    srand(time(nullptr));

    // Allocating necessary memory for matrix
    matrixInt matrix(rows, arrInt(cols));
    for (size_t row{}; row < rows; row++)
        for (size_t col{}; col < cols; col++)
            matrix.at(row).at(col) = offset + (rand() % range);
    return matrix;
}

// Prints matrix to terminal
void printMatrix(matrixInt const &matrix, char const *msg = "")
{
    std::cout << msg << std::endl;
    for (std::size_t row{}; row < matrix.size(); row++)
    {
        for (std::size_t col{}; col < matrix.at(row).size(); col++)
            std::cout << matrix.at(row).at(col) << '\t';
        std::endl(std::cout);
    }
}

std::vector<std::pair<int, int>> getSummaryStatistics(size_t const &rows, size_t const &cols)
{
    std::vector<std::pair<int, int>> stats;
    stats.push_back(std::make_pair(static_cast<int>(rows), static_cast<int>(cols)));

    matrixInt v(fillMatrixRandom(rows, cols)), vCopy{v};
    printMatrix(v, "Original matrix: ");

    BubbleSort bs;
    bs.sort(v);
    printMatrix(v, "\nAfter bubble sort: ");
    bs.printStatistics();
    std::pair<int, int> bsStat{bs.getStatistics()};
    stats.push_back(bsStat);
    v = vCopy;

    SelectionSort ss;
    ss.sort(v);
    printMatrix(v, "\nAfter selection sort: ");
    ss.printStatistics();
    std::pair<int, int> ssStat{ss.getStatistics()};
    stats.push_back(ssStat);
    v = vCopy;

    InsertionSort is;
    is.sort(v);
    printMatrix(v, "\nAfter insertion sort: ");
    is.printStatistics();
    std::pair<int, int> isStat{is.getStatistics()};
    stats.push_back(isStat);
    v = vCopy;

    ShellSort shs;
    shs.sort(v);
    printMatrix(v, "\nAfter Shell sort: ");
    shs.printStatistics();
    std::pair<int, int> shsStat{shs.getStatistics()};
    stats.push_back(shsStat);
    v = vCopy;

    QuickSort qs;
    qs.sort(v);
    printMatrix(v, "\nAfter quick sort: ");
    qs.printStatistics();
    std::pair<int, int> qsStat{qs.getStatistics()};
    stats.push_back(qsStat);
    v = vCopy;

    return stats;
}

bool isNumInSeq(int const &k, int const &numToFind, size_t const &range = RANGE_TO_FIND)
{
    // Our sequence described as following: a_n = 6*n - k (where k is 5, 4, 3, ..., 1)
    arrInt arr;
    for (size_t i{}; i < range * range; i++)
    {
        arr.push_back(6 * i - k);
        if (arr.at(i) == numToFind)
            return true;
    }
    return false;
}

void printSummaryStatistics(std::vector<std::pair<int, int>> const &stat)
{
    std::cout
        << std::endl
        << std::setw(91) << std::setfill('-')
        << "\n|" << std::setw(12) << std::setfill(' ') << "Matrix size" << std::setw(2) << std::setfill(' ') << '|'
        << std::setw(12) << std::setfill(' ') << "Bubble sort" << std::setw(2) << std::setfill(' ') << '|'
        << std::setw(15) << std::setfill(' ') << "Selection sort" << std::setw(2) << std::setfill(' ') << '|'
        << std::setw(15) << std::setfill(' ') << "Insertion sort" << std::setw(2) << std::setfill(' ') << '|'
        << std::setw(11) << std::setfill(' ') << "Shell sort" << std::setw(2) << std::setfill(' ') << '|'
        << std::setw(11) << std::setfill(' ') << "Quick sort" << std::setw(2) << std::setfill(' ') << " |\n"
        << std::setw(90) << std::setfill('-') << '\n'
        << '|' << "Rows" << std::setw(5) << std::setfill(' ') << ' ' << "Cols" << '|'
        << "Comps" << std::setw(4) << std::setfill(' ') << ' ' << "Subs" << '|'
        << "Comps" << std::setw(7) << std::setfill(' ') << ' ' << "Subs" << '|'
        << "Comps" << std::setw(7) << std::setfill(' ') << ' ' << "Subs" << '|'
        << "Comps" << std::setw(3) << std::setfill(' ') << ' ' << "Subs" << '|'
        << "Comps" << std::setw(2) << std::setfill(' ') << ' ' << "Subs"
        << " |\n|";

    for (size_t i{}; i < stat.size(); i++)
    {
        int width{static_cast<int>(std::to_string(stat.at(i).first).length() +
                                   std::to_string(stat.at(i).second).length())};
        if (i % 6 == 0)
        {
            width = 13 - width;
            if (i != 0)
                std::cout << "\n|";
        }
        else if (isNumInSeq(5, i))
            width = 13 - width;
        else if (isNumInSeq(4, i) || isNumInSeq(3, i))
            width = 16 - width;
        else
            width = 12 - width;

        std::cout << stat.at(i).first << std::setw(width) << std::setfill(' ') << ' ' << stat.at(i).second << '|';
    }
    std::cout << '\n'
              << std::setw(90) << std::setfill('-') << ' '
              << "\n* Cols - count of columns in a matrix\n** Comps - count of the compares in each type of sort\n"
              << "*** Subs - count of the substitions in each type of sort" << std::endl;
}

int main()
{
    std::vector<std::pair<int, int>> res(getSummaryStatistics(2, 3));
    std::vector<std::pair<int, int>> vec(getSummaryStatistics(3, 3));

    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(5, 4);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(5, 5);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(5, 6);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(7, 7);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(8, 9);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(10, 9);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));
    vec = getSummaryStatistics(10, 10);
    res.insert(std::end(res), std::cbegin(vec), std::cend(vec));

    printSummaryStatistics(res);

    size_t rows{}, cols{};
    std::cout << "\nEnter count of rows and columns of matrix: ";
    std::cin >> rows >> cols;
    matrixInt matrix(fillMatrixRandom(rows, cols)), matrixCopy{matrix};

    printMatrix(matrix, "Original matrix: ");
    // Arrange each even row in ascending order, then each even column in ascending order
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            if (row % 2 == 0)
            {
                size_t minCol{col};
                int min{matrix.at(row).at(col)};

                for (size_t j{col + 1}; j < matrix.at(row).size(); j++)
                {
                    if (matrix.at(row).at(j) < min)
                    {
                        minCol = j;
                        min = matrix.at(row).at(j);
                    }
                }
                matrix.at(row).at(minCol) = matrix.at(row).at(col);
                std::swap(matrix.at(row).at(col), min);
            }
        }
    }
    printMatrix(matrix, "\nAfter sorting all even rows by ascending order: ");
    matrix = matrixCopy;

    printMatrix(matrix, "\nOriginal matrix: ");
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            if (col % 2 == 0)
            {
                size_t minRow{row};
                int min{matrix.at(row).at(col)};

                for (size_t j{row + 1}; j < matrix.size(); j++)
                {
                    if (matrix.at(j).at(col) < min)
                    {
                        minRow = j;
                        min = matrix.at(j).at(col);
                    }
                }
                matrix.at(minRow).at(col) = matrix.at(row).at(col);
                std::swap(matrix.at(row).at(col), min);
            }
        }
    }
    printMatrix(matrix, "\nAfter sorting all even columns by ascending order: ");
    matrix = matrixCopy;

    printMatrix(matrix, "\nOriginal matrix: ");
    std::cout << "Sort all even rows in ascending order, then sort even cols in asending order in one operation\n";
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            if (row % 2 == 0)
            {
                size_t minCol{col};
                int min{matrix.at(row).at(col)};

                for (size_t j{col + 1}; j < matrix.at(row).size(); j++)
                {
                    if (matrix.at(row).at(j) < min)
                    {
                        minCol = j;
                        min = matrix.at(row).at(j);
                    }
                }
                matrix.at(row).at(minCol) = matrix.at(row).at(col);
                std::swap(matrix.at(row).at(col), min);
            }
        }
    }
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            if (col % 2 == 0)
            {
                size_t minRow{row};
                int min{matrix.at(row).at(col)};

                for (size_t j{row + 1}; j < matrix.size(); j++)
                {
                    if (matrix.at(j).at(col) < min)
                    {
                        minRow = j;
                        min = matrix.at(j).at(col);
                    }
                }
                matrix.at(minRow).at(col) = matrix.at(row).at(col);
                std::swap(matrix.at(row).at(col), min);
            }
        }
    }
    printMatrix(matrix, "\nAfter sorting all even rows and all even columns by ascending order: ");

    return EXIT_SUCCESS;
}
