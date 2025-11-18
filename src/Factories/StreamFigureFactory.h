#pragma once
#include "FigureFactory.h"
#include <functional>

class StreamFigureFactory : public FigureFactory {
public:
	StreamFigureFactory(std::shared_ptr<std::istream> is);
	virtual std::unique_ptr<Figure> create() override;
private:
	std::shared_ptr<std::istream> is;
};