#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <numeric>
#include "Fraction.h"
#include "math_plus.h"
#include <exception>
using namespace std;



Fraction::Fraction() : m_numerator(0), m_denominator(1)
{

}    

Fraction::Fraction(int numerator) : m_numerator(numerator), m_denominator(1)
{

}

Fraction::Fraction(int numerator, int denominator)
    : m_numerator(numerator), m_denominator(denominator) 
{
    check();
    simplify();
}

void Fraction::simplify() 
{
    int gcd = math_plus::greatest_common_divisor(abs(m_numerator), abs(m_denominator));
    m_numerator /= gcd;
    m_denominator /= gcd;
    if (m_denominator < 0) 
    {
        m_denominator *= -1;
        m_numerator *= -1;
    }
}

void Fraction::check() const 
{
    if (m_denominator == 0) 
    {
        throw overflow_error("ERROR!!! Denominator is Zero!!!");
    }
}

int Fraction::toInt() const 
{
    return m_numerator / m_denominator;
}

double Fraction::toReal() const 
{
    return double(m_numerator) / m_denominator;
}

Fraction Fraction::getInverse() const 
{
    return Fraction(m_denominator, m_numerator);
}

bool Fraction::operator==(const Fraction& rhs) const 
{
    return m_numerator == rhs.m_numerator && m_denominator == rhs.m_denominator;
}

bool Fraction::operator!=(const Fraction& rhs) const 
{
    return !(*this == rhs);
}

bool Fraction::operator>(const Fraction& rhs) const 
{
    return toReal() > rhs.toReal();
}

bool Fraction::operator>=(const Fraction& rhs) const 
{
    return *this > rhs || *this == rhs;
}

bool Fraction::operator<(const Fraction& rhs) const 
{
    return toReal() < rhs.toReal();
}

bool Fraction::operator<=(const Fraction& rhs) const 
{
    return *this < rhs || *this == rhs;
}

Fraction Fraction::operator+(const Fraction& rhs) const 
{
    int a = m_numerator, b = m_denominator,
        c = rhs.m_numerator, d = rhs.m_denominator;

    Fraction result(a * d + b * c, b * d);
    return result;
}

Fraction Fraction::operator-(const Fraction& rhs) const 
{
    return *this + (-rhs);
}

Fraction Fraction::operator*(const Fraction& rhs) const 
{
    int a = m_numerator, b = m_denominator,
        c = rhs.m_numerator, d = rhs.m_denominator;

    Fraction result(a * c, b * d);
    return result;
}

Fraction Fraction::operator/(const Fraction& rhs) const 
{
    int a = m_numerator, b = m_denominator,
        c = rhs.m_numerator, d = rhs.m_denominator;

    Fraction result(a * d, b * c);
    return result;
}

Fraction Fraction::operator+=(const Fraction& rhs) 
{
    *this = *this + rhs;
    return *this;
}

Fraction Fraction::operator-=(const Fraction& rhs) 
{
    *this = *this - rhs;
    return *this;
}

Fraction Fraction::operator*=(const Fraction& rhs) 
{
    *this = *this * rhs;
    return *this;
}

Fraction Fraction::operator/=(const Fraction& rhs) 
{
    *this = *this / rhs;
    return *this;
}

Fraction Fraction::operator-() const 
{
    return Fraction(-m_numerator, m_denominator);
}

Fraction Fraction::operator++() 
{
    m_numerator += m_denominator;
    check();
    simplify();
    return *this;
}

Fraction Fraction::operator++(int) 
{
    Fraction old_value(*this);
    ++* this;
    return old_value;
}

Fraction Fraction::operator--() 
{
    m_numerator -= m_denominator;
    check();
    simplify();
    return *this;
}

Fraction Fraction::operator--(int) 
{
    Fraction old_value(*this);
    --* this;
    return old_value;
}

std::istream& operator>>(std::istream& ist, Fraction& value) 
{
    ist >> value.m_numerator >> value.m_denominator;

    value.check();
    value.simplify();

    return ist;
}

ostream& operator<<(ostream& ost, const Fraction& value) 
{
    ost << "(" << value.m_numerator << "\\" << value.m_denominator << ")";
    return ost;
}

Fraction operator+(const int lhs, const Fraction& rhs) 
{
    return Fraction(lhs) + rhs;
}

Fraction operator-(const int lhs, const Fraction& rhs) 
{
    return Fraction(lhs) - rhs;
}

Fraction operator*(const int lhs, const Fraction& rhs) 
{
    return Fraction(lhs) * rhs;
}

Fraction operator/(const int lhs, const Fraction& rhs) 
{
    return Fraction(lhs) / rhs;
}

bool operator==(const int lhs, const Fraction& rhs) 
{
    return rhs == lhs;
}

bool operator!=(const int lhs, const Fraction& rhs) 
{
    return rhs != lhs;
}

bool operator>(const int lhs, const Fraction& rhs) 
{
    return rhs < lhs;
}

bool operator>=(const int lhs, const Fraction& rhs) {
    return rhs <= lhs;
}

bool operator<(const int lhs, const Fraction& rhs) {
    return rhs > lhs;
}

bool operator<=(const int lhs, const Fraction& rhs) {
    return rhs >= lhs;
}

