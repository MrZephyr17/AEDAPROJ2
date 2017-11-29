// ****************************************************************************************************
// ***************************************** NAVIGATOR_CPP__ ******************************************
// ****************************************************************************************************
#include "managers.h"
#include "Exceptions.h"
#include "Store.h"
#include <algorithm>
#include "Employee.h"
#include "Collection.h"
#include "Publication.h"

namespace Managers {
	namespace {
		void toPage(ManagerData &data, Input input) {
			if (input.is.integer) {
				string next = data.nextPage + to_string(input.integer) + ".";
				if (data.menu->has(next)) {
					data.nextPage = next;
					data.leave = true;
				}
				else {
					data.errorLog = "Page not found: " + next;
				}
			}
			if (input.is.plainText) {
				vector<string> v = split(input.plainText, PAGE_SPLITTERS, true);
				if (v.size() > 0) {
					trim(v);
					string next = data.nextPage + join(v, ".") + ".";
					if (data.menu->has(next)) {
						data.nextPage = next;
						data.leave = true;
					}
					else {
						data.errorLog = "Page not found: " + next;
					}
				}
				else {
					data.errorLog = "Command not recognized: " + input.plainText;
				}
			}
		}
		bool validStoreName(string storeName) {
			return isalpha(storeName[0]) && (storeName.length() < 30);
		}
		bool validStoreContact(int storeContact) {
			return (storeContact >= 1e8) && (storeContact < 1e9);
		}
		bool validEmployeeName(string storeName) {
			for (auto c : storeName) {
				if (!isalpha(c) && !iswspace(c)) return false;
			}
			return true;
		}
		bool validBirthDate(string birthDate) {
			auto a = birthDate.find_first_of('-');
			if (a != string::npos) {
				auto b = birthDate.find_first_of('-', a);
				if (b != string::npos) return true;
			}
			return false;
		}
	}

	void Navigator(const Page& page) {
		ManagerData data(page);

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Page Index = Access the page.\n";

		do {
			{
				cout << page.mainContent << endl;
				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			Input input = data.reader.extract();

			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				data.errorLog = "No command.";
			}
			if (input.is.integer) {
				toPage(data, input);
			}
			if (input.is.plainText) {
				toPage(data, input);
			}

			system("cls");
		} while (!data.leave);
	}

