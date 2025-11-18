#include "AbstractFactory.h"
#include "RandomFigureFactory.h"
#include "StreamFigureFactory.h"
#include <iostream>
#include <fstream>
#include "../Utils/Readers.h"

AbstractFactory& AbstractFactory::getInstance() {
	static AbstractFactory theInstance;
	return theInstance;
}

std::unique_ptr<FigureFactory> AbstractFactory::createFactory(const std::string& input) {
	if (input == "Random") {
		double min, max;
		readRandomFactoryArguments(min, max);
		return std::make_unique<RandomFigureFactory>(min, max);
	}
	else if(input == "STDIN") {
		std::shared_ptr<std::istream> stdinPtr = std::shared_ptr<std::istream>(&std::cin, [](std::istream*) {});
		return std::make_unique<StreamFigureFactory>(stdinPtr);
	}
	else if (input == "File") {
		std::shared_ptr<std::ifstream> filePtr;
		readStreamFactoryArgumets(filePtr);
		return std::make_unique<StreamFigureFactory>(filePtr);
	}
	else {
		throw std::runtime_error("Invalid input!");
	}
}
