#pragma once
#ifndef FRACTIONAL_H
#define FRACTIONAL_H
#include <iostream>

class Fraction {
public:
	Fraction();
	Fraction(int numerator);
	Fraction(int numerator, int denominator);

	int toInt() const;
	double toReal() const;
	Fraction getInverse() const;

	bool operator==(const Fraction& rhs) const;
	bool operator!=(const Fraction& rhs) const;
	bool operator>(const Fraction& rhs) const;
	bool operator>=(const Fraction& rhs) const;
	bool operator<(const Fraction& rhs) const;
	bool operator<=(const Fraction& rhs) const;

	Fraction operator+(const Fraction& rhs) const;
	Fraction operator-(const Fraction& rhs) const;
	Fraction operator*(const Fraction& rhs) const;
	Fraction operator/(const Fraction& rhs) const;

	Fraction operator+=(const Fraction& rhs);
	Fraction operator-=(const Fraction& rhs);
	Fraction operator*=(const Fraction& rhs);
	Fraction operator/=(const Fraction& rhs);

	Fraction operator-() const;
	Fraction operator++();
	Fraction operator++(int);
	Fraction operator--();
	Fraction operator--(int);

	friend std::istream& operator>>(std::istream&, Fraction& value);
	friend std::ostream& operator<<(std::ostream&, const Fraction& value);

	friend bool operator==(const int lhs, const Fraction& rhs);
	friend bool operator!=(const int lhs, const Fraction& rhs);
	friend bool operator>(const int lhs, const Fraction& rhs);
	friend bool operator>=(const int lhs, const Fraction& rhs);
	friend bool operator<(const int lhs, const Fraction& rhs);
	friend bool operator<=(const int lhs, const Fraction& rhs);

	friend Fraction operator+(const int lhs, const Fraction& rhs);
	friend Fraction operator-(const int lhs, const Fraction& rhs);
	friend Fraction operator*(const int lhs, const Fraction& rhs);
	friend Fraction operator/(const int lhs, const Fraction& rhs);
private:
	void simplify();
	void check() const;

	int m_numerator, m_denominator;
};

#endif // FRACTIONAL_H