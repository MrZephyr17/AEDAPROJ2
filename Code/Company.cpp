#include "Company.h"
#include "Store.h"
#include "Collection.h"
#include "Employee.h"
#include "Publication.h"
#include "Request.h"

#include "Exceptions.h"
#include "Supplements.h"

#include <algorithm>
#include <iostream>
#include <fstream>
//#include <cstdlib>
//#include <typeinfo>



void Company::addStore(Store* newS)
{
	for (auto it = stores.cbegin(); it != stores.cend(); ++it) {
		if (*it == newS) throw DuplicateElement<Store>(newS);
	}
	stores.push_back(newS);

	for (auto it = collections.begin(); it != collections.end(); ++it) {
		newS->addCollection(*it);
		newS->makeRequests(*it);
	}
}

void Company::addCollection(Collection* newC)
{
	for (auto it = collections.cbegin(); it != collections.cend(); ++it) {
		if (*it == newC) throw DuplicateElement<Collection>(newC);
	}
	collections.push_back(newC);

	for (auto it = stores.begin(); it != stores.end(); ++it) {
		(*it)->addCollection(newC);
		(*it)->makeRequests(newC);
	}
}

void Company::addEmployee(Employee* newE)
{
	for (auto it = employees.cbegin(); it != employees.cend(); ++it) {
		if (*it == newE) throw DuplicateElement<Employee>(newE);
	}
	employees.push_back(newE);
}

void Company::addRequest(Request* newR)
{
	for (auto it = productionPlan.cbegin(); it != productionPlan.cend(); ++it) {
		if (*it == newR) throw DuplicateElement<Request>(newR);
	}
	productionPlan.push_back(newR);
}



void Company::removeStore(Store* store)
{
	for (auto it = productionPlan.begin(); it != productionPlan.end(); ++it) {
		if ((*it)->getStore() == store) {
			delete *it;
			productionPlan.erase(it);
			if (it == productionPlan.end()) break;
		}
	}

	if (store->getEmployee() != nullptr) {
		store->getEmployee()->setStore(nullptr);
	}

	for (auto it = stores.begin(); it != stores.end(); ++it) {
		if (*it == store) {
			delete store;
			stores.erase(it);
			break;
		}
	}
}


void Company::removeCollection(Collection* collection)
{
	for (auto it = stores.begin(); it != stores.end(); ++it) {
		(*it)->removeCollection(collection);
	}

	for (auto it = productionPlan.begin(); it != productionPlan.end(); ++it) {
		if ((*it)->getPublication()->getCollection() == collection) {
			delete *it;
			productionPlan.erase(it);
			if (it == productionPlan.end()) break;
		}
	}

	for (auto it = collections.begin(); it != collections.end(); ++it) {
		if (*it == collection) {
			delete collection;
			collections.erase(it);
			break;
		}
	}
}


void Company::removeEmployee(Employee* employee)
{
	employee->setStore(nullptr);
	for (auto it = employees.begin(); it != employees.end(); ++it) {
		if (*it == employee) {
			delete employee;
			employees.erase(it);
			break;
		}
	}
}


void Company::removeRequest(Request* request)
{
	for (auto it = productionPlan.begin(); it != productionPlan.end(); ++it) {
		if (*it == request) {
			delete request;
			productionPlan.erase(it);
			break;
		}
	}
}

Store* Company::getStore(string name) const
{
	return getObject(name, stores);
}

Collection* Company::getCollection(string name) const
{
	return getObject(name, collections);
}


Publication* Company::getPublication(string name) const
{
	for (int i = 0; i < collections.size();i++) {
		Publication* publ = collections.at(i)->getPublication(name);
		if (publ != nullptr) return publ;
	}

	return nullptr;
}

Employee* Company::getEmployee(string name) const
{
	return getObject(name, employees);
}

vector<Request*> Company::getRequests(const Store* store) const
{
	vector<Request*> reqs;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqs),
		[&store](Request* request) { return request->getStore() == store; });
	return reqs;
}

vector<Request*> Company::getRequests(const Publication* publ) const
{
	vector<Request*> reqs;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqs),
		[&publ](Request* request) { return request->getPublication() == publ; });
	return reqs;
}

vector<Request*> Company::getRequests(const Collection* collection) const
{
	vector<Request*> reqs;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqs),
		[&collection](Request* request) { return request->getPublication()->getCollection() == collection; });
	return reqs;
}

Date Company::today() const
{
	return currentDay;
}



string Company::writeStores()
{
	string m;

	m = "Currently ICNM holds the following stores\n";

		for (auto it = stores.begin(); it != stores.end(); it++)
			m += (*it)->getName() + "\n";

	m += "\n";

	return m;
}

