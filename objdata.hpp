#pragma once

#include "mtldata.hpp"
#include "objdatatypes.hpp"
#include <vector>
namespace objimport {

// Stores indices to position, normal and texture coordinates of a vertex in OBJ
// Indices start at 0
struct Vertex {
	Vertex(index position, index texture, index normal)
		: position(position), texture(texture), normal(normal) {}

	index position;
	index texture;
	index normal;
};

// Stores the vertices of a face
struct Face {
	Face(std::vector<Vertex> vertices) : vertices{vertices} {}
	std::vector<Vertex> vertices;
};

// Stores the entire contents of a file
struct OBJData {
	OBJData();

	index add_vertex(Vector3 v);
	index add_normal(Vector3 v);
	index add_face(Face f);

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Face> faces;

	MTLData material_data;
};

} // namespace objimport
