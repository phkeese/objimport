#pragma once

#include "objdata.hpp"
#include "objscanner.hpp"
#include <istream>

namespace objimport {

class OBJReader {
  public:
	OBJReader();

	OBJData parse(std::string filepath);

  private:
	void _parse_v();

	OBJScanner *_scanner;
	OBJData _data;
};

} // namespace objimport
