#pragma once

#include <fstream>

#include "../utils/vector.hpp"
#include "../utils/string.h"
#include "../shapes/shape.h"
#include "../shapes/shape_factory.h"

class SvgFileHandler {
	SvgFileHandler();

public:
	SvgFileHandler(SvgFileHandler const&) = delete;
	void operator=(SvgFileHandler const&) = delete;
	static SvgFileHandler& getInstance();

	Vector<Shape*> readFromFile(const String& filename);
	void saveToFile(const String& filename, const Vector<Shape*>& shapes);
};