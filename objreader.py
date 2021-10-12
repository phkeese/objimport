from os import pipe
from typing import Set
import progressbar

Vector = list[float]

class Vertex:
	def __init__(self, position: list[float]) -> None:
		self.faces = []
		self.position = position
		self.normal = [0.0] * 3
	
	def add_face(self, face) -> None:
		self.faces.append(face)


class FaceVertex:
	def __init__(self, vertex: int, texture: int, normal: int) -> None:
		self.vertex = vertex
		self.texture = texture
		self.normal = normal


class Face:
	def __init__(self, vertices: list[FaceVertex]) -> None:
		self.vertices = vertices


class LineVertex:
	def __init__(self, vertex: int, texture: int) -> None:
		self.vertex = vertex
		self.texture = texture


class Line:
	def __init__(self, vertices: list[LineVertex]) -> None:
		self.vertices = vertices


class OBJData:
	def __init__(self) -> None:
		self.vertices = []
		self.normals = []
		self.faces = []
		self.lines = []
	
	def add_vertex(self, v: Vertex) -> int:
		self.vertices.append(v)
		return len(self.vertices) - 1
	
	def add_face(self, f: Face) -> int:
		self.faces.append(f)
		return len(self.faces) - 1
	
	def add_normal(self, normal: list[float]) -> int:
		self.normals.append(normal)
		return len(self.normals) - 1
	
	def add_line(self, line: Line) -> int:
		self.lines.append(line)
		return len(self.lines) - 1


class OBJReader:
	def __init__(self) -> None:
		pass
	
	def parse(self, filename) -> OBJData:
		data = OBJData()
		with open(filename, "r") as file:
			lines = file.readlines()
			bar = progressbar.ProgressBar("Parsing", len(lines), 80)
			for i in range(0, len(lines)):
				line = lines[i]
				if i % 10000 == 0:
					bar.set_value(i)
				try:
					self.parse_line(line, data)
				except Exception as e:
					print(f"parse error:{e}")
			bar.finish()
		return data

	def parse_line(self, line: str, data: OBJData) -> None:
		head, _, tail = [x.strip() for x in line.partition(" ")]

		routing = {
			"v" : lambda: self.add_vertex(tail, data),
			"f" : lambda: self.add_face(tail, data),
			"vn" : lambda: self.add_normal(tail, data),
			"l" : lambda: self.add_line(tail, data),
			"#" : lambda: None,
		}

		if head in routing:
			routing[head]()
		else:
			pass
			#print(f"cannot parse '{head}' yet")
	
	def add_vertex(self, tail: str, data: OBJData) -> None:
		x,y,z = [float(v) for v in tail.split(" ")]
		data.add_vertex(Vertex([x,y,z]))

	def add_normal(self, tail: str, data: OBJData) -> None:
		x,y,z = [float(v) for v in tail.split(" ")]
		data.add_normal([x,y,z])

	def add_face(self, tail: str, data: OBJData) -> None:
		vertices = [OBJReader.parse_face_vertex(part) for part in tail.split(" ")]
		data.add_face(Face(vertices))
	
	def parse_face_vertex(part: str) -> FaceVertex:
		# parse v/t/n part of face
		v,_,tn = part.partition("/")
		t,_,n = tn.partition("/")
		return FaceVertex(int(v or 0), int(t or 0), int(n or 0))
	
	def add_line(self, tail: str, data: OBJData) -> None:
		vertices = [OBJReader.parse_line_vertex(part) for part in tail.split(" ")]
		data.add_line(Line(vertices))
	
	def parse_line_vertex(part: str) -> FaceVertex:
		# parse v/t part of line
		v,_,t = part.partition("/")
		return LineVertex(int(v or 0), int(t or 0))
	


