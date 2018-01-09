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

	if (separated.size() == 3) {
		string storeName = trim(separated.at(2));
		store = company->getStore(storeName);
		if (store == nullptr) throw;
	}
	else
		store = nullptr;
}

Employee::Employee(Company* company, string name, Date birthDate) :
	company(company), name(name), birthDate(birthDate), store(nullptr){}

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
	string info;

	info = "Employee information\n";
	info += "Name: " + name + "\n";
	info += "Birthdate: " + birthDate.write() + "\n";
	info += "Designated Store: " + (store ? store->getName() : "None") + "\n\n";

	return info;
} 

string Employee::writeToFile() const 
{
	string space = " ";

	string str = name + space + FILE_ITEM_SEPARATOR + space;
	str += birthDate.write();
	if (store != nullptr) str += space + FILE_ITEM_SEPARATOR + space + store->getName();

	return str + FILE_LINE_SEPARATOR;
}

bool Employee::operator<(const Employee &e2) const
{
	return name < e2.getName();
}