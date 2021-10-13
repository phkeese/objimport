#pragma once

#include <algorithm>
#include <string>

namespace objimport {

inline std::string strip(std::string s) {
	std::string copy{s};
	copy.erase(remove_if(copy.begin(), copy.end(), isspace), copy.end());
	return copy;
}

} // namespace objimport
