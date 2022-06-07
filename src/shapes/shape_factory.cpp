#include "shape_factory.h"

ShapeFactory::ShapeFactory() { }

ShapeFactory& ShapeFactory::getInstance() {
	static ShapeFactory instance;
	return instance;
}

Shape* ShapeFactory::createByCmdTag(const String& tag) const {
	if (tag == Rectangle::cmdTag)
		return new Rectangle();
	if (tag == Circle::cmdTag)
		return new Circle();
	if (tag == Line::cmdTag)
		return new Line();
	return nullptr;
}

Shape* ShapeFactory::createByHtmlTag(const String& tag) const {
	if (tag == Rectangle::htmlTag)
		return new Rectangle();
	if (tag == Circle::htmlTag)
		return new Circle();
	if (tag == Line::htmlTag)
		return new Line();
	return nullptr;
}

Shape* ShapeFactory::createFromArgs(const String& tag, const Vector<String>& args) const {
	Shape* shape = createByCmdTag(tag);
	if (shape != nullptr) {
		shape->fromArgs(args);
	}
	return shape;
}

Shape* ShapeFactory::createFromAttrs(const String& tag, const Vector<String>& attrs) const {
	Shape* shape = createByHtmlTag(tag);
	if (shape != nullptr) {
		Vector<Attribute> attrsParsed;
		for (int i = 0; i < attrs.getSize(); i++) {
			attrsParsed.pushBack(Attribute(attrs[i]));
		}
		shape->fromAttrs(attrsParsed);
	}
	return shape;
}