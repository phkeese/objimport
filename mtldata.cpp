#include "mtldata.hpp"

namespace objimport {

MTLData::MTLData() {
	// Add default white material
	add_material("default", Material{"default"});
}

index MTLData::add_material(std::string name, Material m) {
	materials.push_back(m);
	index i = materials.size() - 1;
	material_indices[name] = i;
	return i;
}

Material MTLData::operator[](std::string name) {
	return materials.at(material_indices.at(name));
}

Material MTLData::operator[](index i) { return materials.at(i); }

} // namespace objimport
