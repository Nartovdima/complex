#include "complex/complex.hpp"

#include <iostream>
const double Complex::EPS = 1e-6;

Complex::Complex(double real) : _real(real), _imag(0.0) {}

Complex::Complex(double real, double imag) : _real(real), _imag(imag) {}

double Complex::real() const {
    return _real;
}

double Complex::imag() const {
    return _imag;
}

double Complex::abs() const {
    return hypot(_real, _imag);
}

std::string Complex::str() const {
    std::ostringstream tmp;
    tmp << "(" << _real << "; " << _imag << ")";
    return tmp.str();
}

Complex Complex::operator-() const {
    return Complex(-_real, -_imag);
}

Complex Complex::operator~() const {
    return Complex(_real, -_imag);
}

Complex Complex::inverse() const {
    double square_abs = _real * _real + _imag * _imag;
    return Complex(_real / square_abs, -_imag / square_abs);
}

Complex& Complex::operator+=(const Complex& number) {
    _real += number._real;
    _imag += number._imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& number) {
    Complex tmp(number);
    tmp = -tmp;
    return *this += tmp;
}

Complex& Complex::operator*=(const Complex& number) {
    Complex tmp(*this);
    _real = tmp._real * number._real - tmp._imag * number._imag;
    _imag = tmp._imag * number._real + tmp._real * number._imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& number) {
    Complex tmp(*this);
    if (std::abs(number._imag) < std::abs(number._real)) {
        double prt1 = number._imag / number._real;
        double prt2 = number._real + number._imag * prt1;
        _real       = (tmp._real + tmp._imag * prt1) / prt2;
        _imag       = (tmp._imag - tmp._real * prt1) / prt2;
    } else {
        double prt1 = number._real / number._imag;
        double prt2 = number._imag + number._real * prt1;
        _real       = (tmp._real * prt1 + tmp._imag) / prt2;
        _imag       = (tmp._imag * prt1 - tmp._real) / prt2;
    }
    return *this;
}

Complex operator+(const Complex& left, const Complex& right) {
    return Complex(left) += right;
}

Complex operator-(const Complex& left, const Complex& right) {
    return Complex(left) -= right;
}

Complex operator*(const Complex& left, const Complex& right) {
    return Complex(left) *= right;
}

Complex operator/(const Complex& left, const Complex& right) {
    return Complex(left) /= right;
}

bool operator==(const Complex& left, const Complex& right) {
    return (std::abs(left._real - right._real) < Complex::EPS) && (std::abs(left._imag - right._imag) < Complex::EPS);
}

bool operator!=(const Complex& left, const Complex& right) {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Complex& number) {
    return out << number.str();
}