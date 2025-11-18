#include "StringToFigure.h"
#include "../Figures/Circle.h"
#include "../Figures/Rectangle.h"
#include "../Figures/Triangle.h"


StringToFigure& StringToFigure::getInstance() {
	static StringToFigure theInstance;
	return theInstance;
}

std::unique_ptr<Figure> StringToFigure::createFrom(const std::string& representation) const {
	std::istringstream iss(representation);
	std::string figureType;
	
	if (!(iss >> figureType)) {
		throw std::runtime_error("Reading figure representation failed!");
	}

	char& c = figureType[0];
	if (std::islower(c)) {
		c = std::toupper(c);
	}

	auto it = creators.find(figureType);
	if (it == creators.end()) {
		throw std::runtime_error("No such figure exists!");
	}

	return it->second(iss);
}

StringToFigure::StringToFigure() {
	init();
}

void StringToFigure::registerCreator(const std::string& figureType, const CreatorFunction& creator) {
	creators[figureType] = creator;
}

void StringToFigure::init() {
	registerCreator("Circle", Circle::create);
	registerCreator("Rectangle", Rectangle::create);
	registerCreator("Triangle", Triangle::create);
}

