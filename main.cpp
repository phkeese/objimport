#include "objreader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace objimport;

int main(int argc, char **argv) {
	// if (argc < 2) {
	// 	std::cerr << "usage: " << argv[0] << " <file>\n";
	// 	exit(EXIT_FAILURE);
	// }

	std::string filename{"../model.obj" /*argv[1]*/};
	std::cout << "read file '" << filename << "'\n";

	std::ifstream file{filename};
	if (!file) {
		std::cerr << "cannot open file\n";
		exit(EXIT_FAILURE);
	}

	OBJReader reader{file};

	try {
		auto data = reader.parse();
		std::cout << "parsing successfull\n";
	} catch (ParsingError e) {
		std::cout << "parsing error\n";
		std::cout << "error:" << e.where() << ":" << e.what() << " near '"
				  << static_cast<char>(e.character()) << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
}