#pragma once
#include "Figure.h"

class Circle : public Figure {
public:
	
	Circle(double radius);

	static std::unique_ptr<Figure> create(std::istringstream& iss);

	virtual double perimeter() const override;
	virtual std::string to_string() const override;
	virtual std::unique_ptr<Figure> clone() const override;

	double getRadius() const;

private:
	double radius;
};