	void Controller11(const Page& page)
	{
		ManagerData data(page);

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write a store name to see more information.\n";
		data.instructions += "Write nothing to unselect that store.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.store != nullptr)
					cout << data.company->writeStore(data.chosen.store);
				else
					cout << data.company->writeStores();

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				data.chosen.store = nullptr;
				data.infoLog = "Showing information for all stores.";
			}
			if (input.is.integer) {
				data.errorLog = "Expected a string for a store name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.store = data.company->getStore(input.plainText);
					data.infoLog = "Showing information for store " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);
	}

	void Controller12(const Page& page)
	{
		ManagerData data(page);

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write a collection name to see more information.\n";
		data.instructions += "Write nothing to unselect collection.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.collection != nullptr)
					cout << data.company->writeCollection(data.chosen.collection);
				else
					cout << data.company->writeCollections();

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				data.chosen.collection = nullptr;
				data.infoLog = "Showing information for all collections.";
			}
			if (input.is.integer) {
				data.errorLog = "Expected a string for a collection name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.collection = data.company->getCollection(input.plainText);
					data.infoLog = "Showing information for collection " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller13(const Page& page)
	{
		ManagerData data(page);

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write an employee name to see more information.\n";
		data.instructions += "Write nothing to unselect employee.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.employee != nullptr)
					cout << data.company->writeEmployee(data.chosen.employee);
				else
					cout << data.company->writeEmployees();

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				data.chosen.employee = nullptr;
				data.infoLog = "Showing information for all employees.";
			}
			if (input.is.integer) {
				data.errorLog = "Expected a string for an employee name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.employee = data.company->getEmployee(input.plainText);
					data.infoLog = "Showing information for employee " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller211(const Page& page)
	{
		ManagerData data(page);
		string storeName;
		int storeContact = 0;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the information of the new store, as requested.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				cout << "Store Information" << endl;
				cout << "Store Name: " << storeName << endl;
				cout << "Store Contact: " << (storeContact ? to_string(storeContact) : "") << endl << endl;

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					Store* store = new Store(data.company, storeName, to_string(storeContact));
					data.company->addStore(store);
					storeName.clear(); storeContact = 0;
				}
				catch (DuplicateElement<Store> &s) {
					data.errorLog = s.message();
				}
			}
			if (input.is.integer) {
				if (validStoreContact(input.integer))
					storeContact = input.integer;
				else
					data.errorLog = "Invalid store contact number.";
			}
			if (input.is.plainText) {
				if (validStoreName(input.plainText))
					storeName = input.plainText;
				else
					data.errorLog = "Invalid store name.";
			}

			system("cls");
		} while (!data.leave);


	}

	//Fazer
	void Controller212(const Page& page)
	{
		ManagerData data(page);
		string storeName;
		int storeContact = 0;
		string employeeName;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the name of the store you want to edit.\n";
		data.instructions += "Next, write the new data in the format \"Variable: new Data\".\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.store != nullptr)
				{
					//colocar nova info
				}
				else
					cout << data.company->writeStores();

			

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					storeName.clear(); storeContact = 0;
				}
				catch (DuplicateElement<Store> &s) {
					data.errorLog = s.message();
				}
			}
			if (input.is.integer) {
				if (validStoreContact(storeContact))
					storeContact = input.integer;
				else
					data.errorLog = "Invalid store contact number.";
			}
			if (input.is.plainText) {
				if (validStoreName(storeName))
					storeName = input.plainText;
				else
					data.errorLog = "Invalid store name.";
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller213(const Page& page)
	{
		ManagerData data(page);
		string storeName;
		int storeContact = 0;
		string employeeName;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the name of the store you want to remove.\n";
		data.instructions += "Press enter to remove the store.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.store == nullptr)
					cout << data.company->writeStores();
				else {
					cout << "You will be removing the following store" << endl << endl;
					cout << data.company->writeStore(data.chosen.store);
				}

				
				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				if (data.chosen.store != nullptr) {
					try {
						data.company->removeStore(data.chosen.store);
						data.chosen.store = nullptr;
					}
					catch (NonExistentElement<Store> &e) {
						data.errorLog = e.message();
					}
				}
				else {
					data.errorLog = "No store selected.";
				}
			}
			if (input.is.integer) {
				data.errorLog = "Invalid store name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.store = data.company->getStore(input.plainText);
					data.infoLog = "Selected store " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller221(const Page& page)
	{
		ManagerData data(page);
		string employeeName;
		string birthDate;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the information of the new employee, as requested.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				cout << "Employee Information" << endl;
				cout << "Employee's Name: " << employeeName << endl;
				cout << "Employee's birth date: " << birthDate << endl << endl;

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					Employee* employee = new Employee(data.company, employeeName, Date(birthDate));
					data.company->addEmployee(employee);
					employeeName.clear(); birthDate.clear();
				}
				catch (Date::InvalidDate &date) {
					data.errorLog = "Invalid date given.";
					birthDate.clear();
				}
				catch (DuplicateElement<Employee> &s) {
					data.errorLog = s.message();
				}
			}
			if (input.is.integer) {
				data.errorLog = "Invalid employee data.";
			}
			if (input.is.plainText) {
				if (validBirthDate(input.plainText))
					birthDate = input.plainText;
				else if (validEmployeeName(input.plainText))
					employeeName = input.plainText;
				else
					data.errorLog = "Invalid data.";
			}

			system("cls");
		} while (!data.leave);


	}
	
	void Controller222(const Page& page)
	{
		ManagerData data(page);
		string employeeName;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the name of the employee you want to remove.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.employee == nullptr)
					cout << data.company->writeEmployees();
				else {
					cout << "You will be removing the following employee" << endl << endl;
					cout << data.company->writeEmployee(data.chosen.employee);
				}


				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					data.company->removeEmployee(data.chosen.employee);
					data.chosen.employee = nullptr;
				}
				catch (NonExistentElement<Employee> &e) {
					data.errorLog = e.message();
				}
			}
			if (input.is.integer) {
				data.errorLog = "Invalid employee name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.employee = data.company->getEmployee(input.plainText);
					data.infoLog = "Selected employee " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}

	namespace {
		bool validCollectionName(string name){
			return name.size() < 50 && isalpha(name[0]);
		}
		bool validCollectionType(string type) {
			return (type == "Book" || type =="Magazine");
		}
		bool validProductionTime(unsigned int time) {
			return time > 0 && time < 30;
		}
	}

	void Controller231(const Page& page)
	{
		ManagerData data(page);
		string name;
		string type;
		unsigned int minProductionTime=0;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write a suitable name for the collection.\n";
		data.instructions += "For the type, write \"Book\" or \"Magazine\".\n";
		data.instructions += "For the production time, choose the number of days it takes\n";
		data.instructions += " to produce a publication of this collection.\n";
		data.instructions += "Press Enter to create the collection once done.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				cout << "Collection Information" << endl;
				cout << "Collection's Name: " << name << endl;
				cout << "Collection's Type: " << type << endl;
				cout << "Collection's Minimum Production Time: " << to_string(minProductionTime) << endl << endl;

				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					Collection* collection;
					if (type == TYPE_BOOK)
					{
						collection = new BookCollection(data.company, name, type, minProductionTime);
					}
					else
					{
						collection = new MagazineCollection(data.company, name, type, minProductionTime, DEFAULT_MAGAZINE_FREQ);
					}
					data.company->addCollection(collection);
					name.clear(); type.clear(); minProductionTime = 0;
				}
				catch (DuplicateElement<Employee> &s) {
					data.errorLog = s.message();
				}
			}
			if (input.is.integer) {
				if (validProductionTime(input.integer))
					minProductionTime = input.integer;
				else
					data.errorLog = "Invalid value for minimum production time.";
			}
			if (input.is.plainText) {
				if (validCollectionType(input.plainText))
					type = input.plainText;
				else if (validCollectionName(input.plainText))
					name = input.plainText;
				else
					data.errorLog = "Invalid data.";
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller232(const Page& page)
	{
		ManagerData data(page);
		string employeeName;

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the name of the collection you want to edit.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.collection == nullptr)
					cout << data.company->writeCollections();


				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				//asdasd
			}
			if (input.is.integer) {
				data.errorLog = "Invalid employee name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.collection = data.company->getCollection(input.plainText);
					data.infoLog = "Selected collection " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}

	void Controller233(const Page& page)
	{
		ManagerData data(page);

		data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
		data.instructions += "Write the name of the collection you want to remove.\n";

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.collection == nullptr)
					cout << data.company->writeCollections();
				else {
					cout << "You will be removing the following collection" << endl << endl;
					cout << data.company->writeCollection(data.chosen.collection);
				}


				cout << Aux::writeLogs(data);
				Aux::clear(data);
			}

			// 2. Wait User input
			Input input = data.reader.extract();

			// 3. Check User input
			if (input.is.ctrlZ) {
				data.nextPage = page.father;
				data.leave = true;
			}
			if (input.is.freeEnter) {
				try {
					data.company->removeCollection(data.chosen.collection);
					data.chosen.collection = nullptr;
				}
				catch (NonExistentElement<Collection> &e) {
					data.errorLog = e.message();
				}
			}
			if (input.is.integer) {
				data.errorLog = "Invalid collection name.";
			}
			if (input.is.plainText) {
				try {
					data.chosen.collection = data.company->getCollection(input.plainText);
					data.infoLog = "Selected collection " + input.plainText + ".";
				}
				catch (NameNotFound &e) {
					data.errorLog = e.message();
				}
			}

			system("cls");
		} while (!data.leave);


	}
}
