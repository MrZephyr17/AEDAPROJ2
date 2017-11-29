#include "Collection.h"

#include "Company.h"
#include "Publication.h"
#include "Supplements.h"
#include "Date.h"

#include <iostream>
#include <algorithm>


Collection::Collection(string info, Company* company) :
	company(company)
{
	vector<string> separated = split(info, "\n");
	vector<string> firstLine = split(separated.at(0), FILE_ITEM_SEPARATOR);

	this->name = trim(firstLine.at(0));
	this->type = trim(firstLine.at(1));
	this->minProductionTime = stoi(firstLine.at(2));
}

Collection::Collection(Company* company, string name, string type, unsigned int time) :
	company(company), name(name), type(type), minProductionTime(time) {}

string Collection::getName() const
{
	return name;
}

string Collection::getType() const
{
	return type;
}

unsigned int Collection::getMinProductionTime() const
{
	return minProductionTime;
}

void Collection::setName(string newName)
{
	name = newName;
}

void Collection::setType(string newType)
{
	type = newType;
}

void Collection::setMinProductionTime(unsigned int newTime)
{
	minProductionTime = newTime;
}

vector<Publication*> Collection::getAllPublications() const {
	return vector<Publication*>();
}

Publication* Collection::getPublication(string name) const
{
	cout << "e isto\n";
	return nullptr;
}

bool Collection::hasPublication(Publication* publ) const
{
	return false;
}

bool Collection::hasPublication(string name) const
{
	return getPublication(name) != nullptr;
}

string Collection::writeInfo() const
{
	string m;

	m = "Collection Information\n";
	m += "Name: " + name + "\n";
	m += "Type: " + type + "\n";
	m += "Minimum Production Time: " + to_string(minProductionTime) + "\n";

	return m;
}

string Collection::writeToFile() const {
	string str = name + " " + FILE_ITEM_SEPARATOR + " ";
	str += type + " " + FILE_ITEM_SEPARATOR + " ";
	str += to_string(minProductionTime) + FILE_LINE_SEPARATOR;
	return str;
}

 
bool Collection::operator<(const Collection& c2){
	return name<c2.getName(); 
}


BookCollection::BookCollection(Company* company, string name, string type, unsigned int time) :
	Collection(company, name, type, time) {}

BookCollection::book_it BookCollection::getBook(Book* book)
{
	for (auto it = books.begin(); it != books.end(); ++it)
		if (*it == book)
			return it;

	return books.end();
}

BookCollection::BookCollection(string info, Company* company) :
	Collection(info, company)
{
	vector<string> separated = split(info, "\n");

	for (auto it = separated.begin() + 1; it != separated.end(); it++) {
		vector<string> info = split(*it, FILE_ITEM_SEPARATOR);

		string name = trim(info.at(0));
		string description = trim(info.at(1));
		Date date(trim(info.at(2)));
		double price = stod(info.at(3));

		Book* book = new Book(name, description, this, date, price);
		books.push_back(book);
	}
}

vector<Book*> BookCollection::getBooks() const
{
	return books;
}

Book* BookCollection::getBook(string name) const
{
	for (auto it = books.cbegin(); it != books.cend(); ++it)
		if ((*it)->getName() == name)
			return *it;

	return nullptr;
}

bool cheaper(const Book* b1, const Book* b2)
{
	return b1->getPrice() < b2->getPrice();
}

vector<Book*> BookCollection::sortCheaper() const
{
	vector<Book*> sorted = books;

	sort(sorted.begin(), sorted.end(), cheaper);

	return sorted;
}

vector<Publication*> BookCollection::getAllPublications() const {
	vector<Publication*> pub;

	transform(books.begin(), books.end(), back_inserter(pub), [](Book* book) {return (Publication*)book; });

	return pub;
}

Publication* BookCollection::getPublication(string name) const
{
	for (auto it = books.cbegin(); it != books.cend(); ++it)
		if ((*it)->name == name)
			return *it;

	return nullptr;
}

bool BookCollection::hasPublication(Publication* publ) const
{
	for (auto it = books.cbegin(); it != books.cend(); ++it)
		if (*it == publ)
			return true;
	
	return false;
}

bool BookCollection::hasPublication(string name) const
{
	return getPublication(name) != nullptr;
}

void BookCollection::addBook(Book* book)
{
	//assert(getBook(book) == books.end());
	books.push_back(book);

	// REST HERE ?
}

