#include "objreader.hpp"
#include "helper_functions.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

namespace objimport {

OBJReader::OBJReader(OBJScanner &scanner)
	: _scanner{scanner}, _data{}, _last{}, _next{} {
	// Load meaningful data into _next
	_advance();
}

OBJData OBJReader::parse() {
	_data = OBJData{};

	while (!_scanner.is_at_end()) {
		_parse_next();
	}

	return _data;
}

void OBJReader::_parse_next() {
	Token t = _advance();
	switch (t.type) {
	// Ignore empty lines
	case T_NEWLINE:
		break;
	case T_V:
		_data.add_vertex(_parse_vector());
		_consume(T_NEWLINE, "expect newline");
		break;

	default:
		throw _error("unexpected token");
		break;
	}
}

Vector3 OBJReader::_parse_vector() {
	float x = _parse_number();
	float y = _parse_number();
	float z = _parse_number();
	return {x, y, z};
}

float OBJReader::_parse_number() {
	_consume(T_NUMBER, "expect number");
	std::string lexeme(_previous().begin, _previous().length);
	return std::stof(lexeme);
}

Token OBJReader::_advance() {
	_last = _next;
	_next = _scanner.next();
	return _last;
}

bool OBJReader::_match(TokenType type) {
	if (_peek().type == type) {
		_advance();
		return true;
	} else {
		return false;
	}
}

void OBJReader::_consume(TokenType type, std::string message) {
	if (!_match(type)) {
		throw _error(message);
	}
}

ParsingError OBJReader::_error(std::string message) {
	return ParsingError{message, _previous()};
}

} // namespace objimport
