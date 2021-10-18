#include "mtldata.hpp"

namespace objimport {

MTLData::MTLData() {
	// Add pink error material
	set_material("error", Material{"error", {1, 1, 1}, {1, 0, 1}});
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

index MTLData::get_index_of(std::string name) {
	return material_indices.at(name);
}

Material MTLData::operator[](std::string name) {
	return materials[get_index_of(name)];
}

Material MTLData::operator[](index i) { return materials.at(i); }

} // namespace objimport
