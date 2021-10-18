#include "objreader.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

using namespace objimport;

OBJReader::OBJReader(std::istream &file) : Parser{file} {}

OBJData OBJReader::parse() {
	OBJData data = OBJData{};

	while (!_is_at_end()) {
		_parse_next(data);
	}

	return data;
}

void OBJReader::_parse_next(OBJData &data) {
	int c = _peek();

	// Handle comments and newlines separately from keywords
	switch (c) {
		// No further parsing at end of file
	case EOF:
		return;
	// Skip empty lines and comments
	case '\r':
	case '\n':
	case '#':
		_skip_line();
		return;
	}

	// Anything else has to be a keyword (or an error!)
	std::string identifier = _parse_identifier();
	Keyword keyword = _check_key(identifier);
	switch (keyword) {
	case K_ERROR:
		throw _error("unexpected identifier '" + identifier + "'");
		break;
	case K_F:
		data.add_face(_parse_face());
		break;
	case K_V:
		data.add_vertex(_parse_vector());
		break;
	case K_VN:
		data.add_normal(_parse_vector());
		break;
	default:
		// Ignore valid but unimplemented keywords
		break;
	}

	_skip_line();
}

Face OBJReader::_parse_face() {
	std::vector<Vertex> vertices;

	// parse until end of line, handle CRLF
	while (!_check('\n') && !_check('\r')) {
		_skip_whitespace();
		vertices.push_back(_parse_face_vertex());
	}

	return Face{vertices};
}

Vertex OBJReader::_parse_face_vertex() {
	index vertex = 0, texture = 0, normal = 0;

	vertex = _parse_int();

	// This is such a mess because any of the following are valid
	// v v/t v/t/n v//n
	if (_match('/')) {
		// Texture or normal
		if (_match('/')) {
			// Only normal
			texture = 0;
			normal = _parse_int();
		} else {
			// Texture
			texture = _parse_int();
			if (_match('/')) {
				// Also normal
				normal = _parse_int();
			}
		}
	}

	return {vertex, texture, normal};
}

Keyword OBJReader::_check_key(std::string s) {
	static std::map<std::string, Keyword> known_keywords{
		{"f", K_F},			  //
		{"l", K_L},			  //
		{"mtllib", K_MTLLIB}, //
		{"o", K_O},			  //
		{"p", K_P},			  //
		{"usemtl", K_USEMTL}, //
		{"v", K_V},			  //
		{"vn", K_VN},		  //
		{"vp", K_VP},		  //
		{"vt", K_VT},		  //
		{"s", K_S},			  //
	};

	if (known_keywords.count(s)) {
		return known_keywords[s];
	} else {
		return K_ERROR;
	}
}
