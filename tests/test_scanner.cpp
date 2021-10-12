#include "../objscanner.hpp"
#include <cassert>

using namespace objimport;

int main(int argc, char **argv) {
	const char *source = "  10 / -20.3 #hello \n another line \n v +10 20 30 ";
	const std::vector<TokenType> types{
		T_NUMBER, T_SLASH,	T_NUMBER, T_IDENTIFIER, T_IDENTIFIER,
		T_V,	  T_NUMBER, T_NUMBER, T_NUMBER,		T_EOF,
	};

	OBJScanner scanner{source};
	auto tokens = scanner.scan_all();
	assert(tokens.size() == types.size());

	for (int i = 0; i < tokens.size(); i++) {
		assert(tokens[i].type == types[i]);
	}
}