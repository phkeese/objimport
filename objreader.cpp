#include "objreader.hpp"
#include "helper_functions.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

namespace objimport {

OBJReader::OBJReader(std::istream &file)
	: _file{file}, _data{}, _last{}, _next{} {
	// Load meaningful data into _next
	_advance();
}

OBJData OBJReader::parse() {
	_data = OBJData{};

	return _data;
}

void OBJReader::_parse_next() {
	int c = _advance();

	switch (c) {
	// Skip empty lines
	case '\n':
		return;
	case 'v':
		_data.add_vertex(_parse_vector());
		break;
	default:
		throw _error("unexpected character");
		break;
	}

	_skip_whitespace();
	_consume('\n', "expect new line");
}

Vector3 OBJReader::_parse_vector() {
	float x = _parse_number();
	float y = _parse_number();
	float z = _parse_number();
	return {x, y, z};
}

float OBJReader::_parse_number() {
	float value;
	if (!(_file >> value)) {
		throw _error("expect number");
	}
	return value;
}

void OBJReader::_skip_whitespace() {
	while (_peek() != '\n' && isspace(_peek())) {
		_advance();
	}
}

int OBJReader::_advance() {
	_last = _next;
	_next = _peek();
}

bool OBJReader::_match(int c) {
	if (_peek() == c) {
		_advance();
		return true;
	} else {
		return false;
	}
}

void OBJReader::_consume(int c, std::string message) {
	if (!_match(c)) {
		throw _error(message);
	}
}

ParsingError OBJReader::_error(std::string message) {
	return ParsingError{message, _previous()};
}

} // namespace objimport
