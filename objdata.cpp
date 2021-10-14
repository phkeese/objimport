#include "objdata.hpp"

namespace objimport {

OBJData::OBJData() : vertices{}, normals{}, faces{} {
	// Add fallback data to shift indices and handle invalid indices
	add_vertex({0, 0, 0});
	add_normal({0, 1, 0});
}

index OBJData::add_vertex(Vector3 v) {
	vertices.push_back(v);
	return vertices.size() - 1;
}

index OBJData::add_normal(Vector3 v) {
	normals.push_back(v);
	return normals.size() - 1;
}

index OBJData::add_face(Face f) {
	faces.push_back(f);
	return faces.size() - 1;
}

} // namespace objimport
