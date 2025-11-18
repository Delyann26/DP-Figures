#include "Circle.h"
#include "../Utils/Exceptions.h"
#include "../Utils/Predicates.h"


Circle::Circle(double radius) {

	if (!isValidSide(radius)) {
		throw invalid_circle_error("Circle's radius must be positive and finite!");
	}

	if (willMulOverflow(radius, 2 * 3.14)) {
		throw invalid_circle_error("Circle perimeter would overflow for this radius!");
	}

	this->radius = radius;
}

std::unique_ptr<Figure> Circle::create(std::istringstream& iss) {
	
	std::string radiusText;

	size_t pos = 0;
	double radius = 0;

	if (!(iss >> radiusText)) {
		throw invalid_circle_error("Circle's radius is missing!");
	}
	
	try {
		radius = std::stod(radiusText, &pos);
	}
	catch(...) {
		throw invalid_circle_error("Circle's radius is invalid!");
	}

	if (pos != radiusText.size()) { 
		throw invalid_circle_error("Unexpected characters after radius.");
	}

	if (iss >> radiusText) {
		throw invalid_circle_error("Unexpected extra input!");
	}

	return std::make_unique<Circle>(radius);
}

double Circle::getRadius() const {
	return radius;
}

double Circle::perimeter() const {
	return 2 * 3.14 * this->radius;
}

std::string Circle::to_string() const {
	return "Circle " + std::to_string(this->radius);
}

std::unique_ptr<Figure> Circle::clone() const {
	return std::make_unique<Circle>(*this);
}




