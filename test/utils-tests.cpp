#include "catch2/catch_all.hpp"
#include "../src/Figures/Figure.h"
#include "../src/Utils/Predicates.h"
#include "../src/Utils/Readers.h"
#include "../src/Utils/CinRedirect.h"

#include <fstream>

TEST_CASE("isValidSide tests") {

    REQUIRE(isValidSide(1.0) == true);
    REQUIRE(isValidSide(0.0001) == true);
    REQUIRE(isValidSide(123456.789) == true);

    REQUIRE(isValidSide(0.0) == false);
    REQUIRE(isValidSide(-1.0) == false);
    REQUIRE(isValidSide(-12345.0) == false);

    REQUIRE(isValidSide(std::numeric_limits<double>::infinity()) == false);
    REQUIRE(isValidSide(-std::numeric_limits<double>::infinity()) == false);

}

TEST_CASE("willAddOverflow tests") {
    double max = std::numeric_limits<double>::max();

    REQUIRE(willAddOverflow(1, 2) == false);
    REQUIRE(willAddOverflow(max / 2, max / 2 - 1) == false);

    REQUIRE(willAddOverflow(max, 1) == true);
    REQUIRE(willAddOverflow(1, max) == true);
    REQUIRE(willAddOverflow(max - 10, 20) == true);

    REQUIRE(willAddOverflow(max, std::numeric_limits<double>::infinity()) == true);
    REQUIRE(willAddOverflow(1, std::numeric_limits<double>::infinity()) == true);

}

TEST_CASE("willMulOverflow tests") {
    double max = std::numeric_limits<double>::max();

    REQUIRE(willMulOverflow(1.0, 2.0) == false);
    REQUIRE(willMulOverflow(max / 10, 9.0) == false);

    REQUIRE(willMulOverflow(max, 2.0) == true);
    REQUIRE(willMulOverflow(max / 2, 3.0) == true);

    REQUIRE(willMulOverflow(max, 0.5) == false);
    REQUIRE(willMulOverflow(0.0, max) == false);

    REQUIRE(willMulOverflow(max, std::numeric_limits<double>::infinity()) == true);
    REQUIRE(willMulOverflow(1.0, std::numeric_limits<double>::infinity()) == true);

}






TEST_CASE("readIndex works correctly", "[Readers]") {
    std::vector<std::unique_ptr<Figure>> v(3);
    size_t index;

    SECTION("Valid input") {
        CinRedirect redirect("1\n");
        REQUIRE_NOTHROW(readIndex(index, v));
        REQUIRE(index == 1);
    }

    SECTION("Negative input throws") {
        CinRedirect redirect("-1\n");
        REQUIRE_THROWS_AS(readIndex(index, v), std::runtime_error);
    }

    SECTION("Out-of-bounds input throws") {
        CinRedirect redirect("5\n");
        REQUIRE_THROWS_AS(readIndex(index, v), std::runtime_error);
    }

    SECTION("Non-numeric input throws") {
        CinRedirect redirect("abc\n");
        REQUIRE_THROWS_AS(readIndex(index, v), std::runtime_error);
    }
}


TEST_CASE("readSelection works correctly", "[Readers]") {
    unsigned choice;

    SECTION("Valid input") {
        CinRedirect redirect("2\n");
        REQUIRE_NOTHROW(readSelection(choice));
        REQUIRE(choice == 2);
    }

    SECTION("Invalid input then valid") {
        CinRedirect redirect("x\n-1\n4\n1\n");
        REQUIRE_NOTHROW(readSelection(choice));
        REQUIRE(choice == 1);
    }
}


TEST_CASE("readSize works correctly", "[Readers]") {
    size_t size;

    SECTION("Valid input") {
        CinRedirect redirect("5\n");
        REQUIRE_NOTHROW(readSize(size));
        REQUIRE(size == 5);
    }

    SECTION("Invalid input then valid") {
        CinRedirect redirect("-1\nabc\n0\n3\n");
        REQUIRE_NOTHROW(readSize(size));
        REQUIRE(size == 3);
    }
}


TEST_CASE("readDecimalNumber works correctly", "[Readers]") {
    double val;

    SECTION("Valid decimal") {
        CinRedirect redirect("3.14\n");
        REQUIRE_NOTHROW(readDecimalNumber(val));
        REQUIRE(val == 3.14);
    }

    SECTION("Invalid then valid") {
        CinRedirect redirect("abc\n-2\n5.5\n");
        REQUIRE_NOTHROW(readDecimalNumber(val));
        REQUIRE(val == 5.5);
    }
}


TEST_CASE("readRandomFactoryArguments works correctly", "[Readers]") {
    double min, max;

    SECTION("Normal order") {
        CinRedirect redirect("2\n5\n");
        readRandomFactoryArguments(min, max);
        REQUIRE(min == 2);
        REQUIRE(max == 5);
    }

    SECTION("Swapped order corrected") {
        CinRedirect redirect("7\n3\n");
        readRandomFactoryArguments(min, max);
        REQUIRE(min == 3);
        REQUIRE(max == 7);
    }
}

