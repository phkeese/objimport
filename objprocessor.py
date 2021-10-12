from objreader import *

class OBJProcessor:
	def __init__(self, data: OBJData) -> None:
		self.data = data
	
	# test wether a vertex is assigned to multiple faces with different normals
	def test_multiple_normals(self) -> bool:
		vertex_normals = {}
		has_mismatch = False
		for face in self.data.faces:
			for vertex in face.vertices:
				v,n = vertex.vertex,vertex.normal
				if v in vertex_normals and vertex_normals[v] != n:
					has_mismatch = True
					#print(f"normal mismatch: v:{v}, n1:{vertex_normals[v]} n2:{n}")
				else:
					vertex_normals[v] = n
		return has_mismatch

	def largest_face_vertex_count(self) -> int:
		largest = 0
		for face in self.data.faces:
			largest = max(largest, len(face.vertices))
		return largest
