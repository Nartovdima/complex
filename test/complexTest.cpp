#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <complex>
#include <iostream>
#include <random>

#include "complex/complex.hpp"

constexpr double min_value = -1e50;
constexpr double max_value = 1e50;

void check_complex_equality(std::complex<double> ideal, Complex test) {
    if ((std::isnan(ideal.real()) && std::isnan(test.real())) ||
        (std::isnan(ideal.imag()) && std::isnan(test.imag()))) {
        return;
    }
    REQUIRE_THAT(ideal.real(), Catch::Matchers::WithinRel(test.real()));
    REQUIRE_THAT(ideal.imag(), Catch::Matchers::WithinRel(test.imag()));
}

TEST_CASE("Constructors and get functions") {
    SECTION("Constructs with real part") {
        std::complex ideal(5.0);
        Complex test(5.0);

        REQUIRE_THAT(ideal.real(), Catch::Matchers::WithinRel(test.real()));
    }

    SECTION("Constructs with real and imag part") {
        std::complex ideal(5.123432, 7.32432);
        Complex test(5.123432, 7.32432);

        check_complex_equality(ideal, test);
    }

    SECTION("Corner cases") {
        std::complex ideal(min_value, max_value);
        Complex test(min_value, max_value);

        check_complex_equality(ideal, test);
    }

    SECTION("Constructs with random numbers") {
        constexpr std::size_t TESTS_NUMBER = 100;
        auto rnd_real                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal(rnd_real, rnd_imag);
        Complex test(rnd_real, rnd_imag);

        check_complex_equality(ideal, test);
    }
}

TEST_CASE("Abs") {
    SECTION("Abs") {
        std::complex ideal(5.123432, 7.32432);
        Complex test(5.123432, 7.32432);

        REQUIRE_THAT(std::abs(ideal), Catch::Matchers::WithinRel(test.abs()));
    }

    SECTION("Abs with random numbers") {
        constexpr std::size_t TESTS_NUMBER = 100;
        auto rnd_real                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal(rnd_real, rnd_imag);
        Complex test(rnd_real, rnd_imag);

        REQUIRE_THAT(std::abs(ideal), Catch::Matchers::WithinRel(test.abs()));
    }
}

TEST_CASE("Unary operations") {
    SECTION("Negate") {
        std::complex ideal(5.123432, 7.32432);
        Complex test(5.123432, 7.32432);

        ideal = -ideal;
        test  = -test;

        check_complex_equality(ideal, test);
    }

    SECTION("Negate with random numbers") {
        constexpr std::size_t TESTS_NUMBER = 100;
        auto rnd_real                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal(rnd_real, rnd_imag);
        Complex test(rnd_real, rnd_imag);

        ideal = -ideal;
        test  = -test;

        check_complex_equality(ideal, test);
    }

    SECTION("Conjugate") {
        std::complex ideal(5.123432, 7.32432);
        Complex test(5.123432, 7.32432);

        ideal = std::conj(ideal);
        test  = ~test;

        check_complex_equality(ideal, test);
    }

    SECTION("Negate with random numbers") {
        constexpr std::size_t TESTS_NUMBER = 100;
        auto rnd_real                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag                      = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal(rnd_real, rnd_imag);
        Complex test(rnd_real, rnd_imag);

        ideal = std::conj(ideal);
        test  = ~test;

        check_complex_equality(ideal, test);
    }
}

TEST_CASE("Binary operations") {
    SECTION("+=") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);

        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        ideal1 += ideal2;
        test1 += test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("Random +=") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        ideal1 += ideal2;
        test1 += test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("+") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);
        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        std::complex ideal3 = ideal1 + ideal2;
        Complex test3       = test1 + test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("Random +") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        std::complex ideal3 = ideal1 + ideal2;
        Complex test3       = test1 + test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("-=") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);

        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        ideal1 -= ideal2;
        test1 -= test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("Random -=") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        ideal1 -= ideal2;
        test1 -= test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("-") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);
        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        std::complex ideal3 = ideal1 - ideal2;
        Complex test3       = test1 - test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("Random -") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        std::complex ideal3 = ideal1 - ideal2;
        Complex test3       = test1 - test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("*=") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);

        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        ideal1 *= ideal2;
        test1 *= test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("Random *=") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        ideal1 *= ideal2;
        test1 *= test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("*") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);
        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        std::complex ideal3 = ideal1 * ideal2;
        Complex test3       = test1 * test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("Random *") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag2                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        std::complex ideal3 = ideal1 * ideal2;
        Complex test3       = test1 * test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("/=") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);

        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        ideal1 /= ideal2;
        test1 /= test2;

        check_complex_equality(ideal1, test1);
    }

    SECTION("Random /=") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(
            take(TESTS_NUMBER, filter([](int rnd_real2) { return rnd_real2 != 0; }, random(min_value, max_value))));
        auto rnd_imag2 = GENERATE(
            take(TESTS_NUMBER, filter([](int rnd_imag2) { return rnd_imag2 != 0; }, random(min_value, max_value))));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);
        ideal1 /= ideal2;
        test1 /= test2;
        check_complex_equality(ideal1, test1);
    }

    SECTION("/") {
        std::complex ideal1(5.123432, 7.32432);
        std::complex ideal2(3242.402358, 547.8332798);
        Complex test1(5.123432, 7.32432);
        Complex test2(3242.402358, 547.8332798);

        std::complex ideal3 = ideal1 / ideal2;
        Complex test3       = test1 / test2;

        check_complex_equality(ideal3, test3);
    }

    SECTION("Random /") {
        constexpr std::size_t TESTS_NUMBER = 10;
        auto rnd_real1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_imag1                     = GENERATE(take(TESTS_NUMBER, random(min_value, max_value)));
        auto rnd_real2                     = GENERATE(
            take(TESTS_NUMBER, filter([](int rnd_real2) { return rnd_real2 != 0; }, random(min_value, max_value))));
        auto rnd_imag2 = GENERATE(
            take(TESTS_NUMBER, filter([](int rnd_imag2) { return rnd_imag2 != 0; }, random(min_value, max_value))));

        std::complex ideal1(rnd_real1, rnd_imag1);
        std::complex ideal2(rnd_real2, rnd_imag2);

        Complex test1(rnd_real1, rnd_imag1);
        Complex test2(rnd_real2, rnd_imag2);

        std::complex ideal3 = ideal1 / ideal2;
        Complex test3       = test1 / test2;

        check_complex_equality(ideal3, test3);
    }
}

TEST_CASE("== and !=") {
    SECTION("==") {
        Complex ideal(5.123432, 7.32432);
        Complex test(5.123432, 7.32432);

        REQUIRE(ideal == test);
    }

    SECTION("!=") {
        Complex ideal(5.123432, 7.32432);
        Complex test(5.133432, 7.32132);

        REQUIRE(ideal != test);
    }
}