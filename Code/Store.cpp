#include "Store.h"

#include "Company.h"
#include "Employee.h"
#include "Request.h"
#include "Publication.h"
#include "Exceptions.h"
#include "Date.h"

#include "Supplements.h"



PublicationLog::PublicationLog(unsigned int stock) :
	stock(stock) {}

PublicationLog::PublicationLog(unsigned int stock, map<Date, unsigned int> sales) :
	stock(stock), sales(sales) {}


Store::stock_it Store::getPubl(Publication* publ) {
	for (auto it = stock.begin(); it != stock.end(); ++it)
		if (it->first == publ)
			return it;

	return stock.end();
}

Store::Store(string info, Company* comp) :
	company(comp)
{
	vector<string> separated = split(info, FILE_LINE_SEPARATOR);
	vector<string> firstLine = split(separated.at(0), FILE_ITEM_SEPARATOR);
	this->name = trim(firstLine.at(0));
	this->contact = trim(firstLine.at(1));

	for (auto it = separated.begin() + 1; it != separated.end(); it++) {
		vector<string> line = split(*it, FILE_ITEM_SEPARATOR);
		string name = trim(line.at(0));
		Publication* pub = company->getPublication(name);
		if (pub == nullptr) {
			throw MalformedFileItem<Store>(this, "Invalid publication line");
		}


		unsigned int s = stoi(line.at(1));
		map<Date, unsigned int> sales;

		for (auto it = line.begin() + 2; it != line.end(); it++) {
			vector<string> m = split(*it, DEFAULT_PAIR_SEPARATOR);
			Date d(trim(m.at(0)));
			unsigned int numberSales = stoi(trim(m.at(1)));

			auto res = sales.insert(pair<Date, unsigned int>(d, numberSales));
			/*if (res.second == false) {
				throw MalformedFileItem<Store>(this, "Repeated date");
			}*/
		}

		PublicationLog pL(s, sales);

		stock.insert(pair<Publication*, PublicationLog>(pub, pL));


	}
}

Store::Store(Company* company, string name, string contact, Employee* manager) :
	company(company), manager(manager), name(name), contact(contact) {}

Employee* Store::getEmployee() const
{
	return manager;
}

string Store::getName() const
{
	return name;
}

string Store::getContact() const
{
	return contact;
}

vector<Request*> Store::getRequests() const
{
	return company->getRequests(this);
}

vector<Request*> Store::getRequests(Collection* collection) const
{
	vector<Request*> res, reqs = company->getRequests(this);
	for (auto it = reqs.begin(); it != reqs.end(); ++it) {
		if ((*it)->getPublication()->getCollection() == collection) {
			res.push_back(*it);
		}
	}
	return res;
}

vector<Request*> Store::getRequests(Publication* publ) const
{
	vector<Request*> res, reqs = company->getRequests(this);
	for (auto it = reqs.begin(); it != reqs.end(); ++it) {
		if ((*it)->getPublication() == publ) {
			res.push_back(*it);
		}
	}
	return res;
}

void Store::setName(string newName)
{
	name = newName;
}

void Store::setContact(string newContact)
{
	contact = newContact;
}

void Store::setManager(Employee* newManager)
{
	manager = newManager;
}

void Store::addToStock(Publication* publ, unsigned int s)
{
	getPubl(publ)->second.stock += s;
}

bool Store::sellPublication(Publication* publ, unsigned int quantity)
{
	unsigned int& stock = getPubl(publ)->second.stock;
	if (stock < quantity) {
		stock = 0;
		return false;
	}
	else {
		stock -= quantity;
		return true;
	}
}

void Store::makeFixedRequest(Publication* publ, unsigned int quantity)
{
	Request* req = new Request(company, publ, this, quantity);
	company->addRequest(req);
}

void Store::addPublication(Publication* publ, unsigned int st)
{
	for (auto it = stock.begin(); it != stock.end(); it++)
		if (it->first == publ)
			throw(DuplicateElement<Publication>(publ));

	PublicationLog p(st);

	stock.insert(pair<Publication*, PublicationLog>(publ, st));
	
}

void Store::addCollection(Collection* collection)
{
	// ...
}

void Store::makeRequest(Publication* publ) const
{
	// ...
}

void Store::makeRequests(Collection* collection) const
{
	// ...
}

void Store::removePublication(Publication* publ)
{
	for (auto it = stock.begin(); it != stock.end(); it++)
		if (it->first == publ)
			stock.erase(it);

	throw(NonExistentElement<Publication>(publ));
}

void Store::removeCollection(Collection* collection)
{
	// ...
}

string Store::writeInfo() const
{
	string m;

	m = "Store Information\n";
	m += "Name/Local: " + name + "\n";
	m += "Contact: " + contact + "\n";
	m += "Manager: " + (manager ? manager->getName() : "None") + "\n";

	for (auto it = stock.cbegin(); it != stock.cend(); ++it) {
		m += "Publication: " + it->first->getName() + "\n";
		m += " Stock: " + to_string(it->second.stock) + "\n";
		auto &sales = it->second.sales;
		for (auto s = sales.cbegin(); s != sales.cend(); ++s)
			m += " " + s->first.write() + ": Sold " + to_string(s->second) + "\n";
	}

	m += "\n";
	return m;
}

string Store::writeToFile() const {
	string str = name + FILE_ITEM_SEPARATOR + contact + FILE_LINE_SEPARATOR;
	for (auto it = stock.cbegin(); it != stock.cend(); ++it) {
		Publication* publ = it->first;
		auto& log = it->second;
		str += publ->getName() + FILE_ITEM_SEPARATOR;
		str += log.stock;
		for (auto s = log.sales.cbegin(); s != log.sales.cend(); ++s) {
			str += FILE_ITEM_SEPARATOR + s->first.write();
			str	+= DEFAULT_PAIR_SEPARATOR + to_string(s->second);
		}
		str += FILE_LINE_SEPARATOR;
	}
	return str;
}