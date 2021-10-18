#pragma once

#include "objdata.hpp"
#include "parser.hpp"
#include <istream>
#include <stdexcept>

namespace objimport {

enum Keyword {
	K_ERROR,
	K_F,
	K_L,
	K_MTLLIB,
	K_O,
	K_P,
	K_USEMTL,
	K_V,
	K_VN,
	K_VP,
	K_VT,
	K_S,
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

	Keyword _check_key(std::string s);
};

} // namespace objimport
