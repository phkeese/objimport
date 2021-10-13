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
	: _file{file}, _data{}, _last{}, _line{1} {}

OBJData OBJReader::parse() {
	_data = OBJData{};

	while (!_is_at_end()) {
		_parse_next();
	}

	return _data;
}

void OBJReader::_parse_next() {
	int c = _advance();

	switch (c) {
		// No further parsing at end of file
	case EOF:
		return;
	// Skip empty lines
	case '\n':
		_line++;
		return;
	case '#':
		break;

	// v or vn
	case 'v':
		if (_match('n')) {
			_data.add_normal(_parse_vector());
		} else {
			_data.add_vertex(_parse_vector());
		}
		break;
	default:
		throw _error("unexpected character");
		break;
	}

	_skip_line();
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

void OBJReader::_skip_line() {
	while (_peek() != '\n') {
		_advance();
	}
	_consume('\n', "expect new line");
	_line++;
}

void OBJReader::_skip_whitespace() {
	while (_peek() != '\n' && isspace(_peek())) {
		_advance();
	}
}

int OBJReader::_advance() {
	_last = _file.get();
	return _last;
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
	return ParsingError{message, _line, _previous()};
}

} // namespace objimport
