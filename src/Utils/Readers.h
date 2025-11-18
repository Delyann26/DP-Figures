#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "../Figures/Figure.h"
#include <fstream>

void readIndex(size_t& index, const std::vector<std::unique_ptr<Figure>>& v);
void readSelection(unsigned& choice);
void readSize(size_t& size);
void readFilePath(std::string& path);

void readRandomFactoryArguments(double& min, double& max);
void readStreamFactoryArgumets(std::shared_ptr<std::ifstream>& filePtr);
void readDecimalNumber(double& value);



void trim(std::string& str);