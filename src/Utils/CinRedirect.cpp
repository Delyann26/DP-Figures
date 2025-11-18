#include "CinRedirect.h"

CinRedirect::CinRedirect(const std::string& data) : input(data) {
    oldCinBuf = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    oldCoutBuf = std::cout.rdbuf();
    std::cout.rdbuf(nullptr);
}

CinRedirect::~CinRedirect() {
    std::cin.rdbuf(oldCinBuf);
    std::cout.rdbuf(oldCoutBuf);
}
