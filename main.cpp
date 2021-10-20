#include "mtlparser.hpp"
#include "objparser.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace objimport;

// Extract a path from a given filename
std::string directory_of(std::string filename) {
	auto where = filename.find_last_of('/');
	return filename.substr(0, where);
}

int main(int argc, char **argv) {
	std::string filename;

	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <file>\n";
		filename = "../model.obj";
	} else {
		filename = argv[1];
	}

	std::cout << "parsing '" << filename << "'..." << std::endl;

	std::ifstream file{filename};

	if (!file) {
		std::cerr << "cannot open file\n";
		exit(EXIT_FAILURE);
	}

	OBJParser reader{directory_of(filename), file};

	try {
		auto data = reader.parse();
		std::cout << "parsing successful\n";
	} catch (ParsingError e) {
		std::cout << "parsing error\n";
		std::cout << "error:" << e.line() << ":" << e.what() << " near '"
				  << static_cast<char>(e.character()) << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
}
