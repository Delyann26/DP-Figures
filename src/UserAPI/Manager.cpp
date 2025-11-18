#include "Manager.h"
#include <iostream>
#include <fstream>
#include "../Factories/AbstractFactory.h"
#include <../Utils/Predicates.h>
#include <../Utils/Readers.h>

Manager& Manager::getInstance() {
	static Manager theInstance;
	return theInstance;
}

void Manager::startProgram() {
	selectFactory();
	if (factory == nullptr) {
		return;
	}
	createFigures();
	factory.reset();
	processCommand();
}

void Manager::selectFactory() {
	std::cout << "How do you want to generate figures? Select between:\n";
	std::cout << "1. Random\n";
	std::cout << "2. STDIN\n";
	std::cout << "3. File\n";
	std::cout << "0. Exit\n";

	unsigned choice;
	readSelection(choice);

	try {
		switch (choice) {
		case 1: factory = AbstractFactory::getInstance().createFactory("Random"); break;
		case 2: factory = AbstractFactory::getInstance().createFactory("STDIN"); break;
		case 3: factory = AbstractFactory::getInstance().createFactory("File"); break;
		}
	}
	catch(const std::exception& e){
		std::cout << "Factory creation failed: " << e.what() << "\n";
		return;
	}
	std::cout << "Factory created successfully\n";
}

void Manager::createFigures() {

	size_t size;
	readSize(size);

	size_t created = 0;

	while (created < size) {
		try {
			std::unique_ptr<Figure> fig = factory->create();
			if (!fig) {
				std::cout << "Input stream reached its end.\n";
				break;
			}
			figures.push_back(std::move(fig));
			created++;
		}
		catch (const std::exception& e) {
			std::cout << "Error creating figure: " << e.what() << "\n";
		}
	}

	std::cout << "Successfully created " << created << " figure(s).\n";
}

void Manager::processCommand() {
	std::string command;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, command);
		trim(command);
		if (command.empty()) {
			continue;
		}
		try {

			if (command == "exit") {
				break;
			}
			else if (command == "list") {
				listFigures();
			}
			else if (command == "duplicate") {
				duplicate();
			}
			else if (command == "remove") {
				remove();
			}
			else if (command == "save") {
				save();
			}
			else {
				std::cout << "Invalid command!\n";
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}
}

void Manager::listFigures() const {
	std::cout << "\n";
	for (size_t i = 0; i < figures.size(); i++) {
		std::cout << figures[i]->to_string() << "\n";
	}
	std::cout << "\n";
}

void Manager::duplicate() {
	if (figures.empty()) {
		std::cout << "No available figures!\n";
		return;
	}
	size_t index;
	readIndex(index, figures);
	figures.push_back(figures[index]->clone());
}

void Manager::remove() {
	if (figures.empty()) {
		std::cout << "No available figures!\n";
		return;
	}
	size_t index;
	readIndex(index, figures);
	figures.erase(figures.begin() + index);
}

void Manager::save() const {
	std::string str;
	readFilePath(str);
	std::ofstream ofs(str);
	if (!ofs.is_open()) {
		throw std::runtime_error("File cannot be opened!");
	}
	for (size_t i = 0; i < figures.size(); i++) {
		ofs << figures[i]->to_string() << "\n";
	}
	ofs.close();
}
