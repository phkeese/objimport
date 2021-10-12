# Exports an OBJData to VBOs for...
# 	glDrawArrays(GL_TRIANGLES,...) -> arrays.tris.bin
#	glDrawElements(GL_TRIANGLES) -> elements.tris.bin
# 		with the indices 		 -> elements.bin
# 
# Vertex data has the following format:
# 	position	x,y,z	IEEE-754, little endian
#	normal		x,y,z	IEEE-754, little endian

from objreader import OBJData

class OBJArraysExporter:
	def __init__(self, directory: str, data: OBJData) -> None:
		self.directory = directory
		self.data = data
		self.arrays_tris = []

	def generate_arrays_tris(self) -> list[float]:
		for face in self.data.faces:
			for v in face.vertices[:3]:
				self.add_vertex(v.vertex)
				self.add_normal(v.normal)
		return self.arrays_tris
	
	def add_vertex(self, index: int) -> None:
		vector = self.data.vertices[index - 1].position
		for value in vector:
			self.add_float(value)
	
	def add_normal(self, index: int) -> None:
		if index >= 1:
			vector = self.data.normals[index - 1]
		else:
			vector = [0,0,0]
		
		for value in vector:
			self.add_float(value)
			
	
	def add_float(self, value: float) -> None:
		self.arrays_tris.append(value)

