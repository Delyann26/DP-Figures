#pragma once
#include "FigureFactory.h"


class AbstractFactory {
public:

	static AbstractFactory& getInstance();

	std::unique_ptr<FigureFactory> createFactory(const std::string& input);

private:
	AbstractFactory() = default;
	AbstractFactory(const AbstractFactory& other) = delete;
	AbstractFactory& operator=(const AbstractFactory& other) = delete;
};