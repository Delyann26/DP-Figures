#include "catch2/catch_all.hpp"
#include "../src/Figures/Circle.h"
#include "../src/Figures/Rectangle.h"
#include "../src/Figures/Triangle.h"
#include "../src/Utils/Exceptions.h"
#include "../src/Factories/StringToFigure.h"


TEST_CASE("Circle creation with valid radius", "[Circle]") {
    Circle c(5.0);
    REQUIRE(c.getRadius() == 5.0);
    REQUIRE(c.perimeter() == 3.14 * 2 * 5);
    REQUIRE(c.to_string() == "Circle 5.000000");
}

TEST_CASE("Circle creation with invalid radius throws", "[Circle]") {

    REQUIRE_THROWS_AS(Circle(0), invalid_circle_error);
    REQUIRE_THROWS_AS(Circle(-3), invalid_circle_error);


    REQUIRE_THROWS_AS(Circle(std::numeric_limits<double>::infinity()), invalid_circle_error);
    REQUIRE_THROWS_AS(Circle(-std::numeric_limits<double>::infinity()), invalid_circle_error);
}

TEST_CASE("Circle perimeter overflow throws", "[Circle]") {
    double max = std::numeric_limits<double>::max();
    REQUIRE_THROWS_AS(Circle(max), invalid_circle_error);
}

TEST_CASE("Circle clone creates a new identical Circle", "[Circle]") {
    Circle c1(3.0);
    std::unique_ptr<Figure> c2 = c1.clone();

    REQUIRE(c2 != nullptr);
    REQUIRE(c2->to_string() == c1.to_string());
    REQUIRE(c2->perimeter() == c1.perimeter());
    REQUIRE(c2.get() != &c1);
}

TEST_CASE("Circle create() with valid input", "[Circle]") {
    std::istringstream iss("      10    ");
    std::unique_ptr<Figure> fig = Circle::create(iss);

    REQUIRE(fig != nullptr);
    REQUIRE(fig->to_string() == "Circle 10.000000");
}

TEST_CASE("Circle create() fails if radius missing", "[Circle]") {
    std::istringstream iss("");
    REQUIRE_THROWS_AS(Circle::create(iss), invalid_circle_error);
}

TEST_CASE("Circle create() fails with non-numeric input", "[Circle]") {
    std::istringstream iss("abc");
    REQUIRE_THROWS_AS(Circle::create(iss), invalid_circle_error);
}

TEST_CASE("Circle create() fails with extra characters", "[Circle]") {
    std::istringstream iss("3.14abc");
    REQUIRE_THROWS_AS(Circle::create(iss), invalid_circle_error);
}

 




TEST_CASE("Triangle creation with valid sides", "[Triangle]") {
    Triangle t(3, 4, 5);

    REQUIRE(t.getSideA() == 3);
    REQUIRE(t.getSideB() == 4);
    REQUIRE(t.getSideC() == 5);
    REQUIRE(t.perimeter() == 12.0);
    REQUIRE(t.to_string() == "Triangle 3.000000 4.000000 5.000000");
}

TEST_CASE("Triangle creation with invalid sides throws", "[Triangle]") {

    REQUIRE_THROWS_AS(Triangle(0, 1, 1), invalid_triangle_error);
    REQUIRE_THROWS_AS(Triangle(1, 1, 0), invalid_triangle_error);
    REQUIRE_THROWS_AS(Triangle(-1, 1, 1), invalid_triangle_error);


    REQUIRE_THROWS_AS(Triangle(std::numeric_limits<double>::infinity(), 1, 1), invalid_triangle_error);


    REQUIRE_THROWS_AS(Triangle(1, 2, 3), invalid_triangle_error);
    REQUIRE_THROWS_AS(Triangle(5, 1, 1), invalid_triangle_error);
    REQUIRE_THROWS_AS(Triangle(10, 5, 3), invalid_triangle_error);
}

TEST_CASE("Triangle creation perimeter overflow throws", "[Triangle]") {
    double max = std::numeric_limits<double>::max();
    REQUIRE_THROWS_AS(Triangle(max, max, max), invalid_triangle_error);
    REQUIRE_THROWS_AS(Triangle(max, 1.0, 1.0), invalid_triangle_error);
}

TEST_CASE("Triangle clone creates identical triangle", "[Triangle]") {
    Triangle t1(3.0, 4.0, 5.0);
    std::unique_ptr<Figure> t2 = t1.clone();

    REQUIRE(t2 != nullptr);
    REQUIRE(t2->to_string() == t1.to_string());
    REQUIRE(t2->perimeter() == t1.perimeter());
    REQUIRE(t2.get() != &t1);
}

TEST_CASE("Triangle create() with valid input", "[Triangle]") {
    std::istringstream iss("3    4    5");
    std::unique_ptr<Figure> fig = Triangle::create(iss);

    REQUIRE(fig != nullptr);
    REQUIRE(fig->to_string() == "Triangle 3.000000 4.000000 5.000000");
}

TEST_CASE("Triangle create() fails if sides missing", "[Triangle]") {
    std::istringstream iss("");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);

    std::istringstream iss2("3");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);

    std::istringstream iss3("3 4");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);

}

TEST_CASE("Triangle create() fails with non-numeric input", "[Triangle]") {
    std::istringstream iss("3 a 5");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);

    std::istringstream iss2("a b c");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);

    std::istringstream iss3("10 21 asda");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);
}

TEST_CASE("Triangle create() fails with extra characters after side", "[Triangle]") {
    std::istringstream iss("3 4 5abc");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);
}

