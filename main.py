import objreader
import objprocessor
import sys
import progressbar
import pickle
import objexporter
from array import array

def main():
	filename = sys.argv[1]
	if filename.endswith(".obj"):
		reader = objreader.OBJReader()
		data = reader.parse(filename)
		with open(filename + ".pickle", "wb") as file:
			pickle.dump(data, file)
	elif filename.endswith(".pickle"):
		with open(filename, "rb") as file:
			data = pickle.load(file)
	else:
		print("unsupported file")
		exit(1)

	bar = progressbar.ProgressBar("Tests", 2, 80)
	bar.set_value(0)
	processor = objprocessor.OBJProcessor(data)
	multiple_normals = processor.test_multiple_normals()
	bar.increment()
	largest_face = processor.largest_face_vertex_count()
	bar.increment()
	bar.finish()
	
	print("Multiple normals per vertex" if multiple_normals else "No multiple normals")
	print(f"largest face: {largest_face}")

	exporter = objexporter.OBJArraysExporter("",data)
	triangle_soup = array("f", exporter.generate_arrays_tris())

	bar = progressbar.ProgressBar("Cooking Soup", 1, 80)
	with open("triangle_soup.bin", "wb") as soup_file:
		triangle_soup.tofile(soup_file)
	bar.finish()


if __name__ == "__main__":
	main()