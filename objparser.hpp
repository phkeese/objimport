#pragma once

#include "objdata.hpp"
#include "parser.hpp"
#include <istream>
#include <stdexcept>

namespace objimport {

enum OBJKeyword {
	K_OBJ_ERROR,
	K_OBJ_F,
	K_OBJ_L,
	K_OBJ_MTLLIB,
	K_OBJ_O,
	K_OBJ_P,
	K_OBJ_USEMTL,
	K_OBJ_V,
	K_OBJ_VN,
	K_OBJ_VP,
	K_OBJ_VT,
	K_OBJ_S,
};

class OBJParser : public Parser {
  public:
	OBJParser(std::istream &file);
	OBJData parse();

  private:
	// Parse the next line
	void _parse_next(OBJData &data);

	// Parse all vertices of a face
	Face _parse_face();
	// Parse a single vertex of a face in the v/t/n format
	Vertex _parse_face_vertex();

	OBJKeyword _check_key(std::string s);
};

} // namespace objimport
