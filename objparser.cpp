#include "objparser.hpp"
#include "mtlparser.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

using namespace objimport;

OBJParser::OBJParser(std::string directory, std::istream &file)
	: _directory{directory}, Parser{file} {}

OBJData OBJParser::parse() {
	OBJData data = OBJData{};

	while (!_is_at_end()) {
		_parse_next(data);
	}

	return data;
}

void OBJParser::_parse_next(OBJData &data) {
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
	OBJKeyword keyword = _check_key(identifier);
	switch (keyword) {
	case K_OBJ_ERROR:
		throw _error("unexpected identifier '" + identifier + "'");
		break;
	case K_OBJ_F:
		data.add_face(_parse_face());
		break;
	case K_OBJ_V:
		data.add_vertex(_parse_vector());
		break;
	case K_OBJ_VN:
		data.add_normal(_parse_vector());
		break;
	case K_OBJ_MTLLIB:
		data.material_data = _parse_mltlib();
		break;
	default:
		// Ignore valid but unimplemented keywords
		break;
	}

	_skip_line();
}

Face OBJParser::_parse_face() {
	std::vector<Vertex> vertices;

	// parse until end of line, handle CRLF
	while (!_check('\n') && !_check('\r')) {
		_skip_whitespace();
		vertices.push_back(_parse_face_vertex());
	}

	return Face{vertices};
}

Vertex OBJParser::_parse_face_vertex() {
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

MTLData OBJParser::_parse_mltlib() {
	std::string filename = _directory + "/" + _parse_identifier();
	std::ifstream file{filename};
	if (!file) {
		throw _error("cannot open material file '" + filename + "'");
	}

	MTLParser parser{file};
	return parser.parse();
}

OBJKeyword OBJParser::_check_key(std::string s) {
	static std::map<std::string, OBJKeyword> known_keywords{
		{"f", K_OBJ_F},			  //
		{"l", K_OBJ_L},			  //
		{"mtllib", K_OBJ_MTLLIB}, //
		{"o", K_OBJ_O},			  //
		{"p", K_OBJ_P},			  //
		{"usemtl", K_OBJ_USEMTL}, //
		{"v", K_OBJ_V},			  //
		{"vn", K_OBJ_VN},		  //
		{"vp", K_OBJ_VP},		  //
		{"vt", K_OBJ_VT},		  //
		{"s", K_OBJ_S},			  //
	};

	if (known_keywords.count(s)) {
		return known_keywords[s];
	} else {
		return K_OBJ_ERROR;
	}
}
