#pragma once
#include "../Figures/Figure.h"


class FigureFactory {
public:
	virtual std::unique_ptr<Figure> create() = 0;
	virtual ~FigureFactory() = default;
};