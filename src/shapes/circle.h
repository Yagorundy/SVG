#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

#include "shape.h"
#include "attribute.hpp"
#include "rectangle.h"
#include "../utils/number_helper.h"

class Circle : public Shape {
	double cx_;
	double cy_;
	double r_;
	String fill_;

public:
	static const String htmlTag;
	static const String cmdTag;

	virtual const String& getHtmlTag() const;
	virtual const String& getCmdTag() const;

	double getCx() const;
	double getCy() const;
	double getR() const;

	virtual void translate(double horizontal, double vertical);

	virtual bool containsPoint(double x, double y) const;

	virtual bool isWithinRectangle(const Rectangle& rectangle) const;
	virtual bool isWithinCircle(const Circle& circle) const;

	virtual double getArea() const;
	virtual double getPerimeter() const;

	virtual void outSimple(std::ostream& out) const;
	virtual void outHtml(std::ostream& out) const;

protected:
	virtual void fromArgs(const Vector<String>& args);
	virtual void fromAttrs(const Vector<Attribute>& attrs);
};