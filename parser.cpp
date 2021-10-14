#include "parser.hpp"

using namespace objimport;

Parser::Parser(std::istream &file) : _file{file}, _last{}, _line{1} {}

Vector3 Parser::_parse_vector() {
	float x = _parse_float();
	float y = _parse_float();
	float z = _parse_float();
	return {x, y, z};
}

float Parser::_parse_float() {
	float value;
	_file >> value;
	return value;
}

int Parser::_parse_int() {
	int value;
	if (!(_file >> value)) {
		throw _error("expect int");
	}
	return value;
}

std::string Parser::_parse_identifier() {
	std::string identifier;
	_file >> identifier;
	return identifier;
}

void Parser::_skip_line() {
	while (_peek() != '\n') {
		_advance();
	}
	_consume('\n', "expect new line");
	_line++;
}

void Parser::_skip_whitespace() {
	while (_peek() != '\n' && isspace(_peek())) {
		_advance();
	}
}

int Parser::_advance() {
	_last = _file.get();
	return _last;
}

bool Parser::_match(int c) {
	if (_check(c)) {
		_advance();
		return true;
	} else {
		return false;
	}
}

bool Parser::_check(int c) { return _peek() == c; }

void Parser::_consume(int c, std::string message) {
	if (!_match(c)) {
		throw _error(message);
	}
}

ParsingError Parser::_error(std::string message) {
	return ParsingError{message, _line, _peek()};
}
