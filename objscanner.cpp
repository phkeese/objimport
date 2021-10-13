#include "objscanner.hpp"
#include <ctype.h>
#include <map>

namespace objimport {

Token OBJScanner::next() {
	_skip_whitespace();

	int c = _advance();
	switch (c) {
		// Separator for vertex/texture/normal
	case '/':
		return _make_token(T_SLASH);
		// Numbers can start with a sign
	case '+':
	case '-':
		return _number();
	case '\n':
		_line++;
		return _make_token(T_NEWLINE);
	// Comments and empty lines should be skipped
	case EOF:
	case '#':
		_skip_line();
		return _make_token(T_NEWLINE);

	default:
		// Multi-character tokens
		if (isalpha(c)) {
			return _identifier();
		} else if (isnumber(c)) {
			return _number();
		} else {
			throw ScanningError{"unrecognized character", _end - _source};
		}
	}
}

Token OBJScanner::_make_token(TokenType type) {
	Token t{type, _start, _end - _start, _line};
	_start = _end;
	return t;
}

void OBJScanner::_skip_whitespace() {
	while (isspace(_peek()) && _peek() != '\n') {
		_advance();
	}
	_start = _end;
}

void OBJScanner::_skip_line() {
	while (_peek() != '\n') {
		_advance();
	}
	// clear newline
	_advance();

	_start = _end;
}

int OBJScanner::_advance() {
	if (!is_at_end()) {
		return *_end++;
	} else {
		return EOF;
	}
}

Token OBJScanner::_number() {
	while (isdigit(_peek())) {
		_advance();
	}

	if (_peek() == '.') {
		_advance();
		while (isdigit(_peek())) {
			_advance();
		}
	}

	return _make_token(T_NUMBER);
}

Token OBJScanner::_identifier() {
	// Scan to end of identifier
	while (isalnum(_peek())) {
		_advance();
	}

	// Match against known identifier types
	std::map<std::string, TokenType> commands{
		{"v", T_V},
	};

	std::string command(_start, _end - _start);
	if (commands.count(command)) {
		return _make_token(commands[command]);
	} else {
		return _make_token(T_IDENTIFIER);
	}
}

} // namespace objimport