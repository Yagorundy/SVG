#pragma once

#include <cmath>

#include "shape.h"
#include "attribute.hpp"
#include "rectangle.h"
#include "circle.h"
#include "../utils/number_helper.h"

class Line : public Shape {
	double x1_;
	double y1_;
	double x2_;
	double y2_;
	String stroke_;

public:
	static const String htmlTag;
	static const String cmdTag;

	virtual const String& getHtmlTag() const;
	virtual const String& getCmdTag() const;

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