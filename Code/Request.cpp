#include "Request.h"

#include "Company.h"
#include "Store.h"
#include "Collection.h"
#include "Publication.h"
#include "Date.h"

#include "Supplements.h"

#include <iostream>

bool RequestPtr::operator==(const RequestPtr& req2) const
{
	return suspensionDate == req2.getSuspensionDate() && request == req2.getRequest();
}

RequestPtr::RequestPtr(Request* request, Date suspensionDate) : 
request(request), suspensionDate(suspensionDate)
{}


Request::Request(string info, Company *company) : company(company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	string publName = trim(separated.at(0));
	publication = company->getPublication(publName);

	string storeName = trim(separated.at(1));
	store = company->getStore(storeName);

	requestDate = Date(trim(separated.at(2)));

	deliveryLimit = Date(trim(separated.at(3)));

	quantity = stoi(separated.at(4));
}

Request::Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit) : company(company), publication(publ), store(store), quantity(quantity), requestDate(company->today()), deliveryLimit(limit) {}

Publication *Request::getPublication() const
{
	return publication;
}

Store *Request::getStore() const
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

void Request::changeStore(Store *newStore)
{
	store = newStore;
}

void Request::setDeliveryLimit(Date newLimit)
{
	deliveryLimit = newLimit;
}

/*
bool Request::isDone() const
{
	unsigned int prodTime = publication->getCollection()->getMinProductionTime();

	return ((requestDate + prodTime) >= company->today());
}
*/

string Request::writeInfo() const
{
	string m;

	m = "Request information\n";
	m += "Publication: " + publication->getName() + "\n";
	m += "Store: " + store->getName() + "\n";
	m += "Request date: " + requestDate.write() + "\n";
	m += "Delivery limit: " + deliveryLimit.write() + "\n";
	m += "Quantity: " + to_string(quantity) + "\n\n";

	return m;
}

string Request::writeToFile() const
{
	string space = " ";
	string str = publication->getName() + space + FILE_ITEM_SEPARATOR + space;
	str += store->getName() + space + FILE_ITEM_SEPARATOR + space;
	str += requestDate.write() + space + FILE_ITEM_SEPARATOR + space;
	str += deliveryLimit.write() + space + FILE_ITEM_SEPARATOR + space;
	str += to_string(quantity) + FILE_LINE_SEPARATOR;
	return str;
}

Date Request::getDeliveryLimit() const
{
	return deliveryLimit;
}

bool Request::operator<(const Request &r2)
{
	if (publication == r2.getPublication())
		return quantity < r2.getQuantity();
	else
		return publication < r2.getPublication();
}