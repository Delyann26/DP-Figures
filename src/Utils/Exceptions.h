#pragma once
#include <stdexcept>
#include <string>

class invalid_triangle_error : public std::logic_error {
public:
	invalid_triangle_error(const std::string& what_arg);
	invalid_triangle_error(const char* what_arg);
};

class invalid_rectangle_error : public std::logic_error {
public:
	invalid_rectangle_error(const std::string& what_arg);
	invalid_rectangle_error(const char* what_arg);
};

class invalid_circle_error : public std::logic_error {
public:
	invalid_circle_error(const std::string& what_arg);
	invalid_circle_error(const char* what_arg);
};