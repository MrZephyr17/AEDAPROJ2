#include "Company.h"
#include "Store.h"
#include "Employee.h"
#include "Publication.h"
#include "Request.h"

#include "Exceptions.h"
#include "Supplements.h"
#include "Console.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>



bool Company::addStore(Store *newS)
{
	if (!nameAvailable(newS->getName())) return false;

	vector<LocalPublication> pub = newS->getPublications();

	for (auto publ : publications) {
		bool found = false;
		for (const auto& lp : pub)
			if (lp.getPublication() == publ) {
				found = true; break;
			}

		if (!found) newS->addPublication(publ, DEFAULT_STOCK_VALUE);
	}

	stores.insert(newS);

	return true;
}


bool Company::addPublication(Publication *newP)
{
	if (!nameAvailable(newP->getName())) return false;

	for (auto store : stores) {
		store->addPublication(newP, DEFAULT_STOCK_VALUE);
	}

	publications.insert(newP);

	return true;
}


bool Company::addEmployee(Employee *newE)
{
	if (!nameAvailable(newE->getName())) return false;

	employees.insert(newE);
	if (newE->getStore() != nullptr)
		designateEmployee(newE->getStore(), newE);

	return true;
}


bool Company::addRequest(Request* newR)
{
	auto search = productionPlan.find(newR);

	if (search == productionPlan.end())
	{
		productionPlan.insert(newR);

		return true;
	}
	else
		return false;
}


bool Company::addSuspendedRequest(Suspended* newSR)
{
	auto search = suspendedRequests.find(newSR);

	if (search == suspendedRequests.end())
	{
		suspendedRequests.insert(newSR);

		return true;
	}
	else
		return false;
}





bool Company::editStore(Store* store, string name, unsigned int contact)
{
	if ((store->getName() != name) && !nameAvailable(name)) return false;

	auto it = stores.find(store);

	store->setName(name);
	store->setContact(to_string(contact));
	stores.erase(it);
	stores.insert(store);

	return true;
}


bool Company::designateEmployee(Store* store, Employee* employee)
{
	if (store != nullptr) {
		Employee* prevManager = store->getManager();
		if (prevManager != nullptr) prevManager->setStore(nullptr);
	}

	if (employee != nullptr) {
		Store* prevStore = employee->getStore();
		if (prevStore != nullptr) prevStore->setManager(nullptr);
	}

	store->setManager(employee);
	employee->setStore(store);

	return true;
}





bool Company::removeStore(Store *store)
{
	auto requests = getRequests(store);
	auto suspended = getSuspendedRequests(store);

	for (auto it = requests.begin(); it != requests.end(); ++it) {
		removeRequest(*it);
	}
	for (auto it = suspended.begin(); it != suspended.end(); ++it) {
		removeSuspended(*it);
	}
	

	if (store->getManager() != nullptr) {
		store->getManager()->setStore(nullptr);
	}

	auto it = stores.find(store);
	if (it == stores.end()) return false;
	stores.erase(it);
	delete store;

	return true;
}


bool Company::removePublication(Publication *publication)
{
	auto requests = getRequests(publication);
	auto suspended = getSuspendedRequests(publication);

	for (auto it = requests.begin(); it != requests.end(); ++it) {
		removeRequest(*it);
	}
	for (auto it = suspended.begin(); it != suspended.end(); ++it) {
		removeSuspended(*it);
	}
	

	for (auto it = stores.begin(); it != stores.end(); ++it) {
		auto store = *it;
		store->removePublication(publication);
	}

	auto it = publications.find(publication);
	if (it == publications.end()) return false;
	publications.erase(it);
	delete publication;

	return true;
}


bool Company::removeEmployee(Employee *employee)
{
	if (employee->getStore() != nullptr) {
		employee->getStore()->setManager(nullptr);
	}

	auto it = employees.find(employee);
	if (it == employees.end()) return false;
	employees.erase(it);
	delete employee;

	return true;
}


bool Company::removeRequest(Request *request)
{
	auto it = productionPlan.find(request);
	if (it == productionPlan.end()) return false;
	productionPlan.erase(it);
	delete request;

	return true;
}


bool Company::removeSuspended(Suspended *suspended)
{
	auto it = suspendedRequests.find(suspended);
	if (it == suspendedRequests.end()) return false;
	suspendedRequests.erase(it);
	delete suspended;

	return true;
}





Store *Company::getStore(string name) const
{
	try {
		return getObject(name, stores);
	}
	catch (NameNotFound err) {
		return nullptr;
	}
}


Publication *Company::getPublication(string name) const
{
	try {
		return getObject(name, publications);
	}
	catch (NameNotFound& err) {
		return nullptr;
	}
}


Employee *Company::getEmployee(string name) const
{
	try {
		return getObject(name, employees);
	}
	catch (NameNotFound err) {
		return nullptr;
	}
}


set<Store*, PComp<Store> > Company::getStores() const
{
	return stores;
}


set<Publication*, PComp<Publication> > Company::getPublications() const
{
	return publications;
}


