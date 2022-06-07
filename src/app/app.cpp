#include "app.h"

void App::free() {
	for (int i = 0; i < shapes_.getSize(); i++) {
		delete shapes_[i];
	}
}

void App::run() {
	String input;
	
	while(true) {
		try {
			std::cout << "> ";
			input.getLine(std::cin);

			Vector<String> args = input.split(' ');
			String cmd = args[0];
			args.popFront();

			if (cmd == "open") {
				open(args[0]);
			}
			else if (cmd == "save") {
				save();
			}
			else if (cmd == "print") {
				print();
			}
			else if (cmd == "create") {
				String tag = args[0];
				args.popFront();
				create(tag, args);
			}
			else if (cmd == "erase") {
				int index = parseDouble(args[0]);
				erase(index);
			}
			else if (cmd == "translate") {
				translate(args);
			}
			else if (cmd == "within") {
				String tag = args[0];
				args.popFront();
				within(tag, args);
			}
			else if (cmd == "pointIn") {
				double x = parseDouble(args[0]);
				double y = parseDouble(args[1]);
				pointIn(x, y);
			}
			else if (cmd == "areas") {
				areas();
			}
			else if (cmd == "pers") {
				perimeters();
			}
			else if (cmd == "exit") {
				break;
			}
		}
		catch (const char* msg) {
			std::cout << msg << "\n";
		}
	}
}

void App::open(String filename) {
	free();
	filename_ = filename;
	shapes_ = SvgFileHandler::getInstance().readFromFile(filename_);
	std::cout << "Successfully opened " << filename_ << "\n";
}

void App::save() {
	SvgFileHandler::getInstance().saveToFile(filename_, shapes_);
	std::cout << "Successfully saved the changes to " << filename_ << "\n";
}

void App::print() {
	for (int i = 0; i < shapes_.getSize(); i++) {
		std::cout << (i + 1) << ". ";
		shapes_[i]->outSimple(std::cout);
		std::cout << '\n';
	}
}

void App::create(const String& tag, const Vector<String>& args) {
	Shape* shape = ShapeFactory::getInstance().createFromArgs(tag, args);
	if (shape != nullptr) {
		shapes_.pushBack(shape);
		std::cout << "Successfully created " << tag << " (" << shapes_.getSize() << ")\n";
	}
}

void App::erase(int number) {
	if (number <= 0 || number > shapes_.getSize()) {
		std::cout << "There is no figure number " << number << "!";
		return;
	}
		
	Shape* shape = shapes_.popAt(number - 1);
	std::cout << "Erased " << shape->getCmdTag() << "(" << number << "(\n";
	delete shape;
}

void App::translate(Vector<String>& args) {
	String indexOrDimension = args[0];
	int number = 0;
	double horizontal = 0;
	double vertical = 0;
	try {
		number = parseDouble(indexOrDimension);
		args.popFront();
	}
	catch (...) {}
	for (int i = 0; i < args.getSize(); i++) {
		Attribute attr(args[i]);

		String dimension = attr.getKey();
		double value = parseDouble(attr.getValue());

		if (dimension == "horizontal")
			horizontal = value;
		else if (dimension == "vertical")
			vertical = value;
	}

	if (number != 0) {
		if (number < 0 || number > shapes_.getSize()) {
			std::cout << "There is no figure number " << number << "!\n";
			return;
		}
		shapes_[number - 1]->translate(horizontal, vertical);
		std::cout << "Translated figure " << number << "\n";
	}
	else {
		for (int i = 0; i < shapes_.getSize(); i++) {
			shapes_[i]->translate(horizontal, vertical);
		}
		std::cout << "Translated all figures\n";
	}
}

void App::within(const String& tag, const Vector<String>& args) {
	Shape* shape = ShapeFactory::getInstance().createFromArgs(tag, args);
	if (shape != nullptr) {
		bool oneWithin = false;
		for (int i = 0; i < shapes_.getSize(); i++) {
			bool currWithin = false;
			if (shape->getCmdTag() == Rectangle::cmdTag) {
				currWithin = shapes_[i]->isWithinRectangle(*dynamic_cast<Rectangle*>(shape));
			}
			else if (shape->getCmdTag() == Circle::cmdTag) {
				currWithin = shapes_[i]->isWithinCircle(*dynamic_cast<Circle*>(shape));
			}
			if (currWithin) {
				oneWithin = true;
				std::cout << (i + 1) << ". ";
				shapes_[i]->outSimple(std::cout);
				std::cout << "\n";
			}
		}
		if (!oneWithin) {
			std::cout << "No figures are located within ";
			shape->outSimple(std::cout);
			std::cout << "\n";
		}
		delete shape;
	}
}

void App::pointIn(double x, double y) {
	bool oneContains = false;
	for (int i = 0; i < shapes_.getSize(); i++) {
		if (shapes_[i]->containsPoint(x, y)) {
			oneContains = true;
			std::cout << (i + 1) << ". ";
			shapes_[i]->outSimple(std::cout);
			std::cout << '\n';
		}
	}
	if (!oneContains) {
		std::cout << "No figures contain point " << x << " " << y << "\n";
	}
}

void App::areas() {
	for (int i = 0; i < shapes_.getSize(); i++) {
		Shape* shape = shapes_[i];
		std::cout << (i + 1) << ". " << shape->getCmdTag() << " " << shape->getArea() << "\n";
	}
}

void App::perimeters() {
	for (int i = 0; i < shapes_.getSize(); i++) {
		Shape* shape = shapes_[i];
		std::cout << (i + 1) << ". " << shape->getCmdTag() << " " << shape->getPerimeter() << "\n";
	}
}
