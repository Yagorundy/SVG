#include "svg_file_handler.h"

SvgFileHandler::SvgFileHandler() { }

SvgFileHandler& SvgFileHandler::getInstance() {
	static SvgFileHandler instance;
	return instance;
}

// not very advanced logic for sake of time and simplicity

Vector<Shape*> SvgFileHandler::readFromFile(const String& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw "Could not open file";

	Vector<Shape*> shapes;
	while (!file.eof())
	{
		const int buffSize = 2048;
		char buff[buffSize];

		file.getline(buff, buffSize, '<');
		file.getline(buff, buffSize, '>');

		size_t len = strlen(buff);
		if (!len)
			break;
		if (buff[len - 1] == '/')
			buff[len - 1] = '\0';

		Vector<String> tokens = String(buff).split(' ');

		String tag = tokens[0];
		tokens.popFront();

		Shape* shape = ShapeFactory::getInstance().createFromAttrs(tag, tokens);
		if (shape != nullptr) {
			shapes.pushBack(shape);
		}
	}
	file.close();
	return shapes;
}

// not very advanced logic for sake of time and simplicity

void SvgFileHandler::saveToFile(const String& filename, const Vector<Shape*>& shapes) {
	std::ofstream file(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n"
		<< "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
		<< "<svg>\n";
	for (int i = 0; i < shapes.getSize(); i++) {
		file << "  ";
		shapes[i]->outHtml(file);
		file << "\n";
	}
	file << "</svg>";
	file.close();
}