TEST_CASE("Triangle create() fails with extra tokens", "[Triangle]") {
    std::istringstream iss("3 4 5 6");
    REQUIRE_THROWS_AS(Triangle::create(iss), invalid_triangle_error);
}





TEST_CASE("Rectangle creation with valid sides", "[Rectangle]") {
    Rectangle r(1, 2);
    REQUIRE(r.getWidth() == 1);
    REQUIRE(r.getHeight() == 2);
    REQUIRE(r.perimeter() == 6);
    REQUIRE(r.to_string() == "Rectangle 1.000000 2.000000");
}

TEST_CASE("Rectangle creation with invalid sides throws", "[Rectangle]") {


    REQUIRE_THROWS_AS(Rectangle(0, 3), invalid_rectangle_error);
    REQUIRE_THROWS_AS(Rectangle(3, 0), invalid_rectangle_error);
    REQUIRE_THROWS_AS(Rectangle(-1, 3), invalid_rectangle_error);
    REQUIRE_THROWS_AS(Rectangle(1, -3), invalid_rectangle_error);


    REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::infinity(), 1), invalid_rectangle_error);

}

TEST_CASE("Rectangle creation perimeter overflow throws", "[Rectangle]") {
    double max = std::numeric_limits<double>::max();
    REQUIRE_THROWS_AS(Rectangle(max, max), invalid_rectangle_error);
    REQUIRE_THROWS_AS(Rectangle(max, 1.0), invalid_rectangle_error);
}

TEST_CASE("Triangle clone creates identical triangle", "[Rectangle]") {
    Rectangle r1(3, 4);
    std::unique_ptr<Figure> r2 = r1.clone();

    REQUIRE(r2 != nullptr);
    REQUIRE(r2->to_string() == r1.to_string());
    REQUIRE(r2->perimeter() == r1.perimeter());
    REQUIRE(r2.get() != &r1);
}

TEST_CASE("Rectangle create() with valid input", "[Rectangle]") {
    std::istringstream iss("  3    4  ");
    std::unique_ptr<Figure> fig = Rectangle::create(iss);

    REQUIRE(fig != nullptr);
    REQUIRE(fig->to_string() == "Rectangle 3.000000 4.000000");
}

TEST_CASE("Rectangle create() fails if sides missing", "[Rectangle]") {
    std::istringstream iss("");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);

    std::istringstream iss2("3");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);
}

TEST_CASE("Rectangle create() fails with non-numeric input", "[Rectangle]") {
    std::istringstream iss("3 a");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);

    std::istringstream iss2("a 3");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);

    std::istringstream iss3("10 21 asda");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);
}

TEST_CASE("Rectangle create() fails with extra characters after side", "[Rectangle]") {
    std::istringstream iss("3 4abc");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);
}

TEST_CASE("Rectangle create() fails with extra tokens", "[Rectangle]") {
    std::istringstream iss("3 4 6");
    REQUIRE_THROWS_AS(Rectangle::create(iss), invalid_rectangle_error);
}







TEST_CASE("StringToFigure creates Circle correctly", "[StringToFigure]") {
    std::string input = "  Circle    10  ";
    std::unique_ptr<Figure> figure = StringToFigure::getInstance().createFrom(input);
    REQUIRE(figure != nullptr);
    REQUIRE(figure->to_string() == "Circle 10.000000");
}

TEST_CASE("StringToFigure creates Rectangle correctly", "[StringToFigure]") {
    std::string input = "Rectangle   4  5";
    std::unique_ptr<Figure> figure = StringToFigure::getInstance().createFrom(input);
    REQUIRE(figure != nullptr);
    REQUIRE(figure->to_string() == "Rectangle 4.000000 5.000000");
}

TEST_CASE("StringToFigure creates Triangle correctly", "[StringToFigure]") {
    std::string input = "Triangle   3 4 5";
    std::unique_ptr<Figure> figure = StringToFigure::getInstance().createFrom(input);
    REQUIRE(figure != nullptr);
    REQUIRE(figure->to_string() == "Triangle 3.000000 4.000000 5.000000");
}

TEST_CASE("StringToFigure throws on unknown figure type", "[StringToFigure]") {
    std::string input = "unknown 6";
    StringToFigure& factory = StringToFigure::getInstance();
    REQUIRE_THROWS_AS(factory.createFrom(input), std::runtime_error);
}

TEST_CASE("StringToFigure throws on empty input", "[StringToFigure]") {
    std::string input = "";
    StringToFigure& factory = StringToFigure::getInstance();
    REQUIRE_THROWS_AS(factory.createFrom(input), std::runtime_error);
}

TEST_CASE("StringToFigure throws when parameters are missing", "[StringToFigure]") {
    std::string input = "Circle";
    StringToFigure& factory = StringToFigure::getInstance();
    REQUIRE_THROWS(factory.createFrom(input));
}

TEST_CASE("StringToFigure throws on malformed parameters", "[StringToFigure]") {
    std::string input = "Rectangle abc def";
    StringToFigure& factory = StringToFigure::getInstance();
    REQUIRE_THROWS(factory.createFrom(input));
}

TEST_CASE("StringToFigure accepts lowercase type name", "[StringToFigure]") {
    std::string input = "circle 10";
    std::unique_ptr<Figure> figure = StringToFigure::getInstance().createFrom(input);
    REQUIRE(figure != nullptr);
    REQUIRE(figure->to_string() == "Circle 10.000000");
}

TEST_CASE("StringToFigure singleton returns same instance", "[StringToFigure]") {
    StringToFigure& factory1 = StringToFigure::getInstance();
    StringToFigure& factory2 = StringToFigure::getInstance();
    CHECK(&factory1 == &factory2);
}