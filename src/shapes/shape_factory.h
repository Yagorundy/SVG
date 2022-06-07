#pragma once

#include "../utils/vector.hpp"
#include "../utils/string.h"
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"

class ShapeFactory {
	ShapeFactory();

public:
	ShapeFactory(ShapeFactory const&) = delete;
	void operator=(ShapeFactory const&) = delete;
	static ShapeFactory& getInstance();

	Shape* createByCmdTag(const String& tag) const;
	Shape* createByHtmlTag(const String& tag) const;
	Shape* createFromArgs(const String& tag, const Vector<String>& args) const;
	Shape* createFromAttrs(const String& tag, const Vector<String>& attrs) const;
};