#include "Request.h"

#include "Company.h"
#include "Store.h"
#include "Collection.h"
#include "Publication.h"
#include "Date.h"

#include "Supplements.h"

#include <iostream>

Request::Request(string info, Company* company) :
	company(company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	string publName = trim(separated.at(0));
	publication = company->getPublication(publName);

	string storeName = trim(separated.at(1));
	store = company->getStore(storeName);

	requestDate = Date(trim(separated.at(2)));
	
	quantity = stoi(separated.at(3));
}

Request::Request(Company* company, Publication* publ, Store* store, unsigned int quantity) :
	company(company), publication(publ), store(store), quantity(quantity) {}

Publication* Request::getPublication() const
{
	return publication;
}

Store* Request::getStore() const
{
	return store;
}

Date Request::getRequestDate() const
{
	return requestDate;
}

unsigned int Request::getQuantity() const
{
	return quantity;
}

void Request::changeStore(Store* newStore)
{
	store = newStore;
}

/*
bool Request::isDone() const
{
	unsigned int prodTime = publication->getCollection()->getMinProductionTime();

	return ((requestDate + prodTime) >= company->today());
}
*/

void Request::conclude()
{
	// ...
}

string Request::writeInfo() const
{
	string m;

	m = "Request information\n";
	m += "Publication: " + publication->getName() + "\n";
	m += "Store: " + store->getName() + "\n";
	m += "Request date: " + requestDate.write() + "\n";
	m += "Quantity: " + to_string(quantity) + "\n\n";

	return m;
}

string Request::writeToFile() const
{
	string str = publication->getName() + FILE_ITEM_SEPARATOR;
	str += store->getName() + FILE_ITEM_SEPARATOR;
	str += requestDate.write() + FILE_ITEM_SEPARATOR;
	str += to_string(quantity) + FILE_LINE_SEPARATOR;
	return str;
}