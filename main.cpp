#include "objreader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace objimport;

int main(int argc, char **argv) {
	std::string filename;

	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <file>\n";
		std::cout << "parsing default file...\n";
		filename = "../model.obj";
	} else {
		filename = argv[1];
	}

	std::ifstream file{filename};
	if (!file) {
		std::cerr << "cannot open file\n";
		exit(EXIT_FAILURE);
	}

	OBJReader reader{file};

	try {
		auto data = reader.parse();
		std::cout << "parsing successful\n";
	} catch (ParsingError e) {
		std::cout << "parsing error\n";
		std::cout << "error:" << e.where() << ":" << e.what() << " near '"
				  << static_cast<char>(e.character()) << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
}
