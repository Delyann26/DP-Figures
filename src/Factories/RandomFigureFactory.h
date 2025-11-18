#pragma once
#include "FigureFactory.h"
#include <random>

class RandomFigureFactory : public FigureFactory {
public:
	RandomFigureFactory(double min, double max);

	virtual std::unique_ptr<Figure> create() override;

private:

	double randomDouble(double min, double max);
	
	std::random_device rd;
	std::mt19937 gen;
	double min;
	double max;
};