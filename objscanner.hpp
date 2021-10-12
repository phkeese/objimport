#pragma once
#include <stdexcept>
#include <string>
#include <vector>

/**
 * Scanner Class
 * Splits a stream of characters into a stream of tokens
 * Makes parsing easier by removing whitespaces and generalising tokens
 */

namespace objimport {

enum TokenType {
	T_ERROR,
	T_V,
	T_NUMBER,
	T_SLASH,
	T_IDENTIFIER,
	T_NEWLINE,
	T_EOF,
};

struct Token {
	Token(TokenType type, const char *begin, long length)
		: type(type), begin(begin), length(length) {}

	TokenType type;
	const char *begin;
	long length;
};

class ScanningError : public std::runtime_error {
  public:
	ScanningError(std::string what, long where)
		: std::runtime_error{what}, _where{where} {}
	inline const long where() const { return _where; }

  private:
	long _where;
};

class OBJScanner {
  public:
	OBJScanner(const char *source)
		: _source(source), _start(source), _end(source) {}
	std::vector<Token> scan_all();
	inline bool is_at_end() const { return *_end == '\0'; }

  private:
	Token _scan_token();
	Token _make_token(TokenType type);

	Token _number();
	Token _identifier();

	void _skip_whitespace();
	void _skip_line();
	inline int _peek() const { return is_at_end() ? EOF : *_end; }
	int _advance();

	const char *_source;
	const char *_start, *_end;
};

} // namespace objimport
