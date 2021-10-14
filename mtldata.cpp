#include "mtldata.hpp"

namespace objimport {

MTLData::MTLData() : materials{} { // Add default white material
	add_material("default", Material{});
}

index MTLData::add_material(std::string name, Material m) {
	materials[name] = m;
	return materials.size() - 1;
}

} // namespace objimport
