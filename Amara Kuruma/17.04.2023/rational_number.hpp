#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <iostream>
#include <limits>

class rational_number
{
private:
    double m_numerator;
    double m_denumerator;

protected:
    static constexpr double kdefault_numerator{0.0};
    static constexpr double kdefault_denumerator{1.0};

public:
    // Default ctor
    explicit rational_number();

    explicit rational_number(double, double);

    // Copy ctor
    explicit rational_number(const rational_number &) = default;

    // Move ctor
    explicit rational_number(rational_number &&) = default;

    // Copy-assignment operator
    rational_number &operator=(const rational_number &) = default;

    // Move-assignment operator
    rational_number &operator=(rational_number &&) noexcept = default;

    // Virtual dtor
    virtual ~rational_number() = default;

    // Getters and setters for numerator and denumerator
    double getNumerator() const;
    double getDenumerator() const;
    inline void setNumerator(double);
    inline void setDenumerator(double);

    // Converts obj of 'rational_number' to "double"
    inline double to_double() const noexcept { return (m_denumerator == 0.0)
                                                          ? std::numeric_limits<double>::quiet_NaN()
                                                          : m_numerator / m_denumerator; }

    friend std::ostream &operator<<(std::ostream &out, const rational_number &num)
    {
        out << num.to_double();
        return out;
    }

    friend inline bool operator==(const rational_number &a, const rational_number &b)
    {
        return a.to_double() == b.to_double();
    }

    friend inline bool operator!=(const rational_number &a, const rational_number &b)
    {
        return a.to_double() != b.to_double();
    }

    friend inline bool operator<(const rational_number &a, const rational_number &b)
    {
        return a.to_double() < b.to_double();
    }

    friend inline bool operator>(const rational_number &a, const rational_number &b)
    {
        return a.to_double() > b.to_double();
    }
};

#endif // !RATIONAL_NUMBER_HPP