// ****************************************************************************************************
// **************************************** SUPPLEMENTS_CPP__ *****************************************
// ****************************************************************************************************
#include "supplements.h"

#include <sstream>
#include <iomanip>


string substring(const string& str, size_t first, size_t last) {
	return str.substr(first, last - first);
}

string trim(const string& str, string what) {
	size_t f = str.find_first_not_of(what);
	size_t l = str.find_last_not_of(what);
	if (f == string::npos) {
		return "";
	}
	else {
		return str.substr(f, l - f + 1);
	}
}

string trimLeft(const string& str, string what) {
	size_t f = str.find_first_not_of(what);
	if (f == string::npos) {
		return "";
	}
	else {
		return str.substr(f);
	}
}

string trimRight(const string& str, string what) {
	size_t l = str.find_last_not_of(what);
	if (l == string::npos) {
		return "";
	}
	else {
		return str.substr(0, l + 1);
	}
}

template <typename InputIterator>
void trim(InputIterator first, InputIterator last, string what) {
	for (auto it = first; it != last; ++it) *it = trim(*it, what);
}

void trim(vector<string> &v, string what) {
	trim(v.begin(), v.end(), what);
}

vector<string> split(const string& str, string splitters, bool discardEmpty) {
	vector<string> v;
	string text;

	auto it = str.find_first_of(splitters);
	text = substring(str, 0, it);
	if (!discardEmpty || text.length() > 0) {
		v.push_back(text);
	}

	while (it != string::npos) {
		auto tmp = str.find_first_of(splitters, it + 1);
		text = substring(str, it + 1, tmp);
		if (!discardEmpty || text.length() > 0) {
			v.push_back(text);
		}
		it = tmp;
	};

	return v;
}

string join(const vector<string> &v, string joiner) {
	if (v.size() > 0) {
		return join(v.cbegin(), v.cend(), joiner);
	}
	else {
		return "";
	}
}

template <typename InputIterator>
string join(InputIterator first, InputIterator last, string joiner) {
	size_t n = 0;
	for (auto it = first; it != last; ++it) {
		n += it->length();
	}

	string result;
	result.reserve(n);

	for (auto it = first; it != last; ++it) {
		if (it != first) result += joiner;
		result += *it;
	}

	return result;
}

string encaps(const string& str, size_t capsule_size, char filler, bool accept_overflow) {
	assert(accept_overflow || capsule_size >= str.length());
	// n == (n / 2) + (n + 1) / 2
	if (capsule_size > str.length()) {
		size_t n = capsule_size - str.length();
		return string(n / 2, filler) + str + string((n + 1) / 2, filler);
	}
	else {
		return str;
	}
}

string encapsLeft(const string& str, size_t capsule_size, char filler, bool accept_overflow) {
	assert(accept_overflow || capsule_size >= str.length());
	if (capsule_size > str.length()) {
		return string(capsule_size - str.length(), filler) + str;
	}
	else {
		return str;
	}
}

string encapsRight(const string& str, size_t capsule_size, char filler, bool accept_overflow) {
	assert(accept_overflow || capsule_size >= str.length());
	if (capsule_size > str.length()) {
		return str + string(capsule_size - str.length(), filler);
	}
	else {
		return str;
	}
}

string wrap(const string& str, string left_filler, string right_filler) {
	auto partition = split(str, "\n");
	string text;
	size_t width = 0;
	for (auto it = partition.begin(); it != partition.end(); ++it) {
		if (width < it->length()) {
			width = it->length();
		}
	}
	for (auto it = partition.begin(); it != partition.end(); ++it) {
		if (it->length() > 0) {
			text += left_filler + encapsRight(*it, width) + right_filler;
		}
		text += "\n";
	}
	return text;
}

string capitalize(const string& str) {
	string result;
	result.reserve(str.length());
	for (auto it = str.begin(); it != str.end(); ++it) {
		char c = *it;
		if (c >= 97 && c <= 122) {
			c -= 32;
		}
		result.push_back(c);
	}
	return result;
}

size_t count(const string& str, string search) {
	size_t total = 0;
	size_t cur = str.find_first_of(search);

	while (cur != string::npos) {
		++total;
		cur = str.find_first_of(search, cur + 1);
	};

	return total;
}

bool isDouble(const string& str)
{
	istringstream iss(str);
	double d;

	return iss >> d >> ws && iss.eof();
}