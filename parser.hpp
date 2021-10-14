#pragma once
#include "objdatatypes.hpp"
#include <istream>
#include <stdexcept>
#include <string>

/**
 * General line-based parser class
 */

namespace objimport {

class ParsingError : public std::runtime_error {
  public:
	ParsingError(std::string what, long line, int character)
		: std::runtime_error{what}, _line{line}, _character{character} {}
	inline const long line() const { return _line; }
	inline const int character() const { return _character; }

  private:
	long _line;
	int _character;
};

class Parser {
  public:
	Parser(std::istream &file);

  protected:
	// Parse a vector of three floats
	Vector3 _parse_vector();
	float _parse_float();
	int _parse_int();
	// Parse the next string of non-space characters
	std::string _parse_identifier();

	// Skip to next \n and consume it
	void _skip_line();
	// Skip to next \n but do not consume it
	void _skip_whitespace();
	inline int _previous() const { return _last; }
	inline int _peek() const { return _file.peek(); }
	inline int _is_at_end() const { return _file.eof(); }
	// Read the next character
	int _advance();
	// Compare the next character, advance if matching
	bool _match(int c);
	// Compare the next character
	bool _check(int c);
	// Consume the next character, throw error if not matching
	void _consume(int c, std::string message);
	// Generate a ParsingError with my current state
	ParsingError _error(std::string message);

	std::istream &_file;
	int _last;
	long _line;
};

} // namespace objimport
