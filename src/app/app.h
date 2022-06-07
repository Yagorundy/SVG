#pragma once

#include <iostream>

#include "../utils/vector.hpp"
#include "../shapes/shape.h"
#include "../shapes/shape_factory.h"
#include "svg_file_handler.h"

class App {
public:
	void run();

private:
	Vector<Shape*> shapes_;
	void free();
	
	String filename_;
	void open(String filename);
	void save();

	void print();
	void create(const String& tag, const Vector<String>& args);
	void erase(int index);
	void translate(Vector<String>& args);
	void within(const String& tag, const Vector<String>& args);
	void pointIn(double x, double y);
	void areas();
	void perimeters();
};