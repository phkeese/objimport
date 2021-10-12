#include "objdata.hpp"

namespace objimport {

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
