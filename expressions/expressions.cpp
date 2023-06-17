#include "expressions/expressions.hpp"

Const::Const(const Complex& const_value) : const_value(const_value) {}

Complex Const::eval(const std::unordered_map<std::string, Complex> values) const {
    return const_value;
}

Expression* Const::clone() const {
    return new Const(*this);
}

std::string Const::str() const {
    return const_value.str();
}

Variable::Variable(std::string variable_name) : variable_name(variable_name) {}

Complex Variable::eval(const std::unordered_map<std::string, Complex> values) const {
    return values.at(variable_name);
}

Expression* Variable::clone() const {
    return new Variable(*this);
}

std::string Variable::str() const {
    return variable_name;
}

BinaryOperation::BinaryOperation(const Expression& left_operand, const Expression& right_opernad)
    : left_operand(left_operand.clone()), right_operand(right_opernad.clone()) {}

Complex BinaryOperation::eval(const std::unordered_map<std::string, Complex> values) const {
    return compute_operation(left_operand->eval(values), right_operand->eval(values));
}

std::string BinaryOperation::str() const {
    return '(' + left_operand->str() + ' ' + operation_sign() + ' ' + right_operand->str() + ')';
}

UnaryOperation::UnaryOperation(const Expression& operand) : operand(operand.clone()) {}

Complex UnaryOperation::eval(const std::unordered_map<std::string, Complex> values) const {
    return compute_operation(operand->eval(values));
}

std::string UnaryOperation::str() const {
    return '(' + operation_sign() + operand->str() + ')';
}

Add::Add(const Expression& left_operand, const Expression& right_operand)
    : BinaryOperation(left_operand, right_operand) {}

Expression* Add::clone() const {
    return new Add(*this);
}

Complex Add::compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const {
    return left_operand_value + right_operand_value;
}

std::string Add::operation_sign() const {
    return sign;
}

Subtract::Subtract(const Expression& left_operand, const Expression& right_operand)
    : BinaryOperation(left_operand, right_operand) {}

Expression* Subtract::clone() const {
    return new Subtract(*this);
}

Complex Subtract::compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const {
    return left_operand_value - right_operand_value;
}

std::string Subtract::operation_sign() const {
    return sign;
}

Multiply::Multiply(const Expression& left_operand, const Expression& right_operand)
    : BinaryOperation(left_operand, right_operand) {}

Expression* Multiply::clone() const {
    return new Multiply(*this);
}

Complex Multiply::compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const {
    return left_operand_value * right_operand_value;
}

std::string Multiply::operation_sign() const {
    return sign;
}

Divide::Divide(const Expression& left_operand, const Expression& right_operand)
    : BinaryOperation(left_operand, right_operand) {}

Expression* Divide::clone() const {
    return new Divide(*this);
}

Complex Divide::compute_operation(const Complex& left_operand_value, const Complex& right_operand_value) const {
    return left_operand_value / right_operand_value;
}

std::string Divide::operation_sign() const {
    return sign;
}

Conjugate::Conjugate(const Expression& operand) : UnaryOperation(operand) {}

Expression* Conjugate::clone() const {
    return new Conjugate(*this);
}

Complex Conjugate::compute_operation(const Complex& operand_value) const {
    return ~Complex(operand_value);
}

std::string Conjugate::operation_sign() const {
    return sign;
}

Negate::Negate(const Expression& operand) : UnaryOperation(operand) {}

Expression* Negate::clone() const {
    return new Negate(*this);
}

Complex Negate::compute_operation(const Complex& operand_value) const {
    return -Complex(operand_value);
}

std::string Negate::operation_sign() const {
    return sign;
}

Add operator+(const Expression& left, const Expression& right) {
    return Add(left, right);
}

Subtract operator-(const Expression& left, const Expression& right) {
    return Subtract(left, right);
}

Multiply operator*(const Expression& left, const Expression& right) {
    return Multiply(left, right);
}

Divide operator/(const Expression& left, const Expression& right) {
    return Divide(left, right);
}

std::ostream& operator<<(std::ostream& out, const Expression& expr) {
    out << expr.str();
    return out;
}
