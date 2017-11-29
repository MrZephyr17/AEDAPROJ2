#include "Employee.h"

#include "Company.h"
#include "Store.h"
#include "Supplements.h"

#include <iostream>

Employee::Employee(string info, Company* company) :
	company(company)
{

	vector<string> separated = split(info, FILE_ITEM_SEPARATOR);
	name = trim(separated.at(0));
	birthDate = Date(trim(separated.at(1)));

	string storeName;
	if (separated.size() == 3) {
		storeName = trim(separated.at(2));
		store = company->getStore(storeName);
	}
	else
		store = NULL;
}

Employee::Employee(Company* company, string name, Date birthDate) :
	company(company), name(name), birthDate(birthDate) {}

string Employee::getName() const
{
	return name;
}

Date Employee::getBirthDate() const
{
	return birthDate;
}

Store* Employee::getStore() const
{
	return store;
}

void Employee::setName(string newName)
{
	name = newName;
}

void Employee::setBirthDate(Date newBirthDate)
{
	birthDate = newBirthDate;
}

void Employee::setStore(Store* newStore)
{
	if (newStore != nullptr) newStore->setManager(this);
	store = newStore;
}

string Employee::writeInfo() const
{
	string m;
	m = "Employee information\n";
	m += "Name: " + name + "\n";
	m += "Birthdate: " + birthDate.write() + "\n";
	m += "Designated Store: " + (store ? store->getName() : "None") + "\n\n";

	return m;
} 

string Employee::writeToFile() const {
	string space = " ";
	string str = name + space + FILE_ITEM_SEPARATOR + space;
	str += birthDate.write();
	str += (store ? (space + FILE_ITEM_SEPARATOR + space + store->getName()) : "") + FILE_LINE_SEPARATOR;
	return str;
}