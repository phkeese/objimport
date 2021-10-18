#include "mtlparser.hpp"

using namespace objimport;

MTLParser::MTLParser(std::istream &file)
	: Parser{file}, _current_material{"default"} {}

MTLData MTLParser::parse() {
	MTLData data{};

	while (!_is_at_end()) {
		_parse_next(data);
	}

	return data;
}

void MTLParser::_parse_next(MTLData &data) {
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
	MTLKeyword keyword = _check_key(identifier);
	switch (keyword) {
	case K_MTL_ERROR:
		throw _error("unexpected identifier '" + identifier + "'");
		break;
	case K_MTL_D:
		_set_transparency(_parse_float());
		break;
	case K_MTL_NEWMTL:
		_new_material(data);
		break;
	default:
		// Ignore valid but unimplemented keywords
		break;
	}

	_skip_line();
}

void MTLParser::_new_material(MTLData &data) {
	data.set_material(_current_material.name, _current_material);
	std::string name = _parse_identifier();
	_current_material = Material{name};
	data.set_material(name, _current_material);
}

MTLKeyword MTLParser::_check_key(std::string s) {
	static std::map<std::string, MTLKeyword> known_keywords{
		{"d", K_MTL_D},			  //
		{"illum", K_MTL_ILLUM},	  //
		{"Ka", K_MTL_KA},		  //
		{"Ke", K_MTL_KE},		  //
		{"Kd", K_MTL_KD},		  //
		{"Ks", K_MTL_KS},		  //
		{"newmtl", K_MTL_NEWMTL}, //
		{"Ni", K_MTL_NI},		  //
		{"Ns", K_MTL_NS},		  //
		{"Tr", K_MTL_TR},		  //
	};

	if (known_keywords.count(s)) {
		return known_keywords[s];
	} else {
		return K_MTL_ERROR;
	}
}