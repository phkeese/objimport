#pragma once
#include "mtldata.hpp"
#include "parser.hpp"

/**
 * Material Template Libary Parser
 */

namespace objimport {

class MTLParser : public Parser {
  public:
	MTLParser(std::istream &file);
	MTLData parse();

  private:
	void _parse_next(MTLData &data);

	Material _current_material;
};

} // namespace objimport