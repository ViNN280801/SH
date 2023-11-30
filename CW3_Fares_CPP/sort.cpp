#include <iostream>
#include <ctime>

#include "sort.hpp"

void ISort::clearObj(ISort &obj)
{
    obj.m_compCount = 0;
    obj.m_subsCount = 0;
}

void ISort::copyObj(ISort const &obj)
{
    m_compCount = obj.m_compCount;
    m_subsCount = obj.m_subsCount;
}

arrInt ISort::matrixIntToArray(matrixInt const &matrix) const
{
    arrInt arr(matrix.size() * matrix.at(0).size());
    size_t idx{};
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            arr.at(idx) = matrix.at(row).at(col);
            idx++;
        }
    }
    return arr;
}

matrixInt ISort::arrIntToMatrix(arrInt const &arr, size_t const &rows, size_t const &cols) const
{
    if (arr.size() != rows * cols)
    {
        std::cout << "The size of array and matrix don't match. Returning empty matrix..." << std::endl;
        return matrixInt{{}};
    }

    matrixInt matrix(rows, arrInt(cols));
    size_t idx{};
    for (size_t row{}; row < rows && (idx < arr.size()); row++)
    {
        for (size_t col{}; col < cols; col++)
        {
            matrix.at(row).at(col) = arr.at(idx);
            idx++;
        }
    }
    return matrix;
}

ISort::ISort() : m_compCount(kdefault_compCount), m_subsCount(kdefault_subsCount) {}

ISort::ISort(ISort const &rhs) { copyObj(rhs); }

ISort::ISort(ISort &&lhs)
{
    copyObj(lhs);
    clearObj(lhs);
}

ISort &ISort::operator=(ISort const &rhs)
{
    if (this == &rhs)
        return *this;

    copyObj(rhs);

    return *this;
}

ISort &ISort::operator=(ISort &&lhs) noexcept
{
    if (this == &lhs)
        return *this;

    clearObj(*this);
    copyObj(lhs);
    clearObj(lhs);

    return *this;
}

ISort::~ISort() { clearObj(*this); }

int ISort::getCompCount() const noexcept { return m_compCount; }

void ISort::setCompCount(int const &newCompCount) { m_compCount = newCompCount; }

int ISort::getSubsCount() const noexcept { return m_subsCount; }

void ISort::setSubsCount(int const &newSubsCount) { m_subsCount = newSubsCount; }

void ISort::increaseCompCount() noexcept { m_compCount++; }

void ISort::increaseSubsCount() noexcept { m_subsCount++; }

void ISort::swap(int &a, int &b) noexcept
{
    a += b;
    b -= a;
    b *= (-1);
    a -= b;

    increaseSubsCount();
}

void ISort::printStatistics()
{
    std::cout << "Count of compares: " << getCompCount() << std::endl;
    std::cout << "Count of substitutions: " << getSubsCount() << std::endl;
}

std::pair<int, int> ISort::getStatistics() const { return std::make_pair(getCompCount(), getSubsCount()); }

void BubbleSort::sort(matrixInt &matrix)
{
    for (size_t row_1{}; row_1 < matrix.size(); row_1++)
        for (size_t row_2{}; row_2 < matrix.size(); row_2++)
            for (size_t col_1{}; col_1 < matrix.at(row_1).size(); col_1++)
                for (size_t col_2{}; col_2 < matrix.at(row_2).size(); col_2++)
                    if (matrix.at(row_1).at(col_1) < matrix.at(row_2).at(col_2))
                    {
                        increaseCompCount();
                        swap(matrix.at(row_1).at(col_1), matrix.at(row_2).at(col_2));
                    }
}

void BubbleSort::printStatistics() { ISort::printStatistics(); }

std::pair<int, int> BubbleSort::getStatistics() const { return ISort::getStatistics(); }

