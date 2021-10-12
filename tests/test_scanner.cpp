#include "../objscanner.hpp"
#include <cassert>

using namespace objimport;

// TODO: As OBJ is completely line-oriented, we have no benefit in parsing the
// file as a whole. We could save memory by simply scanning a single line at
// once. Scanner should be easy to rewrite to that.

int main(int argc, char **argv) {
	const char *source = "  10 / -20.3 name another v";
	const std::vector<TokenType> types{
		T_NUMBER, T_SLASH, T_NUMBER, T_IDENTIFIER, T_IDENTIFIER, T_V, T_END,
	};

	OBJScanner scanner{source};
	auto tokens = scanner.scan_all();
	assert(tokens.size() == types.size());

	for (int i = 0; i < tokens.size(); i++) {
		assert(tokens[i].type == types[i]);
	}
}