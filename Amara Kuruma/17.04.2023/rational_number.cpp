#include <stdexcept>

#include "rational_number.hpp"

rational_number::rational_number() : m_numerator(kdefault_numerator),
                                     m_denumerator(kdefault_denumerator) {}

rational_number::rational_number(double numer, double denum)
{
    if (denum == 0.0)
        throw std::invalid_argument("Error: Invalid argument - denumerator can't equals to null. Can't divise by null!");
    else
    {
        m_numerator = numer;
        m_denumerator = denum;
    }
}

double rational_number::getNumerator() const { return m_numerator; }

double rational_number::getDenumerator() const { return m_denumerator; }

void rational_number::setNumerator(double numerator) { m_numerator = numerator; }

void rational_number::setDenumerator(double denumerator)
{
    if (denumerator == 0.0)
        throw std::invalid_argument("Error: Invalid argument - denumerator can't equals to null. Can't divise by null!");
    else
        m_denumerator = denumerator;
}
