#pragma once
#include "Figure.h"

class Rectangle : public Figure {
public:
	Rectangle(double width, double height);

	static std::unique_ptr<Figure> create(std::istringstream& iss);

	virtual double perimeter() const override;
	virtual std::string to_string() const override;
	virtual std::unique_ptr<Figure> clone() const override;

	double getWidth() const;
	double getHeight() const;

private:
	double width;
	double height;
};