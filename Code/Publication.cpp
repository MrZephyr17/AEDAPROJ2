#include "Publication.h"
#include "Supplements.h"
#include "Company.h"
#include <iostream>

LocalPublication::LocalPublication() : publication(nullptr), stock(stock) {}

LocalPublication::LocalPublication(Publication *publication, unsigned int stock) : publication(publication), stock(stock) {}

Publication *LocalPublication::getPublication() const
{
	return publication;
}

unsigned int LocalPublication::getStock() const
{
	return stock;
}

void LocalPublication::setStock(unsigned int stock)
{
	this->stock = stock;
}

void LocalPublication::addStock(unsigned int quantity)
{
	stock += quantity;
}


string LocalPublication::write() const
{
	string space = " ";

	return publication->getName() + space + FILE_ITEM_SEPARATOR + space + to_string(stock) + FILE_LINE_SEPARATOR;
}

//maior ou menor?
bool LocalPublication::operator<(const LocalPublication &p2) const
{
	return stock > p2.getStock();
}

bool LocalPublication::operator==(const LocalPublication &p2) const
{
	return publication == p2.getPublication() && stock == p2.getStock();
}

bool LocalPublication::operator!=(const LocalPublication& p2) const
{
	return !(*this == p2);
}





Publication::Publication(string name, string description, string collection, Date releaseDate, double price, string type)
	: company(company), name(name), description(description), collection(collection), releaseDate(releaseDate), price(price), type(type) {}

Publication::Publication(string info, Company* company)
	: company(company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	type = trim(separated.at(0));
	name = trim(separated.at(1));
	description = trim(separated.at(2));
	collection = trim(separated.at(3));
	releaseDate = Date(trim(separated.at(4)));
	price = stod(separated.at(5));
}

string Publication::getName() const
{
	return name;
}

string Publication::getDescription() const
{
	return description;
}

string Publication::getCollection() const
{
	return collection;
}

Date Publication::getReleaseDate() const
{
	return releaseDate;
}

double Publication::getPrice() const
{
	return price;
}

string Publication::getType() const
{
	return type;
}

vector<Request*> Publication::getRequests() const
{
	return company->getRequests(this);
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
	string info;

	info = "Name: " + name + "\n";
	info += "Description: " + description + "\n";
	info += "Collection: " + collection + "\n";
	info += "Date: " + releaseDate.write() + "\n";
	info += "Price: " + to_string(price) + "\n";

	return info;
}

string Publication::writeToFile() const
{	
	string space = " ";

	string fileItem = type + space + FILE_ITEM_SEPARATOR + space;
	fileItem += name + space + FILE_ITEM_SEPARATOR + space;
	fileItem += description + space + FILE_ITEM_SEPARATOR + space;
	fileItem += collection + space + FILE_ITEM_SEPARATOR + space;
	fileItem += releaseDate.write() + space + FILE_ITEM_SEPARATOR + space;
	fileItem += to_string(price) + space + FILE_ITEM_SEPARATOR + space;

	return fileItem;
}

bool Publication::operator<(const Publication& publ) const
{
	return name < publ.getName();
}




Book::Book(string name, string description, string collection, Date date, double price, unsigned int edition)
	: Publication(name, description, collection, date, price, "Book"), edition(edition) {}

Book::Book(string info, Company* company) : Publication(info, company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	this->edition = stoi(separated.at(separated.size()-1));
}

unsigned int Book::getEdition() const
{
	return edition;
}

string Book::writeInfo() const
{
	string info = Publication::writeInfo();

	info += "Version: " + to_string(edition) + "\n\n";

	return info;
}

string Book::writeToFile() const
{
	string fileItem = Publication::writeToFile();

	fileItem += to_string(edition) + "\n";

	return fileItem;
}



Magazine::Magazine(string name, string description, string collection, Date date, double price, unsigned int v, unsigned int n)
	: Publication(name, description, collection, date, price, "Magazine"), volume(v), number(n) {}

Magazine::Magazine(string info, Company* company) : Publication(info,company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	this->volume = stoi(separated.at(6));
	this->number = stoi(separated.at(7));
}

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

string Magazine::writeToFile() const
{
	string fileItem = Publication::writeToFile();
	string space = " ";

	fileItem += to_string(volume) + space + FILE_ITEM_SEPARATOR + space;
	fileItem += to_string(number);
	fileItem += "\n";

	return fileItem;
}