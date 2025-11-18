	#pragma once
	#include <vector>
	#include "../Factories/FigureFactory.h"


class Manager {
public:

	static Manager& getInstance();

	void startProgram();

private:

	Manager() = default;
	Manager(const Manager& other) = delete;
	Manager& operator=(const Manager& other) = delete;

	void selectFactory();
	void createFigures();

	void processCommand();

	void listFigures() const;
	void duplicate();
	void remove();
	void save() const;

	std::unique_ptr<FigureFactory>  factory;
	std::vector<std::unique_ptr<Figure>> figures;
};