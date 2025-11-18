#include "Readers.h"
#include "Predicates.h"

void readIndex(size_t& index, const std::vector<std::unique_ptr<Figure>>& v) {
	std::cout << "Enter index: ";
	std::string indexText;

	std::getline(std::cin, indexText);
	trim(indexText);

	if (indexText.empty()) {
		throw std::runtime_error("You must enter index!");
	}

	if (indexText[0] == '-') {
		throw std::runtime_error("Invalid index!");
	}

	size_t pos = 0;

	try {
		index = std::stoul(indexText, &pos);
	}
	catch (...) {
		throw std::runtime_error("Invalid index!");
	}

	if (pos != indexText.size()) {
		throw std::runtime_error("Invalid index!");
	}

	if (index >= v.size()) {
		throw std::runtime_error("Index out of bound!");
	}
}

void readSelection(unsigned& choice) {
	std::string choiceText;
	std::cout << "Select you choice: ";
	while (true) {

		std::getline(std::cin, choiceText);
		trim(choiceText);

		if (choiceText.empty()) {
			std::cout << "Invalid choice! Enter a number between 0 and 3: ";
			continue;
		}

		if (choiceText[0] == '-') {
			std::cout << "Invalid choice! Enter a number between 0 and 3: ";
			continue;
		}

		size_t pos = 0;

		try {
			choice = std::stoul(choiceText, &pos);
		}
		catch (...) {
			std::cout << "Invalid choice! Enter a number between 0 and 3: ";
			continue;
		}

		if (pos != choiceText.size()) {
			std::cout << "Invalid choice! Enter a number between 0 and 3: ";
			continue;
		}

		if (0 <= choice && choice <= 3) {
			break;
		}
		std::cout << "Invalid choice! Enter a number between 0 and 3: ";
	}
}

void readSize(size_t& size) {
	std::string sizeText;

	std::cout << "Enter the amount of figures: ";
	while (true) {

		std::getline(std::cin, sizeText);
		trim(sizeText);

		if (sizeText.empty()) {
			std::cout << "Invalid size! Enter a positive number: ";
			continue;
		}

		if (sizeText[0] == '-') {
			std::cout << "Invalid size! Enter a positive number: ";
			continue;
		}

		size_t pos = 0;

		try {
			size = std::stoul(sizeText, &pos);
		}
		catch (...) {
			std::cout << "Invalid size! Enter a positive number: ";
			continue;
		}

		if (pos != sizeText.size()) {
			std::cout << "Invalid size! Enter a positive number: ";
			continue;
		}

		if (size > 0) {
			break;
		}
		std::cout << "Invalid size! Enter a positive number: ";
	}
}

void readFilePath(std::string& path) {
	std::cout << "Enter file path: ";

	while (true) {
		std::getline(std::cin, path);
		if (!path.empty()) {
			break;
		}
		std::cout << "Empty path is not a valid one! Enter again: ";
	}
}

void readRandomFactoryArguments(double& min, double& max) {
	std::cout << "Enter min value: ";
	readDecimalNumber(min);
	std::cout << "Enter max value: ";
	readDecimalNumber(max);

	if (min > max) {
		std::cout << "Min and max values were swapped for safety!\n";
		std::swap(min, max);
	}
}

void readStreamFactoryArgumets(std::shared_ptr<std::ifstream>& filePtr) {
	std::cout << "Enter file path: ";
	std::string path;
	while (true) {
		std::getline(std::cin, path);

		trim(path);

		if (path.empty()) {
			std::cout << "Path cannot be empty! Try again: ";
			continue;
		}

		filePtr = std::make_shared<std::ifstream>(path);
		if (filePtr->is_open()) {
			return;
		}

		std::cout << "File does not exist or cannot be opened! Try again: ";
		continue;
	}
}

void readDecimalNumber(double& value) {
	std::string valueText;
	while (true) {

		std::getline(std::cin, valueText);
		trim(valueText);

		if (valueText.empty()) {
			std::cout << "Invalid decimal value! Enter again: ";
			continue;
		}

		size_t pos = 0;

		try {
			value = std::stod(valueText, &pos);
		}
		catch (...) {
			std::cout << "Invalid decimal value! Enter again: ";
			continue;
		}

		if (pos != valueText.size()) {
			std::cout << "Invalid decimal value! Enter again: ";
			continue;
		}

		if (isValidSide(value)) {
			break;
		}
		std::cout << "Invalid decimal value! Enter again: ";
	}
}

void trim(std::string& str) {
	str.erase(0, str.find_first_not_of(" \t\n"));
	str.erase(str.find_last_not_of(" \t\n") + 1);
}




