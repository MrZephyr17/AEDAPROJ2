#pragma once
// ****************************************************************************************************
// ***************************************** SUPPLEMENTS_H__ ******************************************
// ****************************************************************************************************
#include "Classes.h"

// Returns the substring [first, last).
string substring(const string& str, size_t first, size_t last);

// Returns a substring without leading and/or trailing whitespace characters.
string trim(const string& str, string what = " \n\t\r");
string trimLeft(const string& str, string what = " \n\t\r");
string trimRight(const string& str, string what = " \n\t\r");
template <typename InputIterator>
void trim(InputIterator first, InputIterator last, string what = " \n\t\r");
void trim(vector<string> &v, string what = " \n\t\r");

// Partitions a given string into multiple substrings at any of the specified characters,
// removing such characters and optionally also any empty such substrings.
vector<string> split(const string& str, string splitters, bool discard_empty = false);

// Concatenates in order the multiple strings in a vector, optionally connecting them with another string.
string join(const vector<string> &v, string joiner = "");
template <typename InputIterator>
string join(InputIterator first, InputIterator last, string joiner = "");

// Returns a new string of specified length capsule_size that is the result of filling in the
// left and/or right the given string with the specified character. Overflow can be allowed.
string encaps(const string& str, size_t capsule_size, char filler = ' ', bool accept_overflow = false);
string encapsLeft(const string& str, size_t capsule_size, char filler = ' ', bool accept_overflow = false);
string encapsRight(const string& str, size_t capsule_size, char filler = ' ', bool accept_overflow = false);

// Wraps each line of a multiple lined string with a given filler on the left and on the right.
string wrap(const string& str, string left_filler, string right_filler = "");

// Returns a new string that is the ASCII-capitalized equivalent of the given one.
string capitalize(const string& str);

// Counts the number of occurrences of characters in the given string.
size_t count(const string& str, string search);

// Checks if a given string is a double
bool isDouble(const string& s);

template <typename T>
struct PComp
{
	bool operator()(const T* a, const T* b) const
	{
		return *a < *b;
	}
};

template <class T>
typename vector<T*>::iterator findElement(T* el, vector<T*> &vec)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
		if (*it == el)
			return it;

	return vec.end();
}

template <class T>
typename vector<T*>::const_iterator findElement(T* el, const vector<T*> &vec)
{
	for (auto it = vec.cbegin(); it != vec.cend(); ++it)
		if (*it == el)
			return it;

	return vec.cend();
}

template <class T>
typename vector<T*>::iterator findObject(string name, vector<T*> &vec)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
		if ((*it)->getName() == name)
			return it;

	return vec.end();
}

template <class T>
typename set<T*>::const_iterator findObject(string name, const set<T*, PComp<T>> &set)
{
	for (auto it = set.cbegin(); it != set.cend(); ++it)
		if ((*it)->getName() == name)
			return it;

	return set.cend();
}

template <class T>
bool existsElement(T* el, const vector<T*> &vec)
{
	return findElement(el, vec) != vec.cend();
}

template <class T>
bool hasObject(string name, const vector<T*> &vec)
{
	return findElement(name, vec) != vec.cend();
}

template <class T>
T* getObject(string name, const set<T*, PComp<T> > &set)
{
	auto it = findObject(name, set);
	if (it == set.cend())
		throw(NameNotFound(name, typeid(T).name()));
	else
		return *it;
}