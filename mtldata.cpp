#include "mtldata.hpp"

namespace objimport {

MTLData::MTLData() {
	// Add default white material
	set_material("default", Material{"default"});
}

index MTLData::set_material(std::string name, Material m) {
	index i = 0;
	auto where = material_indices.find(name);
	if (where == material_indices.end()) {
		materials.push_back(Material{name});
		i = materials.size() - 1;
		material_indices[name] = i;
	} else {
		i = where->second;
	}

	materials[i] = m;
	return i;
}

Material MTLData::operator[](std::string name) {
	return materials.at(material_indices.at(name));
}

Material MTLData::operator[](index i) { return materials.at(i); }

} // namespace objimport
