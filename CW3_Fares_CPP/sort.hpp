#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

using size_t = std::size_t;
using arrInt = std::vector<int>;
using matrixInt = std::vector<std::vector<int>>;

class ISort
{
private:
    // Count of compares
    int m_compCount;

    // Count of substitutions
    int m_subsCount;

    static const int kdefault_compCount = 0;
    static const int kdefault_subsCount = 0;

protected:
    // Clears out specified object
    void clearObj(ISort &);

    // Copying passed object to the current
    void copyObj(ISort const &);

    // Converts integer matrix (2d array) to 1d array and returns it
    arrInt matrixIntToArray(matrixInt const &) const;

    // Converts 1d array of integer to matrix (2d array) and returns it
    // As a second param gets rows of future matrix, as a third - columns
    matrixInt arrIntToMatrix(arrInt const &, size_t const &, size_t const &) const;

public:
    // Default constructor
    explicit ISort();

    // Copy constructor
    explicit ISort(ISort const &);

    // Move constructor
    explicit ISort(ISort &&);

    // Copy assignment operator
    ISort &operator=(ISort const &);

    // Move assignment operator
    ISort &operator=(ISort &&) noexcept;

    // Destructor
    virtual ~ISort();

    // Returns count of the compares
    inline int getCompCount() const noexcept;

    // Modifies private data member -> count of compares
    inline void setCompCount(int const &);

    // Returns count of the substitutions
    inline int getSubsCount() const noexcept;

    // Modifies private data member -> count of substitutions
    inline void setSubsCount(int const &);

    // Increases by 1 counter of compares
    inline void increaseCompCount() noexcept;

    // Increases by 1 counter of substitutions
    inline void increaseSubsCount() noexcept;

    // Swaps integer values
    inline void swap(int &, int &) noexcept;

    // Prints count of compares and substitutions
    virtual void printStatistics();

    // Returns count of compares and count of substitutions as a pair of values
    virtual inline std::pair<int, int> getStatistics() const;

    // Sorting matrix. Pure virtual function based on
    // which will be implemented various sorting algorithms for matrix
    virtual void sort(matrixInt &) = 0;
};

class BubbleSort : ISort
{
public:
    void sort(matrixInt &) override;
    virtual void printStatistics();
    virtual std::pair<int, int> getStatistics() const;
};

class SelectionSort : ISort
{
public:
    void sort(matrixInt &) override;
    virtual void printStatistics();
    virtual std::pair<int, int> getStatistics() const;
};

class InsertionSort : ISort
{
public:
    void sort(matrixInt &) override;
    virtual void printStatistics();
    virtual std::pair<int, int> getStatistics() const;
};

class ShellSort : ISort
{
public:
    void sort(matrixInt &) override;
    virtual void printStatistics();
    virtual std::pair<int, int> getStatistics() const;
};

class QuickSort : ISort
{
private:
    // Quick sort an array
    void qsort(arrInt &arr, size_t low, size_t high);

public:
    void sort(matrixInt &) override;
    virtual void printStatistics();
    virtual std::pair<int, int> getStatistics() const;
};

#endif // SORT_HPP
