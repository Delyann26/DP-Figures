#pragma once
#include "Figure.h"

class Triangle : public Figure {
public:
	Triangle(double sideA, double sideB, double sideC);

	static std::unique_ptr<Figure> create(std::istringstream& iss);

	virtual double perimeter() const override;
	virtual std::string to_string() const override;
	virtual std::unique_ptr<Figure> clone() const override; 

	double getSideA() const;
	double getSideB() const;
	double getSideC() const;

private:

	static void swapIf(double& x, double& y);

	double sideA;
	double sideB;
	double sideC;
};