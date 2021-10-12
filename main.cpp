#include "objreader.hpp"
#include <iostream>

using namespace objimport;

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <file>\n";
		exit(EXIT_FAILURE);
	}

	std::string filename{argv[1]};
	std::cout << "read file '" << filename << "'\n";

	OBJReader reader{};
	auto data = reader.parse(filename);
}