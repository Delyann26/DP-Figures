#include "StreamFigureFactory.h"
#include "StringToFigure.h"
#include "../Utils/Readers.h"
StreamFigureFactory::StreamFigureFactory(std::shared_ptr<std::istream> is) : is(is) {
    
}

std::unique_ptr<Figure> StreamFigureFactory::create() {
    std::string representation;

    while (std::getline(*is, representation)) {
        trim(representation);
        if (!representation.empty()) {
            return StringToFigure::getInstance().createFrom(representation);
        }
    }

    if (is->eof()) {
        return nullptr;
    }

    throw std::runtime_error("Failed to read figure representation from stream!");
}
