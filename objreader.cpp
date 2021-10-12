#include "objreader.hpp"
#include "helper_functions.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

namespace objimport {

OBJReader::OBJReader() : _data{} {}

OBJData OBJReader::parse(std::string filepath) {
	_data = OBJData{};
	std::ifstream file(filepath);

	if (!file) {
		throw std::runtime_error("cannot open file");
	}

	do {
		std::string line;
		std::getline(file, line);
		_parse_line(line);
	} while (file.good());

	return {};
}

void OBJReader::_parse_line(std::string line) {
	if (line.empty())
		return;

	// Function to handle parsing of a specific element like 'v'
	// Takes the remainder of the line as argument
	using handler = std::function<void(std::string)>;

	std::cout << line << "\n";

	// Map of handler methods
	std::map<std::string, handler> lut{
		{"v", [this](std::string args) { this->_parse_vertex(args); }},
	};

	int separator = line.find(' ');
	std::string head = strip(line.substr(0, separator));
	std::string tail = strip(line.substr(separator));

	if (lut.count(head)) {
		lut[head](tail);
	} else {
		std::cout << "cannot parse '" << head << "'\n";
	}
}

void OBJReader::_parse_vertex(std::string args) {}

} // namespace objimport
