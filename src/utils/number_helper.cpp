#include "number_helper.h"

const char* kInvalidNumMsg = "Invalid number";

int parseDigit(const char& ch) {
	if (ch < '0' || ch > '9')
		throw kInvalidNumMsg;
	return ch - '0';
}

double parseDouble(const String& str) {
	double result = 0;
	int i = 0;
	
	bool negative = false;
	if (str[i] == '-') {
		negative = true;
		i++;
	}

	for (i; i < str.getSize() && str[i] != '.'; i++) {
		int digit = parseDigit(str[i]);
		result *= 10;
		result += digit;
	}
	// num has decimal point
	if (i != str.getSize()) {
		i++;
		// no digits after decimal point
		if (i >= str.getSize())
			throw kInvalidNumMsg;

		int depth = 10;
		for (i; i < str.getSize(); i++) {
			double digit = parseDigit(str[i]);
			result += digit / depth;
			depth *= 10;
		}
	}

	return negative ? -result : result;
}

double calcDistance(double x1, double y1, double x2, double y2) {
	double xDiff = x1 - x2;
	double yDiff = y1 - y2;
	return sqrt(xDiff * xDiff + yDiff * yDiff);
}