#pragma once

#include "objdata.hpp"
#include <istream>

namespace objimport {

class OBJReader {
  public:
	OBJReader();

	OBJData parse(std::string filepath);

  private:
	void _parse_line(std::string line);
	void _parse_vertex(std::string args);

	OBJData _data;
};

} // namespace objimport
