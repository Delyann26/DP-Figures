#include "Rectangle.h"
#include "Predicates.h"
#include "Exceptions.h"

Rectangle::Rectangle(double width, double height) {

	if (!isValidSide(width) || !isValidSide(height)) {
		throw invalid_rectangle_error("Rectangle's width and height cannot be less than or equal to zero!");
	}

	if (willAddOverflow(width, height)) {
		throw invalid_rectangle_error("Rectangle perimeter sum would overflow!");
	}

	double sum = width + height;

	if (willMulOverflow(sum, 2.0)) {
		throw invalid_rectangle_error("Rectangle perimeter would overflow!");
	}

	this->width = width;
	this->height = height;
}

std::unique_ptr<Figure> Rectangle::create(std::istringstream& iss) {
	std::string sideText;
	double sides[2];

	for (size_t i = 0; i < 2; i++) {

		size_t pos = 0;

		if (!(iss >> sideText)) {
			throw invalid_rectangle_error("Rectangles's side " + std::to_string(i + 1) + " is missing!");
		}

		try {
			sides[i] = std::stod(sideText, &pos);
		}
		catch (...) {
			throw invalid_rectangle_error("Rectangles's side " + std::to_string(i + 1) + " is invalid!");
		}

		if (pos != sideText.size()) {
			throw invalid_rectangle_error("Unexpected characters after side " + std::to_string(i + 1) + ".");
		}
	}

	if (iss >> sideText) {
		throw invalid_rectangle_error("Unexpected extra input!");
	}

	return std::make_unique<Rectangle>(sides[0], sides[1]);
}

double Rectangle::getWidth() const {
	return width;
}

double Rectangle::getHeight() const {
	return height;
}

double Rectangle::perimeter() const {
	return 2 * (width + height);
}

std::string Rectangle::to_string() const {
	return "Rectangle " + std::to_string(width) + " " + std::to_string(height);
}

std::unique_ptr<Figure> Rectangle::clone() const {
	return std::make_unique<Rectangle>(*this);
}



