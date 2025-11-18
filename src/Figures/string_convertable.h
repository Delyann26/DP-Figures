#pragma once
#include <string>

class string_convertable {
public:
	virtual std::string to_string() const = 0;
	virtual ~string_convertable() = default;
};