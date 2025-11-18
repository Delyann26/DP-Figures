#pragma once
#include "string_convertable.h"
#include <memory>
#include <sstream>


class Figure : public string_convertable {
public:
	virtual ~Figure() = default;
	virtual double perimeter() const = 0;
	virtual std::unique_ptr<Figure> clone() const = 0;
};