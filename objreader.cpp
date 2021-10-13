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
	// Token t = _advance();
	// switch (t.type) {
	// // Ignore empty lines
	// case T_NEWLINE:
	// 	break;
	// case T_V:
	// 	_data.add_vertex(_parse_vector());
	// 	_consume(T_NEWLINE, "expect newline");
	// 	break;

	// default:
	// 	throw _error("unexpected token");
	// 	break;
	// }
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