void BookCollection::removeBook(Book* book)
{
	//assert(getBook(book) == books.end());
	auto it = getBook(book);
	books.erase(it);

	// REST HERE ?
	// UPDATE STORES HERE ?
	// UPDATE REQUESTS HERE ?
	// DELETE HERE ?
}

void BookCollection::updateBook(Book* oldB, Book* newB)
{
	//assert(getBook(book) == books.end());
	auto it = getBook(oldB);
	*it = newB;

	// REST HERE ?
	// UPDATE STORES HERE ?
	// UPDATE REQUESTS HERE ?
	// DELETE oldB HERE ?
}

string BookCollection::writeInfo() const
{
	string m = Collection::writeInfo() + "\n";
	for (auto it = books.cbegin(); it != books.cend(); ++it)
		m += (*it)->writeInfo();
	return m;
}

string BookCollection::writeToFile() const
{
	string str = Collection::writeToFile();
	for (unsigned i = 0; i < books.size(); i++)
	{
		str += books[i]->getName() + " " + FILE_ITEM_SEPARATOR + " ";
		str += books[i]->getDescription() + " " + FILE_ITEM_SEPARATOR + " ";
		str += books[i]->getDate().write() + " " + FILE_ITEM_SEPARATOR + " ";
		str += to_string(books[i]->getPrice()) + "\n";
	}
	return str;
}





MagazineCollection::MagazineCollection(string info, Company* company) :
	Collection(info, company)
{
	vector<string> separated = split(info, "\n");
	vector<string> secondLine = split(separated.at(1), FILE_ITEM_SEPARATOR);

	releaseFrequency = stoi(secondLine.at(0));

	string description = trim(secondLine.at(1));
	unsigned int volume = stoi(secondLine.at(2));
	unsigned int number = stoi(secondLine.at(3));
	Date date(trim(secondLine.at(4)));
	double price = stod(secondLine.at(5));
	magazine = new Magazine(name, description, this, date, price, volume, number);
}

MagazineCollection::MagazineCollection(Company* company, string name, string type, unsigned int time, unsigned int freq) :
	Collection(company, name, type, time), releaseFrequency(freq) {
	magazine = new Magazine(name, DEFAULT_DESCRIPTION, this, company->today(), DEFAULT_PRICE, 1, 1);
}

Magazine* MagazineCollection::getMagazine() const
{
	return magazine;
}

unsigned int MagazineCollection::getReleaseFrequency() const
{
	return releaseFrequency;
}

void MagazineCollection::setReleaseFrequency(unsigned int newFreq)
{
	releaseFrequency = newFreq;
}

vector<Publication*> MagazineCollection::getAllPublications() const {
	vector<Publication*> pub;

	pub.push_back((Publication*)magazine);

	return pub;
}

Publication* MagazineCollection::getPublication(string name) const
{
	if (magazine->name == name)
		return magazine;
	else
		return nullptr;
}

bool MagazineCollection::hasPublication(Publication* publ) const
{
	return magazine == publ;
}

bool MagazineCollection::hasPublication(string name) const
{
	return getPublication(name) != nullptr;
}

void MagazineCollection::updateMagazine()
{
	// ...
}

bool MagazineCollection::isPublishDate()
{
	return (magazine->date + releaseFrequency) == company->today();
}

string MagazineCollection::writeInfo() const
{
	string m = Collection::writeInfo();
	m += "Release frequency: " + to_string(releaseFrequency) + "\n\n";
	m += (magazine ? magazine->writeInfo() : "No Magazine yet\n\n");

	return m;
}

string MagazineCollection::writeToFile() const {
	string str = Collection::writeToFile();
	str += to_string(releaseFrequency) + " " + FILE_ITEM_SEPARATOR + " ";
	str += magazine->getDescription() + " " + FILE_ITEM_SEPARATOR + " ";
	str += to_string(magazine->getVolume()) + " " + FILE_ITEM_SEPARATOR + " ";
	str += to_string(magazine->getNumber()) + " " + FILE_ITEM_SEPARATOR + " ";
	str += magazine->getDate().write() + " " + FILE_ITEM_SEPARATOR + " ";
	str += to_string(magazine->getPrice()) + FILE_LINE_SEPARATOR;
	//str += magazine->writeInfo() + FILE_LINE_SEPARATOR;
	return str;
}