#pragma once

#include "../utils/string.h"
#include "../utils/vector.hpp"

class Attribute {
	String key_;
	String value_;

public:
	Attribute() { }

	Attribute(const String& key, const String& value)
		: key_(key), value_(value)
	{ }

	Attribute(const String& str) {
		Vector<String> tokens = str.split('=');
		if (tokens.getSize() != 2)
			throw "Invalid attribute format!";

		key_ = tokens[0];
		value_ = tokens[1];
		if (value_.getSize() >= 2 && value_[0] == '"' && value_[value_.getSize() - 1] == '"')
			value_ = value_.substring(1, tokens[1].getSize() - 1);
	}

	const String& getKey() const {
		return key_;
	}
	const String& getValue() const {
		return value_;
	}

	template <class T>
	static void out(std::ostream& o, const String& key, const T& value) {
		o << key << "=\"" << value << '"';
	}
};
