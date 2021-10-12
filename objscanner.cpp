#include "objscanner.hpp"
#include <ctype.h>
#include <map>

namespace objimport {

std::vector<Token> OBJScanner::scan_all() {
	std::vector<Token> tokens{};

	TokenType last = T_ERROR;
	do {
		Token t = _scan_token();
		last = t.type;
		tokens.push_back(t);
	} while (last != T_END);

	return tokens;
}

Token OBJScanner::_scan_token() {
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
	// Comments and empty lines should be skipped
	case EOF:
	case '#':
		_skip_to_end();
		return _make_token(T_END);

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
	Token t{type, _start, _end - _start};
	_start = _end;
	return t;
}

void OBJScanner::_skip_whitespace() {
	while (isspace(_peek())) {
		_advance();
	}
	_start = _end;
}

void OBJScanner::_skip_to_end() {
	while (!is_at_end()) {
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