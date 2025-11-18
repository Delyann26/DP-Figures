#pragma once
#include "../Figures/Figure.h"
#include <functional>
#include <unordered_map>

class StringToFigure {
public:
	using CreatorFunction = std::function<std::unique_ptr<Figure>(std::istringstream&)>;

	static StringToFigure& getInstance();
	std::unique_ptr<Figure> createFrom(const std::string& representation) const;

private:
	StringToFigure();
	StringToFigure(const StringToFigure& other) = delete;
	StringToFigure& operator=(const StringToFigure& other) = delete;

	void registerCreator(const std::string& typeName, const CreatorFunction& creator);
	void init();

	std::unordered_map<std::string, CreatorFunction> creators;
};