string Company::writeStore(Store* st)
{
	string m;

	for (auto it = stores.begin(); it != stores.end(); it++)
		if ((*it) == st)
			m=(*it)->writeInfo();

	if(m.empty())
		throw(NonExistentElement<Store>(st));


	return m;
}

string Company::writeCollection(Collection* col) {

	string m;

	for (auto it = collections.begin(); it != collections.end(); it++)
		if ((*it) == col)
			m = (*it)->writeInfo();

	if (m.empty())
		throw(NonExistentElement<Collection>(col));


	return m;

}
string Company::writeCollections() {

	string m;

	m = "Currently ICNM's catalogue holds the following collections\n";

	for (auto it = collections.begin(); it != collections.end(); it++)
		m += (*it)->getName() + "\n";

	m += "\n";

	return m;
}

string Company::writeEmployee(Employee* emp)
{
	string m;

	for (auto it = employees.begin(); it != employees.end(); it++)
		if ((*it) == emp)
			m = (*it)->writeInfo();

	if (m.empty())
		throw(NonExistentElement<Employee>(emp));


	return m;
}

string Company::writeEmployees()
{

	string m;

	m = "Currently ICNM employs the following individuals\n";

	for (auto it = employees.begin(); it != employees.end(); it++)
		m += (*it)->getName() + "\n";

	m += "\n";

	return m;
}

/*
vector<Publication *> Company::getPublications() const
{
	return publications;
}

vector<Store *> Company::getStores() const
{
	return stores;
}

void Company::addStore(Store *newS)
{
	if(!existsElement(newS,stores))
		stores.push_back(newS);

	else 
		throw DuplicateElement<Store>(newS);
}

void Company::addRequest(Request *req)
{
	if (!existsElement(req, productionPlan))
		productionPlan.push_back(req);
	else
		throw DuplicateElement<Request>();
}

void Company::addPublication(Publication *newJ)
{
	if(!existsElement(newJ,publications))
		publications.push_back(newJ);
	else
		throw DuplicateElement<Publication>();
}


vector<Publication *> Company::searchByCollection(string collection)
{
	vector<Publication *> pub;

	for (vector<Publication *>::iterator it = publications.begin(); it != publications.end(); it++)
		if ((*it)->getCollection() == collection)
			pub.push_back(*it);

	return pub;
}
 
void Company::removeStore(unsigned int id)
{
	for (vector<Store *>::iterator it = stores.begin(); it != stores.end(); it++)
		if ((*it)->getId() == id)
			stores.erase(it);

	throw NonExistentId(id,"Store");
}

void Company::searchPub(string name)
{
	vector<Publication *>::iterator pubIt;

	vector<Store *> existing = searchPublication(name, pubIt);

	if (existing.size() == 0)
		cout << "That publication doesn't exist / is not currently available!";
	else
	{
		cout << "Here's the info of the publication you specified:" << endl;

		(*pubIt)->showInfo();

		cout << "You can find this publication in the following stores: ";

		for (vector<Store *>::iterator it = existing.begin(); it != existing.end(); it++)
		{

			if (it != existing.begin())
				cout << ", ";

			cout << (*it)->getPlace();
		}
	}
}






vector<Store *> Company::searchPublication(string name, vector<Publication *>::iterator &pubIt)
{
	Publication *p1 = NULL;
	vector<Store *> stores;

	for (vector<Publication *>::iterator it = publications.begin(); it != publications.end(); it++)
		if ((*it)->getName() == name)
		{
			pubIt = it;
			p1 = *it;
		}

	if (p1 == NULL)
		return stores;

	for (vector<Store *>::iterator it = stores.begin(); it != stores.end(); it++)
		if ((*it)->searchPublication(p1) != (*it)->getEnd())
			stores.push_back(*it);

	return stores;
}



/*
void Company::updateRequests()
{
	for (auto it = productionPlan.begin(); it != productionPlan.end(); it++)
	{

		if ((*it)->isDone())
		{
			(*it)->getStore()->addToStock((*it)->getPublication(), (*it)->getQuantity());
			//erase no vetor da stores
			productionPlan.erase(*it);
			it--;
		}
	}
}



Employee* Company::getEmployee(unsigned int id)
{
	return getObject(id, employees);
}


Publication* getPublication(string name)
{
	for(auto it=publications.begin();it!=publications.end();it++){
		if(it->getName()==name)
			return *it;
	}
	//excecao?
	return NULL;
}


Store* Company::getStore(string name)
{
	for(auto it=stores.begin();it!=stores.end();it++){
		if(it->getName()==name)
			return *it;
	}
	//excecao?
	return NULL;
}


*/