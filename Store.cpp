#include "Store.h"

#include "Company.h"
#include "Employee.h"
#include "Request.h"
#include "Publication.h"
#include "Exceptions.h"
#include "Date.h"

#include "Supplements.h"

#include <algorithm>


Store::Store(string info, Company *comp) : company(comp)
{
	vector<string> separated = split(info, FILE_LINE_SEPARATOR);
	vector<string> firstLine = split(separated.at(0), FILE_ITEM_SEPARATOR);
	this->name = trim(firstLine.at(0));
	this->contact = trim(firstLine.at(1));
	manager = nullptr;

	for (auto it = separated.begin() + 1; it != separated.end(); ++it)
	{
		string line = *it;
		vector<string> pair = split(line, FILE_ITEM_SEPARATOR);
		string name = trim(pair.at(0));
		Publication *publ = company->getPublication(name);

		if (publ == nullptr)
			throw MalformedFileItem<Store>(this, "Invalid store stock line.");

		unsigned int s = stoi(pair.at(1));

		addPublication(publ, s);
	}
}

Store::Store(Company *company, string name, string contact, Employee *manager)
	: company(company), manager(manager), name(name), contact(contact) {}

Employee *Store::getManager() const
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

vector<Request *> Store::getRequests() const
{
	return company->getRequests(this);
}

vector<Request *> Store::getRequests(string collection) const
{
	vector<Request *> res, reqs = company->getRequests(this);

	copy_if(reqs.begin(), reqs.end(), back_inserter(res),
		[&collection](Request *request) { return request->getPublication()->getCollection() == collection; });

	return reqs;
}

vector<Request *> Store::getRequests(Publication *publ) const
{
	vector<Request *> res, reqs = company->getRequests(this);

	copy_if(reqs.begin(), reqs.end(), back_inserter(res),
		[&publ](Request *request) { return  request->getPublication() == publ; });

	return reqs;
}

void Store::setName(string newName)
{
	name = newName;
}

void Store::setContact(string newContact)
{
	contact = newContact;
}

void Store::setManager(Employee *newManager)
{
	manager = newManager;
}

bool Store::noStock() const
{
	return stock.empty();
}

bool Store::sellPublication(Publication *publ, unsigned int quantity)
{
	LocalPublication lp = getPublication(publ);
	unsigned int st = lp.getStock();
	removePublication(lp);

	if (st < quantity)
	{
		lp.setStock(0);
		stock.push(lp);

		return false;
	}
	else
	{
		lp.setStock(st - quantity);
		stock.push(lp);

		return true;
	}
}

void Store::makeRequest(Publication *publ, unsigned int quantity, Date limit)
{
	Request *request = new Request(company, publ, this, quantity, limit);
	company->addRequest(request);
}

void Store::addPublication(Publication *publ, unsigned int st)
{
	vector<LocalPublication> pub = getPublications();

	for (const auto& x : pub)
		if (x.getPublication() == publ)
			throw(DuplicateElement<Publication>(publ));

	LocalPublication lp(publ, st);
	stock.push(lp);
}

bool Store::removePublication(Publication* publ)
{
	LocalPublication lp = getPublication(publ);

	if (lp.getPublication() != nullptr) {
		removePublication(lp);
		return true;
	}

	throw NonExistentElement<Publication>(publ);
}

string Store::writeInfo() const
{
	string info;
	vector<LocalPublication> pub = getPublications();

	info = "Store Information\n";
	info += "Name/Local: " + name + "\n";
	info += "Contact: " + contact + "\n";
	info += "Manager: " + (manager ? manager->getName() : "None") + "\n";

	for (const auto& x : pub)
	{
		info += "Publication: " + x.getPublication()->getName() + "\n";
		info += "Stock: " + to_string(x.getStock()) + "\n";
	}
	info += "\n";

	return info;
}

string Store::writeToFile() const
{
	vector<LocalPublication> publications = getPublications();
	string space = " ";
	string fileItem = name + space + FILE_ITEM_SEPARATOR + space + trim(contact) + FILE_LINE_SEPARATOR;

	for (auto x : publications)
		fileItem += x.write();

	return fileItem + FILE_LINE_SEPARATOR;
}

bool Store::operator<(const Store &s2) const
{
	return name < s2.getName();
}

vector<Publication *> Store::stockLowerThan(unsigned int n) const
{
	vector<Publication *> lower;
	priority_queue<LocalPublication> temp = stock;
	LocalPublication lp;

	if (temp.empty())
		return lower;

	lp = temp.top();

	while (lp.getStock() < n)
	{
		lower.push_back(lp.getPublication());
		temp.pop();
		lp = temp.top();
	}

	return lower;
}

vector<LocalPublication> Store::getPublications() const
{
	vector<LocalPublication> publications;
	priority_queue<LocalPublication> temp = stock;

	while (!temp.empty())
	{
		publications.push_back(temp.top());
		temp.pop();
	}

	return publications;
}

void Store::receiveProduction(Publication *publication, unsigned int quantity)
{
	LocalPublication pub = getPublication(publication);
	removePublication(pub);
	pub.addStock(quantity);
	stock.push(pub);
}

LocalPublication Store::getPublication(Publication* publication) const
{
	vector<LocalPublication> pub = getPublications();
	LocalPublication empty;

	for (const auto& x : pub)
		if (x.getPublication() == publication)
			return x;

	return empty;
}

void Store::removePublication(LocalPublication publication)
{
	priority_queue<LocalPublication> pub = stock;
	LocalPublication top;

	while (!stock.empty())
	{
		top = stock.top();

		if (top != publication)
			pub.push(stock.top());

		stock.pop();
	}

	stock = pub;
}