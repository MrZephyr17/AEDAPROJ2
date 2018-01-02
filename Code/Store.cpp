#include "Store.h"

#include "Company.h"
#include "Collection.h"
#include "Employee.h"
#include "Request.h"
#include "Publication.h"
#include "Exceptions.h"
#include "Date.h"

#include "Supplements.h"

#include <algorithm>

PublicationLog::PublicationLog(unsigned int stock, map<Date, unsigned int> sales) : stock(stock), sales(sales) {}

Store::stock_it Store::getPubl(Publication *publ)
{
	for (auto it = stock.begin(); it != stock.end(); ++it)
		if (it->first == publ)
			return it;

	return stock.end();
}

Store::Store(string info, Company *comp) : company(comp)
{
	vector<string> separated = split(info, FILE_LINE_SEPARATOR);
	vector<string> firstLine = split(separated.at(0), FILE_ITEM_SEPARATOR);
	this->name = trim(firstLine.at(0));
	this->contact = trim(firstLine.at(1));
	manager = NULL;

	for (auto it = separated.begin() + 1; it != separated.end(); it++)
	{
		vector<string> line = split(*it, FILE_ITEM_SEPARATOR);
		string name = trim(line.at(0));
		Publication *pub = company->getPublication(name);
		if (pub == nullptr)
		{
			throw MalformedFileItem<Store>(this, "Invalid publication line");
		}

		unsigned int s = stoi(line.at(1));
		map<Date, unsigned int> sales;

		for (auto it = line.begin() + 2; it != line.end(); it++)
		{
			vector<string> m = split(*it, DEFAULT_PAIR_SEPARATOR);
			Date d(trim(m.at(0)));
			unsigned int numberSales = stoi(trim(m.at(1)));

			auto res = sales.insert(pair<Date, unsigned int>(d, numberSales));
			/*if (res.second == false) {
				throw MalformedFileItem<Store>(this, "Repeated date");
			}*/
		}

		PublicationLog pL(s, sales);

		stock.insert(pair<Publication *, PublicationLog>(pub, pL));
	}
}

Store::Store(Company *company, string name, string contact, Employee *manager) : company(company), manager(manager), name(name), contact(contact) {}

Employee *Store::getEmployee() const
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

vector<Request *> Store::getRequests(Collection *collection) const
{
	vector<Request *> res, reqs = company->getRequests(this);
	for (auto it = reqs.begin(); it != reqs.end(); ++it)
	{
		if ((*it)->getPublication()->getCollection() == collection)
		{
			res.push_back(*it);
		}
	}
	return res;
}

