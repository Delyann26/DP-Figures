#include "catch2/catch_all.hpp"
#include <iostream>
#include <fstream>

#include "../src/Utils/CinRedirect.h"
#include "../src/UserAPI/Manager.h"

TEST_CASE("Manager startProgram with STDIN factory", "[Manager]") {

    Manager& m = Manager::getInstance();

    std::string simulatedInput = "2\n2\ncircle 5\nrectangle 3 4\nlist\nduplicate\n1\nsave\n../../../test/test3.txt\nexit\n";

    CinRedirect redirect(simulatedInput);

    m.getInstance().startProgram();

    std::ifstream ifs("../../../test/test3.txt");
    REQUIRE(ifs.is_open());

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }
    ifs.close();
    std::remove("../../../test/test3.txt");

    REQUIRE(lines.size() == 3);

    REQUIRE(lines[0] == "Circle 5.000000");
    REQUIRE(lines[1] == "Rectangle 3.000000 4.000000");
    REQUIRE(lines[2] == "Rectangle 3.000000 4.000000");

}

