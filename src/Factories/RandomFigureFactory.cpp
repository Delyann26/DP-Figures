#include "RandomFigureFactory.h"
#include "StringToFigure.h"
#include "../Utils/Predicates.h"

RandomFigureFactory::RandomFigureFactory(double min, double max) : gen(rd()) {
	if (!isValidSide(min) || !isValidSide(max)) {
		throw std::invalid_argument("Min and max must be positive finite numbers!");
	}
	if (max <= min) {
		throw std::invalid_argument("Max must be greater than min!");
	}
	this->min = min;
	this->max = max;
}

std::unique_ptr<Figure> RandomFigureFactory::create() {
	
	std::uniform_int_distribution<int> typeDist(0, 2);
	int type = typeDist(gen);

	std::ostringstream oss;

	switch (type) {
	case 0: {
		double radius = randomDouble(min, max);
		oss << "Circle " << radius;
		break;
	}
	case 1: {
		double width = randomDouble(min, max);
		double height = randomDouble(min, max);
		oss << "Rectangle " << width << " " << height;
		break;
	}
	case 2: {
		double a = randomDouble(min, max);
		double b = randomDouble(a, max);       // a <= b <= c < a+b
		double minC = b;
		double maxC = std::min(a + b - 0.0001, max);
		double c = randomDouble(minC, maxC);
		oss << "Triangle " << a << " " << b << " " << c;
	}
	}

	std::string representation = oss.str();

	return StringToFigure::getInstance().createFrom(representation);
}

double RandomFigureFactory::randomDouble(double min, double max) {
	std::uniform_real_distribution<double> value(min, max);
	return value(gen);
}

