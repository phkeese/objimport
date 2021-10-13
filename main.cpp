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

	std::stringstream ss{};
	ss << file.rdbuf();
	OBJScanner scanner{ss.str().c_str()};
	OBJReader reader{scanner};

	try {
		auto data = reader.parse();
	} catch (ParsingError e) {
		std::string lexeme(e.where().begin, e.where().length);
		std::cerr << "error:" << e.where().line << ":" << e.what() << " near '"
				  << lexeme << "' (token:" << e.where().type << ")\n";
	}
}