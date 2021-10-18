#pragma once
#include "mtldata.hpp"
#include "parser.hpp"

/**
 * Material Template Libary Parser
 */

namespace objimport {

enum MTLKeyword {
	K_MTL_ERROR,
	K_MTL_D,
	K_MTL_ILLUM,
	K_MTL_KA,
	K_MTL_KD,
	K_MTL_KE,
	K_MTL_KS,
	K_MTL_NEWMTL,
	K_MTL_NI,
	K_MTL_NS,
	K_MTL_TR,
};

class MTLParser : public Parser {
  public:
	MTLParser(std::istream &file);
	MTLData parse();

  private:
	void _parse_next(MTLData &data);

	void _new_material(MTLData &data);

	inline void _set_transparency(float value) {
		_current_material.transparency = value;
	}

	MTLKeyword _check_key(std::string s);

	Material _current_material;
};

} // namespace objimport