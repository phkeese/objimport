#pragma once

#include "objdata.hpp"
#include "objscanner.hpp"
#include <istream>
#include <stdexcept>

namespace objimport {

class ParsingError : public std::runtime_error {
  public:
	ParsingError(std::string what, long where)
		: std::runtime_error{what}, _where{where} {}
	inline const long where() const { return _where; }

  private:
	long _where;
};

class OBJReader {
  public:
	OBJReader(std::istream &file);
	OBJData parse();

  private:
	// Parse the next line
	void _parse_next();

	// Parse a vector of three floats
	Vector3 _parse_vector();
	float _parse_number();

	inline int _previous() const { return _last; }
	inline int _peek() const { return _file.peek(); }
	inline int _is_at_end() const { return _file.eof(); }
	// Read the next character
	int _advance();
	// Compare the next character, advance if matching
	bool _match(int c);
	// Consume the next character, throw error if not matching
	void _consume(int c, std::string message);
	ParsingError _error(std::string message);

	std::istream &_file;
	OBJData _data;
	int _last, _next;
};

} // namespace objimport