set<Employee*, PComp<Employee> > Company::getEmployees() const
{
	return employees;
}


vector<Request *> Company::getRequests(const Store *store) const
{
	vector<Request *> reqsStore;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqsStore),
		[&store](Request *request) { return request->getStore() == store; });
	return reqsStore;
}


vector<Request *> Company::getRequests(const Publication *publ) const
{
	vector<Request *> reqsPubl;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqsPubl),
		[&publ](Request *request) { return request->getPublication() == publ; });
	return reqsPubl;
}


vector<Request *> Company::getRequests(const Store* store, const Publication* publication) const
{
	vector<Request *> reqs;
	copy_if(productionPlan.begin(), productionPlan.end(), back_inserter(reqs),
		[&store, &publication](Request* request) { return request->getStore() == store && request->getPublication() == publication; });

	return reqs;
}


vector<Request *> Company::getRequests() const
{
	vector<Request *> reqsAll;
	copy(productionPlan.begin(), productionPlan.end(), back_inserter(reqsAll));
	return reqsAll;
}


vector<Suspended*> Company::getSuspendedRequests(const Store* store) const
{
	vector<Suspended*> suspendedStore;
	copy_if(suspendedRequests.begin(), suspendedRequests.end(), back_inserter(suspendedStore),
		[&store](Suspended* suspended) { return suspended->getStore() == store; });
	return suspendedStore;
}


vector<Suspended*> Company::getSuspendedRequests(const Publication* publication) const
{
	vector<Suspended*> suspendedPubl;
	copy_if(suspendedRequests.begin(), suspendedRequests.end(), back_inserter(suspendedPubl),
		[&publication](Suspended* suspended) { return suspended->getPublication() == publication; });
	return suspendedPubl;
}


vector<Suspended*> Company::getSuspendedRequests(const Store* store, const Publication* publication) const
{
	vector<Suspended*> suspended;
	copy_if(suspendedRequests.begin(), suspendedRequests.end(), back_inserter(suspended),
		[&store, &publication](Suspended* suspended) { return suspended->getStore() == store && suspended->getPublication() == publication; });
	return suspended;
}


vector<Suspended*> Company::getSuspendedRequests() const
{
	vector<Suspended*> suspendedAll;
	copy(suspendedRequests.begin(), suspendedRequests.end(), back_inserter(suspendedAll));
	return suspendedAll;
}





Date Company::today() const
{
	return currentDay;
}


bool Company::setRequestDeadline(Request* request, Date dateLimit)
{
	auto search = productionPlan.find(request);

	if (search != productionPlan.end())
	{
		Request* req = *search;

		productionPlan.erase(search);

		req->setDeliveryLimit(dateLimit);

		productionPlan.insert(req);

		return true;
	}

	throw(NonExistentElement<Request>(request));
}


void Company::checkRequests()
{
	for (auto it = productionPlan.begin(); it != productionPlan.end(); it++)
	{
		if ((*it)->getDeliveryLimit() <= currentDay)
		{
			sendProduction((*it)->getPublication(), (*it)->getStore(), (*it)->getQuantity());
			removeRequest((*it));
		}
	}
}


void Company::sendProduction(Publication *publication, Store *store, unsigned int quantity) const
{
	for (auto x : stores)
		if (x == store)
			x->receiveProduction(publication, quantity);
}


bool Company::suspendRequest(Request *request)
{
	auto search = productionPlan.find(request);

	if (search != productionPlan.end())
	{
		productionPlan.erase(search);

		Suspended* suspend = new Suspended(this, request->getPublication(), request->getStore(), request->getQuantity(), request->getRequestDate(), request->getDeliveryLimit(), currentDay);
		suspendedRequests.insert(suspend);

		return true;
	}
	else
		return false;
}


bool Company::endSuspension(Suspended* suspended)
{
	auto search = suspendedRequests.find(suspended);

	if (search != suspendedRequests.end())
	{
		suspendedRequests.erase(search);

		Request* original = new Request(this, suspended->getPublication(), suspended->getStore(), suspended->getQuantity(),
			suspended->getRequestDate(), suspended->getDeliveryLimit());

		removeSuspended(suspended);


		addRequest(original);
		return true;
	}
	else
		return false;
}


void Company::checkSuspendedRequests()
{
	vector<Suspended*> toDelete;
	for (auto it = suspendedRequests.begin(); it != suspendedRequests.end(); ++it)
	{
		Suspended* sus = *it;
		if (sus->getSuspensionDate() + DEFAULT_REQUEST_DEADLINE >= currentDay)
		{
			toDelete.push_back(sus);
		}
	}
	for (auto sus : toDelete) removeSuspended(sus);
}


bool Company::nameAvailable(string name) const
{
	try {
		auto publ = getObject(name, publications);
		return false;
	}
	catch (NameNotFound& err) {}

	try {
		auto store = getObject(name, stores);
		return false;
	}
	catch (NameNotFound& err) {}

	try {
		auto employee = getObject(name, employees);
		return false;
	}
	catch (NameNotFound& err) {}

	return true;
}