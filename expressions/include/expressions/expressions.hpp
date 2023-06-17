#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "complex/complex.hpp"

class Expression {
public:
    Expression()                             = default;
    Expression(const Expression& expr)       = default;
    Expression& operator=(Expression&& expr) = default;

    virtual Complex eval(const std::unordered_map<std::string, Complex> values) const = 0;
    virtual Expression* clone() const                                                 = 0;
    virtual std::string str() const                                                   = 0;

    virtual ~Expression() = default;
};

class BinaryOperation: public Expression {
public:
    BinaryOperation(const Expression& left_operand, const Expression& right_operand);

    Complex eval(const std::unordered_map<std::string, Complex> values) const;

    std::string str() const;

protected:
    virtual Complex compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const = 0;
    virtual std::string operation_sign() const                                                                     = 0;

private:
    std::shared_ptr<Expression> left_operand;
    std::shared_ptr<Expression> right_operand;
};

class UnaryOperation: public Expression {
public:
    UnaryOperation(const Expression& operand);

    Complex eval(const std::unordered_map<std::string, Complex> values) const;

    std::string str() const;

protected:
    virtual Complex compute_operation(const Complex& operand_value) const = 0;
    virtual std::string operation_sign() const                            = 0;

private:
    std::shared_ptr<Expression> operand;
};

class Add: public BinaryOperation {
public:
    Add(const Expression& left_operand, const Expression& right_operand);

    Expression* clone() const;

private:
    std::string sign = "+";

    Complex compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const;

    std::string operation_sign() const;
};

class Subtract: public BinaryOperation {
public:
    Subtract(const Expression& left_operand, const Expression& right_operand);

    Expression* clone() const;

private:
    std::string sign = "-";

    Complex compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const;

    std::string operation_sign() const;
};

class Multiply: public BinaryOperation {
public:
    Multiply(const Expression& left_operand, const Expression& right_operand);

    Expression* clone() const;

private:
    std::string sign = "*";

    Complex compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const;

    std::string operation_sign() const;
};

class Divide: public BinaryOperation {
public:
    Divide(const Expression& left_operand, const Expression& right_operand);

    Expression* clone() const;

private:
    std::string sign = "/";

    Complex compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const;

    std::string operation_sign() const;
};

class Conjugate: public UnaryOperation {
public:
    Conjugate(const Expression& operand);

    Expression* clone() const;

private:
    std::string sign = "~";

    Complex compute_operation(const Complex& operand_value) const;

    std::string operation_sign() const;
};

class Negate: public UnaryOperation {
public:
    Negate(const Expression& operand);

    Expression* clone() const;

private:
    std::string sign = "-";

    Complex compute_operation(const Complex& operand_value) const;

    std::string operation_sign() const;
};

class Const: public Expression {
public:
    Const(const Complex& const_value);

    Complex eval(const std::unordered_map<std::string, Complex> values) const;

    Expression* clone() const;

    std::string str() const;

private:
    Complex const_value;
};

class Variable: public Expression {
public:
    Variable(std::string variable_name);

    Complex eval(const std::unordered_map<std::string, Complex> values) const;

    Expression* clone() const;

    std::string str() const;

private:
    std::string variable_name;
};

Add operator+(const Expression& left, const Expression& right);
Subtract operator-(const Expression& left, const Expression& right);
Multiply operator*(const Expression& left, const Expression& right);
Divide operator/(const Expression& left, const Expression& right);

std::ostream& operator<<(std::ostream& out, const Expression& expr);