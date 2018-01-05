#include "Exceptions.h"


NameNotFound::NameNotFound(string name, string type)
{
	this->name = name;
	this->type = type;
}

string NameNotFound::message()
{
	string m = "Could not find an element of type " + type + " with that name!\n";

	return m;
}