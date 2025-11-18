#include "catch2/catch_all.hpp"
#include "../src/Figures/Circle.h"
#include "../src/Figures/Rectangle.h"
#include "../src/Figures/Triangle.h"
#include "../src/Factories/StreamFigureFactory.h"
#include "../src/Factories/RandomFigureFactory.h"
#include "../src/Factories/AbstractFactory.h"
#include "../src/Utils/CinRedirect.h"


TEST_CASE("StreamFigureFactory creates figures from stream", "[StreamFigureFactory]") {
    std::string input = "Circle 10\n";

    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);
    StreamFigureFactory factory(iss);

    std::unique_ptr<Figure> fig = factory.create();
    REQUIRE(fig != nullptr);
    REQUIRE(fig->to_string() == "Circle 10.000000");
}

TEST_CASE("StreamFigureFactory reads multiple figures sequentially", "[StreamFigureFactory]") {
    std::string input = "Circle 5\nRectangle 4 6\nTriangle 3 4 5\n";

    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);
    StreamFigureFactory factory(iss);

    std::unique_ptr<Figure> fig1 = factory.create();
    REQUIRE(fig1 != nullptr);
    REQUIRE(fig1->to_string() == "Circle 5.000000");

    std::unique_ptr<Figure> fig2 = factory.create();
    REQUIRE(fig2 != nullptr);
    REQUIRE(fig2->to_string() == "Rectangle 4.000000 6.000000");

    std::unique_ptr<Figure> fig3 = factory.create();
    REQUIRE(fig3 != nullptr);
    REQUIRE(fig3->to_string() == "Triangle 3.000000 4.000000 5.000000");

    std::unique_ptr<Figure> fig4 = factory.create();
    REQUIRE(fig4 == nullptr);
}

TEST_CASE("StreamFigureFactory skips empty lines", "[StreamFigureFactory]") {
    std::string input = "\n\n  \nCircle 8\n";
    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);

    StreamFigureFactory factory(iss);

    std::unique_ptr<Figure> fig = factory.create();
    REQUIRE(fig != nullptr);
    REQUIRE(fig->to_string() == "Circle 8.000000");

}

TEST_CASE("StreamFigureFactory returns nullptr at EOF", "[StreamFigureFactory]") {
    std::string input = "";
    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);

    StreamFigureFactory factory(iss);

    auto fig = factory.create();
    REQUIRE(fig == nullptr);
}

TEST_CASE("StreamFigureFactory throws on invalid figure input", "[StreamFigureFactory]") {
    std::string input = "INVALIDTYPE 123\n";
    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);
    StreamFigureFactory factory(iss);
    REQUIRE_THROWS_AS(factory.create(), std::runtime_error);
}

TEST_CASE("StreamFigureFactory throws if stream fails unexpectedly", "[StreamFigureFactory]") {
    std::string input = "Circle 13\n";
    std::shared_ptr<std::istream> iss = std::make_shared<std::istringstream>(input);
    iss->setstate(std::ios::badbit);
    StreamFigureFactory factory(iss);
    REQUIRE_THROWS_AS(factory.create(), std::runtime_error);
}







TEST_CASE("RandomFigureFactory rejects invalid min/max", "[RandomFigureFactory]") {
    REQUIRE_THROWS_AS(RandomFigureFactory(-1, 10), std::invalid_argument);

    REQUIRE_THROWS_AS(RandomFigureFactory(0, 10), std::invalid_argument);

    REQUIRE_THROWS_AS(RandomFigureFactory(5, 5), std::invalid_argument);
    REQUIRE_THROWS_AS(RandomFigureFactory(10, 5), std::invalid_argument);

    REQUIRE_THROWS_AS(RandomFigureFactory(1, std::numeric_limits<double>::infinity()), std::invalid_argument);
    REQUIRE_THROWS_AS(RandomFigureFactory(std::numeric_limits<double>::infinity(), 0.01), std::invalid_argument);
}


