#include "circle.h"

const String Circle::htmlTag = "circle";

const String Circle::cmdTag = Circle::htmlTag;

const String& Circle::getHtmlTag() const {
	return Circle::htmlTag;
};

const String& Circle::getCmdTag() const {
	return Circle::cmdTag;
};

double Circle::getCx() const {
	return cx_;
}
double Circle::getCy() const {
	return cy_;
}
double Circle::getR() const {
	return r_;
}

void Circle::translate(double horizontal, double vertical) {
	cx_ += horizontal;
	cy_ += vertical;
}

bool Circle::containsPoint(double x, double y) const {
	return calcDistance(cx_, cy_, x, y) <= r_;
}

bool Circle::isWithinRectangle(const Rectangle& rectangle) const {
	double x1 = rectangle.getX();
	double y1 = rectangle.getY();
	double x2 = rectangle.getX2();
	double y2 = rectangle.getY2();
	return rectangle.containsPoint(cx_, cy_)
		&& !containsPoint(x1, y1)
		&& !containsPoint(x2, y2)
		&& !containsPoint(x1, y2)
		&& !containsPoint(x2, y1);
}
bool Circle::isWithinCircle(const Circle& circle) const {
	double centerDist = calcDistance(cx_, cy_, circle.cx_, circle.cy_);
	return centerDist + r_ < circle.r_;
}

double Circle::getArea() const {
	return M_PI * r_ * r_;
}

double Circle::getPerimeter() const {
	return 2 * M_PI * r_;
}

void Circle::outSimple(std::ostream& out) const {
	out << getCmdTag() << ' ' << cx_ << ' ' << cy_ << ' ' << r_;
	if (fill_.getSize() != 0) {
		out << ' ' << fill_;
	}
}

void Circle::outHtml(std::ostream& out) const {
	out << "<" << htmlTag;
	out << " "; Attribute::out(out, "cx", cx_);
	out << " "; Attribute::out(out, "cy", cy_);
	out << " "; Attribute::out(out, "r", r_);
	if (fill_.getSize()) {
		out << " "; Attribute::out(out, "fill", fill_);
	}
	out << "/>";
}

void Circle::fromArgs(const Vector<String>& args) {
	cx_ = parseDouble(args[0]);
	cy_ = parseDouble(args[1]);
	r_ = parseDouble(args[2]);
	if (args.getSize() > 3) {
		fill_ = args[3];
	}
}

void Circle::fromAttrs(const Vector<Attribute>& attrs) {
	for (int i = 0; i < attrs.getSize(); i++) {
		String key = attrs[i].getKey();
		String value = attrs[i].getValue();

		if (key == "cx") {
			cx_ = parseDouble(value);
		}
		else if (key == "cy") {
			cy_ = parseDouble(value);
		}
		else if (key == "r") {
			r_ = parseDouble(value);
		}
		else if (key == "fill") {
			fill_ = value;
		}
	}
}
