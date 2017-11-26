#include "Publication.h"

#include "Collection.h"

#include <iostream>



Publication::Publication(string name, string description, Collection* collection, Date date, double price) :
	name(name), description(description), collection(collection), date(date), price(price) {}

string Publication::getName() const
{
	return name;
}

string Publication::getDescription() const
{
	return description;
}

Collection* Publication::getCollection() const
{
	return collection;
}

Date Publication::getDate() const
{
	return date;
}

double Publication::getPrice() const
{
	return price;
}

void Publication::setName(string newName)
{
	name = newName;
}

void Publication::setDescription(string newDescription)
{
	description = newDescription;
}

void Publication::setPrice(double newPrice)
{
	price = newPrice;
}

string Publication::writeInfo() const
{
	string m;

	m = "Name: " + name + "\n";
	m += "Description: " + description + "\n";
	m += "Collection: " + collection->getName() + "\n";
	m += "Date: " + date.write() + "\n";
	m += "Price: " + to_string(price) + "\n";

	return m;
}





Book::Book(string name, string description, Collection* collection, Date date, double price, string version) :
	Publication(name, description, collection, date, price), version(version) {}

string Book::getVersion() const
{
	return version;
}

string Book::writeInfo() const
{
	string m = Publication::writeInfo();
	m += "Version: " + version + "\n\n";

	return m;
}





Magazine::Magazine(string name, string description, Collection* collection, Date date, double price, unsigned int v, unsigned int n)
	: Publication(name, description, collection, date, price), volume(v), number(n) {}

unsigned int Magazine::getVolume() const
{
	return volume;
}

unsigned int Magazine::getNumber() const
{
	return number;
}

string Magazine::writeInfo() const
{
	string m = Publication::writeInfo();
	m += "Volume: " + to_string(volume) + "\n";
	m += "Number: " + to_string(number) + "\n\n";

	return m;
}