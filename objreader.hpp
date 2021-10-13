#pragma once

#include "objdata.hpp"
#include "objscanner.hpp"
#include <istream>
#include <stdexcept>

namespace objimport {

class ParsingError : public std::runtime_error {
  public:
	ParsingError(std::string what, Token where)
		: std::runtime_error{what}, _where{where} {}
	inline const Token where() const { return _where; }

  private:
	Token _where;
};

class OBJReader {
  public:
	OBJReader(OBJScanner &scanner);
	OBJData parse();

  private:
	// Parse the next line
	void _parse_next();

	// Parse a vector of three floats
	Vector3 _parse_vector();
	float _parse_number();

	inline Token _previous() const { return _last; }
	inline Token _peek() const { return _next; }
	// Read the next token
	Token _advance();
	// Compare the next token, advance if matching
	bool _match(TokenType type);
	// Consume the next token, throw error if not matching
	void _consume(TokenType type, std::string message);
	ParsingError _error(std::string message);

	OBJScanner &_scanner;
	OBJData _data;
	Token _last, _next;
};

} // namespace objimport
