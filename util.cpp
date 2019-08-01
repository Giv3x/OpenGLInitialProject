#include "util.h"


std::vector<std::string> split(const std::string& s, const char& d) {
	std::string text = "";
	std::vector<std::string> result;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == d) {
			if (text.size() == 0)
				continue;
			result.push_back(text);
			text = "";
			continue;
		}

		text += s[i];
	}

	if (text.size() != 0)	result.push_back(text);

	return result;
}