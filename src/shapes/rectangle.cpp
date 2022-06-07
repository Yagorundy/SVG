#include "rectangle.h"

const String Rectangle::htmlTag = "rect";

const String Rectangle::cmdTag = "rectangle";

const String& Rectangle::getHtmlTag() const {
	return Rectangle::cmdTag;
};

const String& Rectangle::getCmdTag() const {
	return Rectangle::cmdTag;
};

double Rectangle::getX() const {
	return  x_;
}
double Rectangle::getY() const {
	return y_;
}
double Rectangle::getX2() const {
	return  x_ + width_;
}
double Rectangle::getY2() const {
	return y_ + height_;
}

void Rectangle::translate(double horizontal, double vertical) {
	x_ += horizontal;
	y_ += vertical;
}

bool Rectangle::containsPoint(double x, double y) const {
	double x2 = getX2();
	double y2 = getY2();

	return (x_ >= x && x >= x2 && y_ >= y && y >= y2)
		|| (x2 >= x && x >= x_ && y2 >= y && y >= y_);
}

bool Rectangle::isWithinRectangle(const Rectangle& rectangle) const {
	return rectangle.containsPoint(x_, y_) && rectangle.containsPoint(getX2(), getY2());
}
bool Rectangle::isWithinCircle(const Circle& circle) const {
	return circle.containsPoint(x_, y_) && circle.containsPoint(getX2(), getY2());
}

double Rectangle::getArea() const {
	return width_ * height_;
}

double Rectangle::getPerimeter() const {
	return (width_ + height_) * 2;
}

void Rectangle::outSimple(std::ostream& out) const {
	out << getCmdTag() << ' ' << x_ << ' ' << y_ << ' ' << width_ << ' ' << height_;
	if (fill_.getSize() != 0) {
		out << ' ' << fill_;
	}
}

void Rectangle::outHtml(std::ostream& out) const {
	out << "<" << htmlTag;
	out << " "; Attribute::out(out, "x", x_);
	out << " "; Attribute::out(out, "y", y_);
	out << " "; Attribute::out(out, "width", width_);
	out << " "; Attribute::out(out, "height", height_);
	if (fill_.getSize()) {
		out << " "; Attribute::out(out, "fill", fill_);
	}
	out << "/>";
}

void Rectangle::fromArgs(const Vector<String>& args) {
	x_ = parseDouble(args[0]);
	y_ = parseDouble(args[1]);
	width_ = parseDouble(args[2]);
	height_ = parseDouble(args[3]);
	if (args.getSize() > 4) {
		fill_ = args[4];
	}
}

void Rectangle::fromAttrs(const Vector<Attribute>& attrs) {
	for (int i = 0; i < attrs.getSize(); i++) {
		String key = attrs[i].getKey();
		String value = attrs[i].getValue();

		if (key == "x") {
			x_ = parseDouble(value);
		}
		else if (key == "y") {
			y_ = parseDouble(value);
		}
		else if (key == "width") {
			width_ = parseDouble(value);
		}
		else if (key == "height") {
			height_ = parseDouble(value);
		}
		else if (key == "fill") {
			fill_ = value;
		}
	}
}
