#include "objscanner.hpp"
#include "ctype.h"

namespace objimport {

std::vector<Token> OBJScanner::scan_all() {}

Token OBJScanner::_scan_token() {
retry:
	_skip_whitespace();

	int c = _advance();
	switch (c) {
		// Single character tokens
	case EOF:
		return _make_token(T_ERROR);
	case '/':
		return _make_token(T_SLASH);
	case '+':
	case '-':
		return _number();
	case '#':
		_skip_line();
		goto retry;

	default:
		// Multi-character tokens
		if (isalpha(c)) {
			return _identifier();
		} else if (isnumber(c)) {
			return _number();
		} else {
				}
	}
}

Token OBJScanner::_make_token(TokenType type) {
	Token t{type, _start, _end - _start};
	_start = _end;
	return t;
}

void OBJScanner::_skip_whitespace() {
	while (isspace(_peek())) {
		_advance();
	}
}

void OBJScanner::_skip_line() {
	while (_peek() != '\n') {
		_advance();
	}
}

int OBJScanner::_advance() {
	if (!is_at_end()) {
		return *_end++;
	} else {
		return EOF;
	}
}

} // namespace objimport