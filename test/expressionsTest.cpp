#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <string>

#include "expressions/expressions.hpp"

void check_complex_equality(Complex test, Complex ideal) {
    if ((std::isnan(ideal.real()) && std::isnan(test.real())) ||
        (std::isnan(ideal.imag()) && std::isnan(test.imag()))) {
        return;
    }
    REQUIRE_THAT(ideal.real(), Catch::Matchers::WithinRel(test.real()));
    REQUIRE_THAT(ideal.imag(), Catch::Matchers::WithinRel(test.imag()));
}

TEST_CASE("str") {
    auto expr = Multiply(Multiply(Const(Complex(312.3, 643.6)), Const(Complex(1))), Const(Complex()));

    REQUIRE_THAT(expr.str(), Catch::Matchers::Equals("(((312.3; 643.6) * (1; 0)) * (0; 0))"));

    expr = Multiply(Const(Complex(728.81)), Multiply(Const(Complex(12.6, 8)), Const(Complex(32.7, 1325.7))));

    REQUIRE_THAT(expr.str(), Catch::Matchers::Equals("((728.81; 0) * ((12.6; 8) * (32.7; 1325.7)))"));

    expr = Multiply(Add(Const(Complex(0.8)), Const(Complex(12593))),
                    Divide(Subtract(Variable("x"), Variable("y")), Negate(Conjugate(Variable("z")))));

    REQUIRE_THAT(expr.str(), Catch::Matchers::Equals("(((0.8; 0) + (12593; 0)) * ((x - y) / (-(~z))))"));
}

TEST_CASE("eval") {
    auto expr = Multiply(Multiply(Const(Complex(312.3, 643.6)), Const(Complex(1))), Const(Complex()));

    check_complex_equality(expr.eval({{"x", Complex(324.6546)}, {"pie", Complex(0.09832)}}),
                           Complex(312.3, 643.6) * Complex(1) * Complex());

    REQUIRE_THAT(expr.str(), Catch::Matchers::Equals("(((312.3; 643.6) * (1; 0)) * (0; 0))"));

    expr = Multiply(Const(Complex(728.81)), Multiply(Const(Complex(12.6, 8)), Const(Complex(32.7, 1325.7))));

    check_complex_equality(expr.eval({{"x", Complex(324.6546)}, {"pie", Complex(0.09832)}}),
                           Complex(728.81) * Complex(12.6, 8) * Complex(32.7, 1325.7));

    expr = Multiply(Add(Const(Complex(0.8)), Const(Complex(12593))),
                    Divide(Subtract(Variable("x"), Variable("y")), Negate(Conjugate(Variable("z")))));

    check_complex_equality(
        expr.eval({{"x", Complex(324.6546)}, {"y", Complex(0.09832)}, {"z", Complex(0.09832, 6534)}}),
        ((Complex(0.8) + Complex(12593)) * ((Complex(324.6546) - Complex(0.09832)) / (-(~Complex(0.09832, 6534))))));

    expr = ((Const(Complex(0.8)) + Const(Complex(12593))) *
            ((Variable("x") - Variable("y")) / (Negate((Conjugate(Variable("z")))))));

    check_complex_equality(
        expr.eval({{"x", Complex(324.6546)}, {"y", Complex(0.09832)}, {"z", Complex(0.09832, 6534)}}),
        ((Complex(0.8) + Complex(12593)) * ((Complex(324.6546) - Complex(0.09832)) / (-(~Complex(0.09832, 6534))))));
}