void SelectionSort::sort(matrixInt &matrix)
{
    for (size_t row{}; row < matrix.size(); row++)
    {
        for (size_t col{}; col < matrix.at(row).size(); col++)
        {
            size_t minRow{row}, minCol{col};
            int min{matrix.at(row).at(col)};

            for (size_t j{col + 1}; j < matrix.at(row).size(); j++)
            {
                if (matrix.at(row).at(j) < min)
                {
                    increaseCompCount();
                    minRow = row;
                    minCol = j;
                    min = matrix.at(row).at(j);
                }
            }
            for (size_t i{row + 1}; i < matrix.size(); i++)
            {
                for (size_t j{}; j < matrix.at(row).size(); j++)
                {
                    if (matrix.at(i).at(j) < min)
                    {
                        increaseCompCount();
                        minRow = i;
                        minCol = j;
                        min = matrix.at(i).at(j);
                    }
                }
            }
            matrix.at(minRow).at(minCol) = matrix.at(row).at(col);
            swap(matrix.at(row).at(col), min);
        }
    }
}

void SelectionSort::printStatistics() { ISort::printStatistics(); }

std::pair<int, int> SelectionSort::getStatistics() const { return ISort::getStatistics(); }

void InsertionSort::sort(matrixInt &matrix)
{
    arrInt arr(matrixIntToArray(matrix));
    for (size_t i{1}; i < arr.size(); i++)
    {
        int val{arr.at(i)};
        size_t pos{i - 1};
        while (pos < arr.size() && arr.at(pos) > val)
        {
            increaseCompCount();
            arr.at(pos + 1) = arr.at(pos);
            pos--;
        }
        arr.at(pos + 1) = val;
        increaseSubsCount();
    }
    matrix = arrIntToMatrix(arr, matrix.size(), matrix.at(0).size());
}

void InsertionSort::printStatistics() { ISort::printStatistics(); }

std::pair<int, int> InsertionSort::getStatistics() const { return ISort::getStatistics(); }

void ShellSort::sort(matrixInt &matrix)
{
    arrInt arr(matrixIntToArray(matrix));
    for (size_t interval{arr.size() / 2}; interval > 0; interval /= 2)
    {
        for (size_t i{}; i < arr.size(); i++)
        {
            int val{arr.at(i)};
            size_t j{};
            for (j = i; (j >= interval) && (arr.at(j - interval) > val); j -= interval)
            {
                increaseCompCount();
                arr.at(j) = arr.at(j - interval);
            }
            arr.at(j) = val;
            increaseSubsCount();
        }
    }
    matrix = arrIntToMatrix(arr, matrix.size(), matrix.at(0).size());
}

void ShellSort::printStatistics() { ISort::printStatistics(); }

std::pair<int, int> ShellSort::getStatistics() const { return ISort::getStatistics(); }

void QuickSort::qsort(arrInt &arr, size_t low, size_t high)
{
    size_t i{low}, j{high};
    // Select pivot value
    int pivot{arr.at((i + j) / 2)}, tmp{};

    while (i <= j && i < arr.size() && j < arr.size())
    {
        while (arr.at(i) < pivot && i < arr.size())
            i++;
        while (arr.at(j) > pivot && j < arr.size())
            j--;
        if (i <= j && i < arr.size() && j < arr.size())
        {
            increaseCompCount();
            tmp = arr.at(i);
            arr.at(i) = arr.at(j);
            arr.at(j) = tmp;
            increaseSubsCount();
            i++;
            j--;
        }
    }
    // Recursive call sorting to left side from pivot
    if (j > low && j < arr.size())
    {
        increaseCompCount();
        qsort(arr, low, j);
    }
    // Recursive call sorting to right side from pivot
    if (i < high && i < arr.size())
    {
        increaseCompCount();
        qsort(arr, i, high);
    }
}

void QuickSort::sort(matrixInt &matrix)
{
    arrInt arr(matrixIntToArray(matrix));
    qsort(arr, 0, arr.size() - 1);
    matrix = arrIntToMatrix(arr, matrix.size(), matrix.at(0).size());
}

void QuickSort::printStatistics() { ISort::printStatistics(); }

std::pair<int, int> QuickSort::getStatistics() const { return ISort::getStatistics(); }
