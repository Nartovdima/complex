#ifndef COMPLEX_COMPLEX_HPP
#define COMPLEX_COMPLEX_HPP

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class Complex {
public:
    Complex() = default;

    Complex(double real);

    Complex(double real, double imag);

    Complex(const Complex& number) = default;

    Complex& operator=(Complex&& value) = default;

    double real() const;

    double imag() const;

    double abs() const;

    std::string str() const;

    Complex operator-() const;
    Complex operator~() const;

    Complex& operator+=(const Complex& number);
    Complex& operator-=(const Complex& number);
    Complex& operator*=(const Complex& number);
    Complex& operator/=(const Complex& number);

    Complex inverse() const;

    friend Complex operator+(const Complex& left, const Complex& right);
    friend Complex operator-(const Complex& left, const Complex& right);
    friend Complex operator*(const Complex& left, const Complex& right);
    friend Complex operator/(const Complex& left, const Complex& right);

    friend bool operator==(const Complex& left, const Complex& right);
    friend bool operator!=(const Complex& left, const Complex& right);

    friend std::ostream& operator<<(std::ostream& out, const Complex& number);

private:
    static const double EPS;

    double _real;
    double _imag;
};

Complex operator+(const Complex& left, const Complex& right);
Complex operator-(const Complex& left, const Complex& right);
Complex operator*(const Complex& left, const Complex& right);
Complex operator/(const Complex& left, const Complex& right);

bool operator==(const Complex& left, const Complex& right);
bool operator!=(const Complex& left, const Complex& right);

std::ostream& operator<<(std::ostream& out, const Complex& number);

#endif  // COMPLEX_COMPLEX_HPP
