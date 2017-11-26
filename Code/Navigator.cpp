// ****************************************************************************************************
// ***************************************** NAVIGATOR_CPP__ ******************************************
// ****************************************************************************************************
#include "managers.h"
#include "Exceptions.h"
#include "Store.h"
#include <algorithm>

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

	namespace {
		bool validStoreName(string storeName) {
			return isalpha(storeName[0]) && (storeName.length() < 30);
		}
		bool validStoreContact(int storeContact) {
			return (storeContact >= 1e8) && (storeContact < 1e9);
		}
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

		do {
			// 1. Write Page Content
			{
				cout << page.mainContent << endl;

				// Write Page Content
				if (data.chosen.store == nullptr)
				{
					cout << data.company->writeStores();
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
				data.company->removeStore(data.company->getStore(storeName));
			}
			if (input.is.integer) {
					data.errorLog = "Invalid store name.";
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
}