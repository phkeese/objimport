#include "mtlparser.hpp"
#include "objparser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace objimport;

int main(int argc, char **argv) {
	std::string filename;

	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <file>\n";
		filename = "../model.mtl";
	} else {
		filename = argv[1];
	}

	std::cout << "parsing '" << filename << "'..." << std::endl;

	std::ifstream file{filename};
	if (!file) {
		std::cerr << "cannot open file\n";
		exit(EXIT_FAILURE);
	}

	MTLParser reader{file};

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