TEST_CASE("RandomFigureFactory generates valid figures", "[RandomFigureFactory]") {
    double min = 1;
    double max = 2;
    RandomFigureFactory factory(min, max);
    size_t size = 10000;
    size_t created = 0;
    std::unordered_map<std::string, int> typeCount;
    
    for (size_t i = 0; i < size; i++) {
        std::unique_ptr<Figure> fig = factory.create();

        Triangle* t = dynamic_cast<Triangle*>(fig.get());
        Circle* c = dynamic_cast<Circle*>(fig.get());
        Rectangle* r = dynamic_cast<Rectangle*>(fig.get());

        if (t) {
            typeCount["Triangle"]++;
            double a = t->getSideA();
            double b = t->getSideB();
            double c = t->getSideC();

            REQUIRE(min <= a);
            REQUIRE(max >= a);

            REQUIRE(min <= b);
            REQUIRE(max >= b);

            REQUIRE(min <= c);
            REQUIRE(max >= c);

            REQUIRE(a + b > c);
            REQUIRE(a + c > b);
            REQUIRE(c + b > a);
            created++;
        }
        else if (c) {
            typeCount["Circle"]++;
            REQUIRE(c->getRadius() >= min);
            REQUIRE(c->getRadius() <= max);
            created++;
        }
        else if (r) {
            typeCount["Rectangle"]++;
            REQUIRE(r->getWidth() >= min);
            REQUIRE(r->getWidth() <= max);
            REQUIRE(r->getHeight() >= min);
            REQUIRE(r->getHeight() <= max);
            created++;
        }
        else {
            FAIL("Unknown figure type generated!");
        }
    }

    REQUIRE(created == size);

    double expected = created / 3.0;
    double tolerance = created * 0.05;

    REQUIRE(typeCount["Circle"] >= expected - tolerance);
    REQUIRE(typeCount["Circle"] <= expected + tolerance);

    REQUIRE(typeCount["Rectangle"] >= expected - tolerance);
    REQUIRE(typeCount["Rectangle"] <= expected + tolerance);

    REQUIRE(typeCount["Triangle"] >= expected - tolerance);
    REQUIRE(typeCount["Triangle"] <= expected + tolerance);
}








TEST_CASE("AbstractFactory is a singleton", "[AbstractFactory]") {
    AbstractFactory& f1 = AbstractFactory::getInstance();
    AbstractFactory& f2 = AbstractFactory::getInstance();
    CHECK(&f1 == &f2);
}


TEST_CASE("AbstractFactory creates RandomFigureFactory", "[AbstractFactory]") {
    CinRedirect redirect("10\n15\n");

    AbstractFactory& factory = AbstractFactory::getInstance();
    std::unique_ptr<FigureFactory> f = factory.createFactory("Random");

    std::unique_ptr<Figure> fig = f->create();
    REQUIRE(fig != nullptr);
}

TEST_CASE("AbstractFactory creates StreamFigureFactory from STDIN", "[AbstractFactory]") {
    CinRedirect redirect("Triangle 10 21 30\n");

    AbstractFactory& factory = AbstractFactory::getInstance();
    std::unique_ptr<FigureFactory> f = factory.createFactory("STDIN");

    std::unique_ptr<Figure> fig = f->create();
    REQUIRE(fig->to_string() == "Triangle 10.000000 21.000000 30.000000");
}

TEST_CASE("AbstractFactory creates StreamFigureFactory from File", "[AbstractFactory]") {
    CinRedirect redirect("asd\n../../../test/test1.txt\n");
    AbstractFactory& factory = AbstractFactory::getInstance();
    std::unique_ptr<FigureFactory> f = factory.createFactory("File");

    std::unique_ptr<Figure> fig = f->create();
    REQUIRE(fig != nullptr);
}

TEST_CASE("AbstractFactory throws on invalid input", "[AbstractFactory]") {
    AbstractFactory& factory = AbstractFactory::getInstance();
    CHECK_THROWS_AS(factory.createFactory("Unknown"), std::runtime_error);
}
