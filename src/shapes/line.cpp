#include "line.h"

const String Line::htmlTag = "line";

const String Line::cmdTag = Line::htmlTag;

const String& Line::getHtmlTag() const {
	return Line::htmlTag;
};

const String& Line::getCmdTag() const {
	return Line::cmdTag;
};

void Line::translate(double horizontal, double vertical) {
	x1_ += horizontal;
	x2_ += horizontal;
	y1_ += vertical;
	y2_ += vertical;
}

bool Line::containsPoint(double x, double y) const {
	double a = calcDistance(x1_, y1_, x, y);
	double b = calcDistance(x2_, y2_, x, y);
	double dist = calcDistance(x1_, y1_, x2_, y2_);
	return a + b == dist;
}

bool Line::isWithinRectangle(const Rectangle& rectangle) const {
	return rectangle.containsPoint(x1_, y1_) && rectangle.containsPoint(x2_, y2_);
}
bool Line::isWithinCircle(const Circle& circle) const {
	return circle.containsPoint(x1_, y1_) && circle.containsPoint(x2_, y2_);
}

double Line::getArea() const {
	return -1;
}

double Line::getPerimeter() const {
	return calcDistance(x1_, y1_, x2_, y2_);
}

void Line::outSimple(std::ostream& out) const {
	out << getCmdTag() << ' ' << x1_ << ' ' << y1_ << ' ' << x2_ << ' ' << y2_;
	if (stroke_.getSize() != 0) {
		out << ' ' << stroke_;
	}
}

void Line::outHtml(std::ostream& out) const {
	out << "<" << htmlTag;
	out << " "; Attribute::out(out, "x1", x1_);
	out << " "; Attribute::out(out, "y1", y1_);
	out << " "; Attribute::out(out, "x2", x2_);
	out << " "; Attribute::out(out, "y2", y2_);
	if (stroke_.getSize()) {
		out << " "; Attribute::out(out, "stroke", stroke_);
	}
	out << "/>";
}

void Line::fromArgs(const Vector<String>& args) {
	x1_ = parseDouble(args[0]);
	y1_ = parseDouble(args[1]);
	x2_ = parseDouble(args[2]);
	y2_ = parseDouble(args[3]);
	if (args.getSize() > 4) {
		stroke_ = args[4];
	}
}

void Line::fromAttrs(const Vector<Attribute>& attrs) {
	for (int i = 0; i < attrs.getSize(); i++) {
		String key = attrs[i].getKey();
		String value = attrs[i].getValue();

		if (key == "x1") {
			x1_ = parseDouble(value);
		}
		else if (key == "y1") {
			y1_ = parseDouble(value);
		}
		else if (key == "x2") {
			x2_ = parseDouble(value);
		}
		else if (key == "y2") {
			y2_ = parseDouble(value);
		}
		else if (key == "stroke") {
			stroke_ = value;
		}
	}
}
