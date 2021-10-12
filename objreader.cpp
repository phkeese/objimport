#include "objreader.hpp"
#include "helper_functions.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

namespace objimport {

OBJReader::OBJReader() : _scanner{}, _data{} {}

OBJData OBJReader::parse(std::string filepath) {
	_data = OBJData{};
	std::ifstream file(filepath);

	if (!file) {
		throw std::runtime_error("cannot open file");
	}

	return {};
}

} // namespace objimport
