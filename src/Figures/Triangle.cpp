#include "Triangle.h"
#include "Exceptions.h"
#include "Predicates.h"
Triangle::Triangle(double sideA, double sideB, double sideC) {
	
	if (!isValidSide(sideA) || !isValidSide(sideB) || !isValidSide(sideC)) {
		throw invalid_triangle_error("Triangle sides must be positive, finite numbers!");
	}

	swapIf(sideA, sideB);
	swapIf(sideB, sideC);
	swapIf(sideA, sideB);

	//A <= B <= C

	if (willAddOverflow(sideA, sideB)) {
		throw invalid_triangle_error("Overflow while checking triangle inequality!");
	}

	double sumAB = sideA + sideB;
	if (sumAB <= sideC) {
		throw invalid_triangle_error("Triangle inequality violated");
	}

	if (willAddOverflow(sumAB, sideC)) {
		throw invalid_triangle_error("Overflow while calculating perimeter");
	}

	this->sideA = sideA;
	this->sideB = sideB;
	this->sideC = sideC;
}

std::unique_ptr<Figure> Triangle::create(std::istringstream& iss) {
	
	std::string sideText;
	double sides[3];

	for (size_t i = 0; i < 3; i++) {

		size_t pos = 0;

		if (!(iss >> sideText)) {
			throw invalid_triangle_error("Triangle's side " + std::to_string(i + 1) + " is missing!");
		}
		
		try {
			sides[i] = std::stod(sideText, &pos);
		}
		catch (...) {
			throw invalid_triangle_error("Triangle's side " + std::to_string(i + 1) + " is invalid!");
		}

		if (pos != sideText.size()) {
			throw invalid_triangle_error("Unexpected characters after side " + std::to_string(i + 1) + ".");
		}
	}

	if (iss >> sideText) {
		throw invalid_triangle_error("Unexpected extra input!");
	}

	return std::make_unique<Triangle>(sides[0], sides[1], sides[2]);
}

double Triangle::getSideA() const {
	return sideA;
}

double Triangle::getSideB() const {
	return sideB;
}

double Triangle::getSideC() const {
	return sideC;
}

double Triangle::perimeter() const {
	return sideA + sideB + sideC;
}

std::string Triangle::to_string() const {
	return "Triangle " + std::to_string(sideA) + " " + std::to_string(sideB) + " " + std::to_string(sideC);
}

std::unique_ptr<Figure> Triangle::clone() const {
	return std::make_unique<Triangle>(*this);
}

void Triangle::swapIf(double& x, double& y) {
	if (x > y) {
		std::swap(x, y);
	}
}
