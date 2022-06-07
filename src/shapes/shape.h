#pragma once

class ShapeFactory;

#include "shapes.h"
#include "attribute.hpp"

#include "../utils/string.h"
#include "../utils/vector.hpp"

class Shape {
public:	
	virtual const String& getHtmlTag() const = 0;
	virtual const String& getCmdTag() const = 0;

	virtual void translate(double horizontal, double vertical) = 0;

	virtual bool containsPoint(double x, double y) const = 0;
	
	virtual bool isWithinRectangle(const Rectangle& rectangle) const = 0;
	virtual bool isWithinCircle(const Circle& circle) const = 0;

	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;

	virtual void outSimple(std::ostream& out) const = 0;
	virtual void outHtml(std::ostream& out) const = 0;

protected:
	friend class ShapeFactory;

	virtual void fromArgs(const Vector<String>& args) = 0;
	virtual void fromAttrs(const Vector<Attribute>& attrs) = 0;
};