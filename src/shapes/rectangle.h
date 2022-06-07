#pragma once

#include "shape.h"
#include "attribute.hpp"
#include "circle.h"
#include "../utils/number_helper.h"

class Rectangle : public Shape {
	double x_;
	double y_;
	double width_;
	double height_;
	String fill_;

public:
	static const String htmlTag;
	static const String cmdTag;

	virtual const String& getHtmlTag() const;
	virtual const String& getCmdTag() const;

	double getX() const;
	double getY() const;
	double getX2() const;
	double getY2() const;

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