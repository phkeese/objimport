#pragma once

#include <vector>

namespace objimport {

using index = unsigned int;

struct Vector3 {
	float x, y, z;
};

// Stores indices to position, normal and texture coordinates of a vertex in OBJ
// Indices start at 1 to reflect file
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
	OBJData() : vertices{}, normals{}, faces{} {}

	index add_vertex(Vector3 v);
	index add_normal(Vector3 v);
	index add_face(Face v);

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Face> faces;
};

} // namespace objimport
