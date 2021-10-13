#pragma once

#include "objdata.hpp"
#include <istream>
#include <stdexcept>

namespace objimport {

class ParsingError : public std::runtime_error {
  public:
	ParsingError(std::string what, long where, int character)
		: std::runtime_error{what}, _where{where}, _character{character} {}
	inline const long where() const { return _where; }
	inline const int character() const { return _character; }

  private:
	long _where;
	int _character;
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
	float _parse_float();
	int _parse_int();
	Face _parse_face();
	Vertex _parse_face_vertex();

	void _skip_line();
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
	ParsingError _error(std::string message);

	std::istream &_file;
	OBJData _data;
	int _last;
	long _line;
};

} // namespace objimport
