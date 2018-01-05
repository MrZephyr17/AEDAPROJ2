#include "Request.h"

#include "Company.h"
#include "Store.h"
#include "Publication.h"
#include "Date.h"

#include "Supplements.h"

#include <iostream>


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

	if (publication == nullptr || store == nullptr) throw;
}

Request::Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit) : company(company), publication(publ), store(store), quantity(quantity), requestDate(company->today()), deliveryLimit(limit) {}

Request::Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date requestDate, Date limit) : company(company), publication(publ), store(store), quantity(quantity), requestDate(requestDate), deliveryLimit(limit) {}

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

Date Request::getDeliveryLimit() const
{
	return deliveryLimit;
}

unsigned int Request::getQuantity() const
{
	return quantity;
}

string Request::writeInfo() const
{
	string info;

	info = "Request information\n";
	info += "Publication: " + publication->getName() + "\n";
	info += "Store: " + store->getName() + "\n";
	info += "Request date: " + requestDate.write() + "\n";
	info += "Delivery limit: " + deliveryLimit.write() + "\n";
	info += "Quantity: " + to_string(quantity) + "\n\n";

	return info;
}

string Request::writeToFile() const
{
	string space = " ";

	string fileItem = publication->getName() + space + FILE_ITEM_SEPARATOR + space;
	fileItem += store->getName() + space + FILE_ITEM_SEPARATOR + space;
	fileItem += requestDate.write() + space + FILE_ITEM_SEPARATOR + space;
	fileItem += deliveryLimit.write() + space + FILE_ITEM_SEPARATOR + space;
	fileItem += to_string(quantity);

	return fileItem + FILE_LINE_SEPARATOR;
}

void Request::setDeliveryLimit(Date newLimit)
{
	deliveryLimit = newLimit;
}

bool Request::operator<(const Request &r2) const
{
	if (publication != r2.getPublication())
		return publication->getName() < r2.getPublication()->getName();
	else if (quantity != r2.getQuantity())
		return quantity < r2.getQuantity();
	else if (store != r2.getStore())
		return store->getName() < r2.getStore()->getName();
	else
		return requestDate < r2.getRequestDate();
}


Suspended::Suspended(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit, Date suspensionDate) :
	Request(company, publ, store, quantity, limit), suspensionDate(suspensionDate)
{}

Suspended::Suspended(Company *company, Publication *publ, Store *store, unsigned int quantity, Date requestDate, Date limit, Date suspensionDate) :
	Request(company, publ, store, quantity, requestDate, limit), suspensionDate(suspensionDate)
{}

Suspended::Suspended(string info, Company* company) : Request(info, company)
{
	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);

	suspensionDate = Date(trim(separated.at(5)));
}

Date Suspended::getSuspensionDate() const
{
	return suspensionDate;
}

string Suspended::writeInfo() const
{
	string text = Request::writeInfo();
	text.pop_back();
	text = "Suspended " + text;
	text += "Suspension Date: " + suspensionDate.write() + "\n\n";

	return text;
}

string Suspended::writeToFile() const
{
	string space = " ";
	string fileItem = Request::writeToFile();
	fileItem.pop_back();

	fileItem += space + FILE_ITEM_SEPARATOR + space + suspensionDate.write();

	return fileItem + FILE_LINE_SEPARATOR;
}


bool Suspended::operator==(const Suspended& req2) const
{
	return publication == req2.getPublication() && store == req2.getStore()
		&& requestDate == req2.getRequestDate() && suspensionDate == req2.getSuspensionDate();
}