vector<Request *> Store::getRequests(Publication *publ) const
{
	vector<Request *> res, reqs = company->getRequests(this);
	for (auto it = reqs.begin(); it != reqs.end(); ++it)
	{
		if ((*it)->getPublication() == publ)
		{
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

void Store::setManager(Employee *newManager)
{
	manager = newManager;
}

bool Store::noStock() const
{
	return stock.empty();
}

void Store::addToStock(Publication *publ, unsigned int s)
{
	getPubl(publ)->second.stock += s;
}

bool Store::sellPublication(Publication *publ, unsigned int quantity)
{
	//update PublicationLog
	unsigned int &stock = getPubl(publ)->second.stock;
	if (stock < quantity)
	{
		stock = 0;
		return false;
	}
	else
	{
		stock -= quantity;
		return true;
	}
}

void Store::makeFixedRequest(Publication *publ, unsigned int quantity)
{
	Request *req = new Request(company, publ, this, quantity);
	company->addRequest(req);
}

void Store::addPublication(Publication *publ, unsigned int st)
{
	for (auto it = stock.begin(); it != stock.end(); it++)
		if (it->first == publ)
			throw(DuplicateElement<Publication>(publ));

	PublicationLog p(st);

	stock[publ] = p;
	// stock.insert(pair<Publication* const, PublicationLog>(publ, st));
}

void Store::addCollection(Collection *collection)
{
	auto publications = collection->getAllPublications();
	for (auto p : publications)
		addPublication(p, 0);
}

void Store::makeRequest(Publication *publ)
{
	if (publ->getCollection()->getType() == TYPE_BOOK)
	{
		Request *request = new Request(company, publ, this, DEFAULT_BOOK_QT_REQ);
		company->addRequest(request);
	}
	else
	{
		Request *request = new Request(company, publ, this, DEFAULT_MAGAZINE_QT_REQ);
		company->addRequest(request);
	}
}

void Store::makeRequests(Collection *collection)
{
	auto publications = collection->getAllPublications();
	for (auto p : publications)
		makeRequest(p);
}

void Store::removePublication(Publication *publ)
{
	for (auto it = stock.begin(); it != stock.end(); it++)
		if (it->first == publ)
			stock.erase(it);

	throw(NonExistentElement<Publication>(publ));
}

void Store::removeCollection(Collection *collection)
{
	auto it = stock.begin();
	auto s = *it;

	for (auto it = stock.begin(); it != stock.end();)
	{
		if (it->first->getCollection() == collection)
			it = stock.erase(it);
		else
			++it;
	}
}

string Store::writeInfo() const
{
	string m;
	vector<LocalPublication> pub = getPublications();

	m = "Store Information\n";
	m += "Name/Local: " + name + "\n";
	m += "Contact: " + contact + "\n";
	m += "Manager: " + (manager ? manager->getName() : "None") + "\n";

	/*
	for (auto it = stock.cbegin(); it != stock.cend(); ++it) {
		m += "Publication: " + it->first->getName() + "\n";
		m += " Stock: " + to_string(it->second.stock) + "\n";
		auto &sales = it->second.sales;
		for (auto s = sales.cbegin(); s != sales.cend(); ++s)
			m += " " + s->first.write() + ": Sold " + to_string(s->second) + "\n";
	}*/

	for (auto x : pub)
	{
		m += "Publication: " + x.publication->getName() + "\n";
		m += " Stock: " + to_string(x.stock) + "\n";
	}
	//sales???
	m += "\n";
	return m;
}

//alterar
string Store::writeToFile() const
{
	string space = " ";
	string str = name + space + FILE_ITEM_SEPARATOR + space + contact + FILE_LINE_SEPARATOR;
	for (auto it = stock.cbegin(); it != stock.cend(); ++it)
	{
		Publication *publ = it->first;
		auto &log = it->second;
		str += publ->getName() + space + FILE_ITEM_SEPARATOR + space;
		str += to_string(log.stock);
		for (auto s = log.sales.cbegin(); s != log.sales.cend(); ++s)
		{
			str += space + FILE_ITEM_SEPARATOR + space + (s->first.write());
			str += space + DEFAULT_PAIR_SEPARATOR + space + (to_string(s->second));
		}
		str += FILE_LINE_SEPARATOR;
	}
	return str;
}

bool Store::operator<(const Store &s2)
{
	return name < s2.getName();
}

vector<Publication *> stockLowerThan(unsigned int n) const
{
	vector<Publication *> lower;
	priority_queue<LocalPublication> temp = stock;
	LocalPublication lp;

	if (temp.empty())
		return lower;

	lp = temp.top();

	while (lp.stock < n)
	{
		lp = temp.top();
		temp.pop();

		lower.push_back(lp.getPublication());
	}

	return lower;
}

vector<LocalPublication> getPublications() const
{
	vector<LocalPublication> publications;
	pirority_queue<LocalPublication> temp = stock;

	while (!temp.empty)
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

LocalPublication Store::LocalPublication getPublication(Publication* publication) const
{
	vector<LocalPublication> pub = getPublications();
	LocalPublication empty;
	
	for(auto x: pub)
	{
		if(x.publication == publication)
		return x;
	}

	return empty;
}

void Store::removePublication(LocalPublication publication)
{
	priority_queue<LocalPublication> pub = stock;

	while (!stock.empty())
	{
		if (stock.top() != publication)
			pub.push(stock.top());

		stock.pop();
	}

	stock = pub;
}