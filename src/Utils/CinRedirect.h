#pragma once
#include <iostream>
#include <sstream>

class CinRedirect {
    std::streambuf* oldCinBuf;
    std::streambuf* oldCoutBuf;
    std::istringstream input;
public:
    CinRedirect(const std::string& data);
    ~CinRedirect();
};