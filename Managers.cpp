// ****************************************************************************************************
// ***************************************** NAVIGATOR_CPP__ ******************************************
// ****************************************************************************************************
#include "Managers.h"
#include "Exceptions.h"
#include "Supplements.h"
#include "Date.h"

#include "Company.h"
#include "Employee.h"
#include "Publication.h"
#include "Request.h"
#include "Store.h"

#include <algorithm>
#include <iomanip>


namespace Managers {
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
			Aux::toPage(data, input);
		}
		if (input.is.plainText) {
			Aux::toPage(data, input);
		}

		system("cls");
	} while (!data.leave);
}





void Controller11(const Page& page)
{
	// (1.1) List of Stores - Check stock per publication
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a store name to see more information.\n";
	data.instructions += "Just press enter to unselect that store.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			if (data.chosen.store != nullptr)
				cout << Writer::writeStoreDetails(data.company, data.chosen.store);

			cout << endl << endl;
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
			data.infoLog = "Now showing the list of stores.";
		}
		if (input.is.integer) {
			data.errorLog = "A store's name should be plain text, not an integer.";
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				data.chosen.store = store;
				data.infoLog = "Showing detailed information for store " + input.plainText + ".";
			}
			else {
				data.errorLog = "Store with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller12(const Page& page)
{
	// (1.2) List of Publications - Check stock per store
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication name to see more information.\n";
	data.instructions += "Just press enter to unselect that publication.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl;
			if (data.chosen.publication != nullptr)
				cout << Writer::writePublicationDetails(data.company, data.chosen.publication);

			cout << endl << endl;
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
			data.chosen.publication = nullptr;
			data.infoLog = "Now showing the list of publications.";
		}
		if (input.is.integer) {
			data.errorLog = "A publication's name should be plain text, not an integer.";
		}
		if (input.is.plainText) {
			Publication* publication = data.company->getPublication(input.plainText);
			if (publication != nullptr) {
				data.chosen.publication = publication;
				data.infoLog = "Showing detailed  information for collection " + input.plainText + ".";
			}
			else {
				data.errorLog = "Publication with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller13(const Page& page)
{
	// (1.3) List of Employees - Personal information and working status
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write an employee name to see more information.\n";
	data.instructions += "Just press enter to unselect that employee.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeEmployees(data.company, data.chosen.employee) << endl;
			if (data.chosen.employee != nullptr)
				cout << Writer::writeEmployeeDetails(data.company, data.chosen.employee);

			cout << endl << endl;
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
			data.infoLog = "Now showing the list of employees.";
		}
		if (input.is.integer) {
			data.errorLog = "An employees's name should be plain text, not an integer.";
		}
		if (input.is.plainText) {
			Employee* employee = data.company->getEmployee(input.plainText);
			if (employee != nullptr) {
				data.chosen.employee = employee;
				data.infoLog = "Showing detailed information of employee " + input.plainText + ".";
			}
			else {
				data.errorLog = "Employee with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller14(const Page& page)
{
	// (1.4) Detailed list of all active requests
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a store name or a publication name to filter the table.\n";
	data.instructions += "Just press enter to unselect that store or publication filter.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store != nullptr)
				cout << Writer::writeRequests(data.company, data.chosen.store);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeRequests(data.company, data.chosen.publication);
			else
				cout << Writer::writeRequests(data.company);

			cout << endl << endl;
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
			data.chosen.publication = nullptr;
			data.infoLog = "Now showing the table of all active requests.";
		}
		if (input.is.integer) {
			data.errorLog = "A store or publication's name should be plain text, not an integer.";
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller15(const Page& page)
{
	// (1.5) Detailed list of suspended requests
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a store name or a publication name to filter the table.\n";
	data.instructions += "Just press enter to unselect that store or publication filter.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store != nullptr)
				cout << Writer::writeSuspended(data.company, data.chosen.store);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeSuspended(data.company, data.chosen.publication);
			else
				cout << Writer::writeSuspended(data.company);

			cout << endl << endl;
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
			data.chosen.publication = nullptr;
			data.infoLog = "Now showing the table of all suspended requests.";
		}
		if (input.is.integer) {
			data.errorLog = "A store or publication's name should be plain text, not an integer.";
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for suspended requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for suspended requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}





void Controller211(const Page& page)
{
	// (2.1.1) Add a Store
	ManagerData data(page);

	string storeName;
	int storeContact;
	bool name = false, contact = false;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the information of the new store, as requested.\n";
	data.instructions += "Name should be plain text and contact should be a (phone) number.\n";
	data.instructions += "Once done, just press enter to create the store!\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company) << endl;

			cout << encaps(" § Store Information § ", SHORT_WIDTH, '=') + "\n";
				
			cout << " >> Store Name: ";
			if (name) cout << storeName;
			cout << endl;
				
			cout << " >> Store Contact: ";
			if (contact) cout << to_string(storeContact);
			cout << endl;

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (contact) {
				contact = false;
			}
			else if (name) {
				name = false;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (name && contact) {
				Store* store = new Store(data.company, storeName, to_string(storeContact));
				bool success = data.company->addStore(store);
				if (success) {
					data.infoLog = "Successfully created store '" + storeName + "'.";
					name = false; contact = false;
				}
				else {
					data.errorLog = "Invalid store information: a store with the same name already exists.";
					name = false;
					delete store;
				}
			}
			else {
				if (!name) {
					data.errorLog = "Please write the store's name.";
				}
				else if (!contact) {
					data.errorLog = "Please write the store's contact number.";
				}
			}
		}
		if (input.is.integer) {
			if (Aux::validStoreContact(input.integer)) {
				storeContact = input.integer;
				contact = true;
			}
			else {
				data.errorLog = "Invalid store contact number.";
			}
		}
		if (input.is.plainText) {
			if (Aux::validStoreName(input.plainText)) {
				storeName = input.plainText;
				name = true;
			}
			else {
				data.errorLog = "Invalid store name.";
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller212(const Page& page)
{
	// (2.1.2) Update/Edit a Store
	ManagerData data(page);

	string storeName;
	int storeContact;
	bool name = false, contact = false;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the name of the store you want to edit.\n";
	data.instructions += "Then write the new data (as if you were creating the store from scratch).\n";
	data.instructions += "Just press enter to confirm.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;

			if (data.chosen.store != nullptr) {
				cout << encaps(" § Store Information § ", SHORT_WIDTH, '=') + "\n";
				cout << " >>>> Selected Store: " << data.chosen.store->getName() << endl << endl;
				
				cout << " >> Store Name: ";
				if (name) cout << storeName;
				cout << endl;

				cout << " >> Store Contact: ";
				if (contact) cout << to_string(storeContact);
				cout << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (contact) {
				contact = false;
			}
			else if (name) {
				name = false;
			}
			else if (data.chosen.store != nullptr) {
				data.chosen.store = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (name && contact) {
				bool success = data.company->editStore(data.chosen.store, storeName, contact);
				if (success) {
					data.infoLog = "Successfully editted store '" + storeName + "'.";
					name = false; contact = false;
					data.chosen.store = nullptr;
				}
				else {
					data.errorLog = "Invalid store information: a store with the same name already exists.";
					name = false;
				}
			}
			else {
				if (!name) {
					data.errorLog = "Please write the store's name.";
				}
				else if (!contact) {
					data.errorLog = "Please write the store's contact number.";
				}
			}
		}
		if (input.is.integer) {
			if (data.chosen.store != nullptr) {
				if (Aux::validStoreContact(input.integer)) {
					storeContact = input.integer;
					contact = true;
				}
				else {
					data.errorLog = "Invalid store contact number.";
				}
			}
			else {
				data.errorLog = "Expected a store name for store selection.";
			}
		}
		if (input.is.plainText) {
			if (data.chosen.store != nullptr) {
				if (Aux::validStoreName(input.plainText)) {
					storeName = input.plainText;
					name = true;
				}
				else {
					data.errorLog = "Invalid store name.";
				}
			}
			else {
				Store* store = data.company->getStore(input.plainText);
				if (store != nullptr) {
					data.chosen.store = store;
					storeName = store->getName();
					storeContact = stoi(store->getContact());
					name = true; contact = true;
					data.infoLog = "Editing store " + input.plainText + ".";
				}
				else {
					data.errorLog = "Store with name '" + input.plainText + "' not found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller213(const Page& page)
{
	// (2.1.3) Remove a Store
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the name of the store you want to remove.\n";
	data.instructions += "Press enter to confirm and remove the store.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;

			if (data.chosen.store != nullptr) {
				cout << "\n >>>> You have selected the following store for removal:\n\n";
				cout << Writer::writeStoreDetails(data.company, data.chosen.store) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (data.chosen.store != nullptr) {
				data.chosen.store = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.store != nullptr) {
				string name = data.chosen.store->getName();
				bool success = data.company->removeStore(data.chosen.store);
				if (success) {
					data.infoLog = "Successfully removed the store " + name + ".";
					data.chosen.store = nullptr;
				}
				else {
					data.errorLog = "Failed to remove store " + name + ".";
				}
			}
			else {
				data.errorLog = "No store selected.";
			}
		}
		if (input.is.integer) {
			data.errorLog = "Expected a store name.";
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				data.chosen.store = store;
				data.infoLog = "Selected store " + input.plainText + " for removal. Press enter to confirm.";
			}
			else {
				data.errorLog = "Store with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}



void Controller221(const Page& page)
{
	// (2.2.1) Create Book or Magazine
	ManagerData data(page);

	constexpr int stepName = 0, stepDescription = 1,
		stepCollection = 2, stepPrice = 3, stepType = 4,
		stepEdition = 5, stepVolume = 5, stepNumber = 6;
	int step = stepName;

	string name, description, collection, type;
	double price;
	// Book
	unsigned int edition;
	// Magazine
	unsigned int volume, number;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the information of the new publication in order.\n";
	data.instructions += "Name, description, collection and type should be plain text.\n";
	data.instructions += "Price may be decimal; last fields should be integers.\n";
	data.instructions += "Once done, just press enter to create the publication!\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writePublications(data.company) << endl;

			cout << encaps(" § Publication Information § ", SHORT_WIDTH, '=') + "\n";

			cout << " >> Publication's Name: ";
			if (step > stepName) cout << name;
			cout << endl;

			cout << " >> Publication's Description: ";
			if (step > stepDescription) cout << description;
			cout << endl;

			cout << " >> Collection: ";
			if (step > stepCollection) cout << collection;
			cout << endl;

			cout << " >> Standard Price: ";
			if (step > stepPrice) cout << price;
			cout << endl;

			cout << " >>>> Type (Book/Magazine): ";
			if (step > stepType) cout << type;
			cout << endl;

			if (step > stepType) {
				if (type == TYPE_BOOK) {
					cout << " >> Book Version: ";
					if (step > stepEdition) cout << edition;
					cout << endl;
				}
				if (type == TYPE_MAGAZINE) {
					cout << " >> Magazine's Volume: ";
					if (step > stepVolume) cout << volume;
					cout << endl;

					cout << " >> Magazine's Number: ";
					if (step > stepNumber) cout << number;
					cout << endl;
				}
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (step == stepName) {
				data.nextPage = page.father;
				data.leave = true;
			}
			else {
				--step;
			}
		}
		if (input.is.freeEnter) {
			if (type == TYPE_BOOK && step > stepEdition) {
				Book* book = new Book(name, description, collection, data.company->today(), price, edition);
				bool success = data.company->addPublication(book);
				if (success) {
					data.infoLog = "Successfully created book '" + name + "'.";
					step = stepName;
				}
				else {
					data.errorLog = "Invalid book information: a publication with the same name already exists.";
					step = stepName;
					delete book;
				}
			}
			if (type == TYPE_MAGAZINE && step > stepNumber) {
				Magazine* magazine = new Magazine(name, description, collection, data.company->today(), price, volume, number);
				bool success = data.company->addPublication(magazine);
				if (success) {
					data.infoLog = "Successfully created magazine '" + name + "'.";
					step = stepName;
				}
				else {
					data.errorLog = "Invalid magazine information: a publication with the same name already exists.";
					step = stepName;
					delete magazine;
				}
			}
		}
		if (input.is.integer) {
			if (step > stepType) {
				if (type == TYPE_BOOK) {
					if (step == stepEdition) {
						edition = input.integer;
						data.infoLog = "Set edition to " + to_string(edition) + ".";
						++step;
					}
					else {
						data.infoLog = "All fields have been set already!";
					}
				}
				if (type == TYPE_MAGAZINE) {
					if (step == stepVolume) {
						volume = input.integer;
						data.infoLog = "Set volume to " + to_string(volume) + ".";
						++step;
					}
					else if (step == stepNumber) {
						number = input.integer;
						data.infoLog = "Set number to " + to_string(number) + ".";
						++step;
					}
					else {
						data.infoLog = "All fields have been set already!";
					}
				}
			}
			else {
				if (step == stepPrice) {
					price = input.integer;
					data.infoLog = "Set price to " + to_string(price) + ".";
					++step;
				}
				else {
					data.errorLog = "Expected plain text input for the next field.";
				}
			}
		}
		if (input.is.plainText) {
			if (step <= stepType) {
				if (step == stepName) {
					name = input.plainText;
					data.infoLog = "Set name to " + name + ".";
					++step;
				}
				else if (step == stepDescription) {
					description = input.plainText;
					data.infoLog = "Set description to " + description + ".";
					++step;
				}
				else if (step == stepCollection) {
					collection = input.plainText;
					data.infoLog = "Set collection to " + collection + ".";
					++step;
				}
				else if (step == stepType) {
					type = input.plainText;
					if (type == TYPE_BOOK || type == TYPE_MAGAZINE) {
						data.infoLog = "Publication is to be a " + type + ".";
						++step;
					}
					else {
						data.errorLog = "Invalid publication type (must be Book or Magazine).";
					}
				}
				else {
					data.errorLog = "Expected numeric input for the next field.";
				}
			}
			else {
				if (step == stepPrice && isDouble(input.plainText)) {
					price = stod(input.plainText);
					data.infoLog = "Set price to " + to_string(price) + ".";
					++step;
				}
			}
		}

		system("cls");
	} while (!data.leave);
}
	

void Controller222(const Page& page)
{
	// (2.2.2) Reform an old Publication
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the name of the publication you want to remove.\n";
	data.instructions += "Press enter to confirm and reform the publication.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl;

			if (data.chosen.publication != nullptr) {
				cout << "\n >>>> You have selected the following publication for removal:\n\n";
				cout << Writer::writePublicationDetails(data.company, data.chosen.publication) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (data.chosen.publication != nullptr) {
				data.chosen.publication = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.publication != nullptr) {
				string name = data.chosen.publication->getName();
				bool success = data.company->removePublication(data.chosen.publication);
				if (success) {
					data.infoLog = "Successfully reformed the publication " + name + ".";
					data.chosen.publication = nullptr;
				}
				else {
					data.errorLog = "Failed to reform publication " + name + ".";
				}
			}
			else {
				data.errorLog = "No publication selected.";
			}
		}
		if (input.is.integer) {
			data.errorLog = "Expected a publication name.";
		}
		if (input.is.plainText) {
			Publication* publication = data.company->getPublication(input.plainText);
			if (publication != nullptr) {
				data.chosen.publication = publication;
				data.infoLog = "Selected publication " + input.plainText + " for removal. Press enter to confirm.";
			}
			else {
				data.errorLog = "Publication with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}



void Controller231(const Page& page)
{
	// (2.3.1) Add an Employee
	ManagerData data(page);

	string employeeName;
	bool name = false;

	Date birthDate = Date::randomBirthDate();

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Birth date chosen randomly. Change year by writing an integer.\n";
	data.instructions += "Or just press enter to randomize another date completely.\n";
	data.instructions += "Chosen the birth date, write the employee's name.\n";
	data.instructions += "Then just press enter to add the new employee!\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeEmployees(data.company) << endl;

			cout << encaps(" § Employee Information § ", SHORT_WIDTH, '=') + "\n";

			cout << " >> Date of Birth: ";
			cout << birthDate << endl;
					
			cout << " >> Employee's Name: ";
			if (name) cout << employeeName;
			cout << endl;

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (name) {
				name = false;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (name) {
				Employee* employee = new Employee(data.company, employeeName, birthDate);
				bool success = data.company->addEmployee(employee);
				if (success) {
					data.infoLog = "Successfully created employee '" + employeeName + "'.";
					name = false; birthDate = Date::randomBirthDate();
				}
				else {
					data.errorLog = "Invalid employee information: an employee with the same name already exists.";
					name = false;
					delete employee;
				}
			}
			else {
				birthDate = Date::randomBirthDate();
			}
		}
		if (input.is.integer) {
			Date::Year year = input.integer;
			if (year >= 1920 && year <= 2010) {
				birthDate.setYear(year);
				data.infoLog = "Changed employee's birth year to " + to_string(year) + ".";
			}
			else {
				data.infoLog = "Invalid birth year, choose one in the range [1920...2010].";
			}
		}
		if (input.is.plainText) {
			employeeName = input.plainText;
			data.infoLog = "Set employee's name to " + employeeName + ".";
			name = true;
		}

		system("cls");
	} while (!data.leave);
}


void Controller232(const Page& page)
{
	// (2.3.2) Designate an Employee to a store
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write in any order:\n";
	data.instructions += "  The name of the employee you want to designate;\n";
	data.instructions += "  The name of the store you want to designate him to.\n";
	data.instructions += "Then just press enter to confirm.\n";
	data.instructions += "Note this will overwrite previous work designations.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeEmployees(data.company, data.chosen.employee) << endl;
			cout << Writer::writeStores(data.company, data.chosen.store) << endl << endl;

			if (data.chosen.employee != nullptr) {
				cout << " >>>> Selected Employee: " << data.chosen.employee->getName() << endl;
			}
			
			if (data.chosen.store != nullptr) {
				cout << " >>>> Selected Store: " << data.chosen.store->getName() << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (data.chosen.employee != nullptr) {
				data.chosen.employee = nullptr;
			}
			else if (data.chosen.store != nullptr) {
				data.chosen.store = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.store != nullptr && data.chosen.employee != nullptr) {
				bool success = data.company->designateEmployee(data.chosen.store, data.chosen.employee);
				if (success) {
					data.infoLog = "Designated employee " + data.chosen.employee->getName() + \
						" to store " + data.chosen.store->getName() + ".";
					data.chosen.employee = nullptr;
					data.chosen.store = nullptr;
				}
			}
			else {
				if (data.chosen.employee == nullptr) {
					data.errorLog = "No employee selected";
				}
				else if (data.chosen.store == nullptr) {
					data.errorLog = "No store selected.";
				}
			}
		}
		if (input.is.integer) {
			data.errorLog = "Expected a store or employee name.";
		}
		if (input.is.plainText) {
			Employee* employee = data.company->getEmployee(input.plainText);
			if (employee != nullptr) {
				data.chosen.employee = employee;
				data.infoLog = "Selected employee " + input.plainText + ".";
			}
			else {
				Store* store = data.company->getStore(input.plainText);
				if (store != nullptr) {
					data.chosen.store = store;
					data.infoLog = "Selected store " + input.plainText + ".";
				}
				else {
					data.errorLog = "Employee or store with name '" + input.plainText + "' not found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller233(const Page& page)
{
	// (2.3.3) Reform an Employee
	ManagerData data(page);

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the name of the employee you want to reform.\n";
	data.instructions += "Press enter to confirm and reform the employee.\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeEmployees(data.company, data.chosen.employee) << endl;
			
			if (data.chosen.employee != nullptr) {
				cout << "\n >>>> You have selected the following employee for removal:\n\n";
				cout << Writer::writeEmployeeDetails(data.company, data.chosen.employee) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (data.chosen.employee != nullptr) {
				data.chosen.employee = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.employee != nullptr) {
				string name = data.chosen.employee->getName();
				bool success = data.company->removeEmployee(data.chosen.employee);
				if (success) {
					data.infoLog = "Successfully removed the employee " + name + ".";
					data.chosen.employee = nullptr;
				}
				else {
					data.errorLog = "Failed to remove employee " + name + ".";
				}
			}
			else {
				data.errorLog = "No employee selected.";
			}
		}
		if (input.is.integer) {
			data.errorLog = "Expected an employee name.";
		}
		if (input.is.plainText) {
			Employee* employee = data.company->getEmployee(input.plainText);
			if (employee != nullptr) {
				data.chosen.employee = employee;
				data.infoLog = "Selected employee " + input.plainText + " for removal. Press enter to confirm.";
			}
			else {
				data.errorLog = "Employee with name '" + input.plainText + "' not found.";
			}
		}

		system("cls");
	} while (!data.leave);
}





void Controller31(const Page& page)
{
	// (3.1) Create Stock Requests
	ManagerData data(page);
	// Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit);

	unsigned int reqQuantity, reqDeadline = DEFAULT_REQUEST_DEADLINE;
	bool quantity = false, deadline = false;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write the name of the publication and the name\n";
	data.instructions += " of the store you want to request stock for.\n";
	data.instructions += "Then write in order the number of copies and the production deadline\n";
	data.instructions += " (how many days production has to produce these copies (deadline).\n";
	data.instructions += "Once done, just press enter to add the stock request!\n";

	do {
		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;
			
			if (data.chosen.publication != nullptr) {
				cout << " >>>> Chosen Publication: " << data.chosen.publication->getName() << endl;
			}

			if (data.chosen.store != nullptr) {
				cout << " >>>> Chosen Store: " << data.chosen.store->getName() << endl;
			}

			cout << " >> Number of copies: ";
			if (quantity) cout << reqQuantity;
			cout << endl;

			Date dateLimit = data.company->today() + reqDeadline;
			cout << " >> Deadline: (" << reqDeadline << ") - Day " << dateLimit << endl;

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (deadline) {
				deadline = false;
				reqDeadline = DEFAULT_REQUEST_DEADLINE;
			}
			else if (quantity) {
				quantity = false;
			}
			else if (data.chosen.store != nullptr) {
				data.chosen.store = nullptr;
			}
			else if (data.chosen.publication != nullptr) {
				data.chosen.publication = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (quantity && data.chosen.publication != nullptr && data.chosen.store != nullptr) {
				Date dateLimit = data.company->today() + reqDeadline;
				Request* request = new Request(data.company, data.chosen.publication, data.chosen.store, reqQuantity, dateLimit);
				bool success = data.company->addRequest(request);
				if (success) {
					data.infoLog = "Successfully added request.";
					deadline = false;
					reqDeadline = DEFAULT_REQUEST_DEADLINE;
					quantity = false;
					data.chosen.store = nullptr;
				}
				else {
					data.errorLog = "Unsuccessful request.";
				}
			}
			else {
				if (data.chosen.publication == nullptr) {
					data.errorLog = "Please choose a publication first.";
				}
				else if (data.chosen.store == nullptr) {
					data.errorLog = "Please choose a store first.";
				}
				else if (!quantity) {
					data.errorLog = "Please write the number of copies requested first.";
				}
			}
		}
		if (input.is.integer) {
			if (quantity) {
				reqDeadline = input.integer;
				Date dateLimit = data.company->today() + reqDeadline;
				data.infoLog = "Changed deadline to " + to_string(reqDeadline) + " days from today (" + dateLimit.write() + ").";
				deadline = true;
			}
			else {
				reqQuantity = input.integer;
				data.infoLog = "Set quantity to " + to_string(reqQuantity) + ".";
				quantity = true;
			}
		}
		if (input.is.plainText) {
			Publication* publication = data.company->getPublication(input.plainText);
			if (publication != nullptr) {
				data.chosen.publication = publication;
				data.infoLog = "Selected publication " + input.plainText + ".";
			}
			else {
				Store* store = data.company->getStore(input.plainText);
				if (store != nullptr) {
					data.chosen.store = store;
					data.infoLog = "Selected store " + input.plainText + ".";
				}
				else {
					data.errorLog = "Publication or store with name '" + input.plainText + "' not found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller32(const Page& page)
{
	// (3.2) Delete (pending) Stock Requests
	ManagerData data(page);

	vector<Request*> reqVector;
	unsigned int index = 0;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication or store name to filter requests.\n";
	data.instructions += "Write the request's index in the table to select it.\n";
	data.instructions += "Just press enter to confirm delection.\n";

	do {
		// 0. Load request vector
		{
			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				reqVector = data.company->getRequests();
			else if (data.chosen.publication != nullptr)
				reqVector = data.chosen.publication->getRequests();
			else if (data.chosen.store != nullptr)
				reqVector = data.chosen.store->getRequests();
		}

		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, index);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.publication, index);
			else if (data.chosen.store != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.store, index);

			if (data.chosen.request != nullptr) {
				cout << "\n >>>> You have selected the following request for removal:\n\n";
				cout << Writer::writeRequest(data.company, data.chosen.request) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (index > 0) {
				index = 0; data.chosen.request = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.request != nullptr) {
				bool success = data.company->removeRequest(data.chosen.request);
				if (success) {
					data.infoLog = "Successfully removed the request.";
					index = 0; data.chosen.request = nullptr;
				}
				else {
					data.errorLog = "Failed to remove the request.";
				}
			}
			else {
				data.errorLog = "No request selected.";
			}
		}
		if (input.is.integer) {
			unsigned uns = input.integer;
			if (input.integer > 0 && uns <= reqVector.size()) {
				index = uns;
				data.chosen.request = reqVector[index - 1];
				data.infoLog = "Chose request #" + to_string(index) + ".";
			}
			else {
				data.errorLog = "No request with that index.";
			}
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				index = 0; data.chosen.request = nullptr;
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					index = 0; data.chosen.request = nullptr;
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller33(const Page& page)
{
	// (3.3) Suspend (pending) Stock Requests
	ManagerData data(page);

	vector<Request*> reqVector;
	unsigned int index = 0;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication or store name to filter requests.\n";
	data.instructions += "Write the request's index in the table to select it.\n";
	data.instructions += "Just press enter to confirm suspension.\n";

	do {
		// 0. Load request vector
		{
			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				reqVector = data.company->getRequests();
			else if (data.chosen.publication != nullptr)
				reqVector = data.company->getRequests(data.chosen.publication);
			else if (data.chosen.store != nullptr)
				reqVector = data.company->getRequests(data.chosen.store);
		}

		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, index);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.publication, index);
			else if (data.chosen.store != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.store, index);

			if (data.chosen.request != nullptr) {
				cout << "\n >>>> You have selected the following request for suspension:\n\n";
				cout << Writer::writeRequest(data.company, data.chosen.request) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (index > 0) {
				index = 0; data.chosen.request = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.request != nullptr) {
				bool success = data.company->suspendRequest(data.chosen.request);
				if (success) {
					data.infoLog = "Successfully suspended the request.";
					index = 0; data.chosen.request = nullptr;
				}
				else {
					data.errorLog = "Failed to suspend the request.";
				}
			}
			else {
				data.errorLog = "No request selected.";
			}
		}
		if (input.is.integer) {
			unsigned uns = input.integer;
			if (input.integer > 0 && uns <= reqVector.size()) {
				index = uns;
				data.chosen.request = reqVector[index - 1];
				data.infoLog = "Chose request #" + to_string(index) + ".";
			}
			else {
				data.errorLog = "No request with that index.";
			}
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				index = 0; data.chosen.request = nullptr;
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					index = 0; data.chosen.request = nullptr;
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller34(const Page& page)
{
	// (3.4) End suspension of Stock Requests
	ManagerData data(page);

	vector<Suspended*> susVector;
	unsigned int index = 0;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication or store name to filter suspended requests.\n";
	data.instructions += "Write the suspended request's index in the table to select it.\n";
	data.instructions += "Just press enter to confirm the end of suspension.\n";

	do {
		// 0. Load suspended vector
		{
			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				susVector = data.company->getSuspendedRequests();
			else if (data.chosen.publication != nullptr)
				susVector = data.company->getSuspendedRequests(data.chosen.publication);
			else if (data.chosen.store != nullptr)
				susVector = data.company->getSuspendedRequests(data.chosen.store);
		}

		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, index);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, data.chosen.publication, index);
			else if (data.chosen.store != nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, data.chosen.store, index);

			if (data.chosen.suspended != nullptr) {
				cout << "\n >>>> You have selected to end the suspension of the following request:\n\n";
				cout << Writer::writeSuspended(data.company, data.chosen.suspended) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (index > 0) {
				index = 0; data.chosen.suspended = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.suspended != nullptr) {
				bool success = data.company->endSuspension(data.chosen.suspended);
				if (success) {
					data.infoLog = "Successfully ended suspension of the request.";
					index = 0; data.chosen.suspended = nullptr;
				}
				else {
					data.errorLog = "Failed to end the suspension.";
				}
			}
			else {
				data.errorLog = "No suspended request selected.";
			}
		}
		if (input.is.integer) {
			unsigned uns = input.integer;
			if (input.integer > 0 && uns <= susVector.size()) {
				index = uns;
				data.chosen.suspended = susVector[index - 1];
				data.infoLog = "Chose suspended request #" + to_string(index) + ".";
			}
			else {
				data.errorLog = "No suspended request with that index.";
			}
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				index = 0; data.chosen.suspended = nullptr;
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for suspended requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					index = 0; data.chosen.suspended = nullptr;
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for suspended requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller35(const Page& page)
{
	// (3.5) Remove suspended Stock Requests
	ManagerData data(page);

	vector<Suspended*> susVector;
	unsigned int index = 0;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication or store name to filter suspended requests.\n";
	data.instructions += "Write the suspended request's index in the table to select it.\n";
	data.instructions += "Just press enter to confirm the removal.\n";

	do {
		// 0. Load suspended vector
		{
			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				susVector = data.company->getSuspendedRequests();
			else if (data.chosen.publication != nullptr)
				susVector = data.company->getSuspendedRequests(data.chosen.publication);
			else if (data.chosen.store != nullptr)
				susVector = data.company->getSuspendedRequests(data.chosen.store);
		}

		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, index);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, data.chosen.publication, index);
			else if (data.chosen.store != nullptr)
				cout << Writer::writeSuspendedNumbered(susVector, data.chosen.store, index);

			if (data.chosen.suspended != nullptr) {
				cout << "\n >>>> You have selected the following suspended request for removal:\n\n";
				cout << Writer::writeSuspended(data.company, data.chosen.suspended) << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (index > 0) {
				index = 0; data.chosen.suspended = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.suspended != nullptr) {
				bool success = data.company->removeSuspended(data.chosen.suspended);
				if (success) {
					data.infoLog = "Successfully removed suspended request.";
					index = 0; data.chosen.suspended = nullptr;
				}
				else {
					data.errorLog = "Failed to remove the suspended request.";
				}
			}
			else {
				data.errorLog = "No suspended request selected.";
			}
		}
		if (input.is.integer) {
			unsigned uns = input.integer;
			if (input.integer > 0 && uns <= susVector.size()) {
				index = uns;
				data.chosen.suspended = susVector[index - 1];
				data.infoLog = "Chose suspended request #" + to_string(index) + ".";
			}
			else {
				data.errorLog = "No suspended request with that index.";
			}
		}
		if (input.is.plainText) {
			Store* store = data.company->getStore(input.plainText);
			if (store != nullptr) {
				index = 0; data.chosen.suspended = nullptr;
				data.chosen.store = store;
				data.chosen.publication = nullptr;
				data.infoLog = "Filtered table for suspended requests from store '" + input.plainText + "'.";
			}
			else {
				Publication* publication = data.company->getPublication(input.plainText);
				if (publication != nullptr) {
					index = 0; data.chosen.suspended = nullptr;
					data.chosen.store = nullptr;
					data.chosen.publication = publication;
					data.infoLog = "Filtered table for suspended requests of publication '" + input.plainText + "'.";
				}
				else {
					data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
				}
			}
		}

		system("cls");
	} while (!data.leave);
}


void Controller36(const Page& page)
{
	// (3.6) Postpone Stock Requests deadlines
	ManagerData data(page);

	vector<Request*> reqVector;
	unsigned int index = 0;

	unsigned int reqDeadline = DEFAULT_REQUEST_DEADLINE;

	data.instructions += "Ctrl+Z = Leave to page " + page.father + "\n";
	data.instructions += "Write a publication or store name to filter requests.\n";
	data.instructions += "Write the request's index in the table to select it.\n";
	data.instructions += "Choose the new production deadline (how many days from today).\n";
	data.instructions += "Press enter to confirm alteration.\n";
	data.instructions += "Press Ctrl+Z to cancel alteration.\n";

	do {
		// 0. Load request vector
		{
			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				reqVector = data.company->getRequests();
			else if (data.chosen.publication != nullptr)
				reqVector = data.chosen.publication->getRequests();
			else if (data.chosen.store != nullptr)
				reqVector = data.chosen.store->getRequests();
		}

		// 1. Write Page Content
		{
			cout << page.mainContent << endl;

			// Write Page Content
			cout << Writer::writeStores(data.company, data.chosen.store) << endl;
			cout << Writer::writePublications(data.company, data.chosen.publication) << endl << endl;

			if (data.chosen.store == nullptr && data.chosen.publication == nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, index);
			else if (data.chosen.publication != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.publication, index);
			else if (data.chosen.store != nullptr)
				cout << Writer::writeRequestsNumbered(reqVector, data.chosen.store, index);

			if (data.chosen.request != nullptr) {
				cout << "\n >>>> You have selected the following request for alteration:\n\n";
				cout << Writer::writeRequest(data.company, data.chosen.request) << endl;

				Date dateLimit = data.company->today() + reqDeadline;
				cout << " >> New Deadline: (" << reqDeadline << ") - " << dateLimit << endl;
			}

			cout << endl << endl;
			cout << Aux::writeLogs(data);
			Aux::clear(data);
		}

		// 2. Wait User input
		Input input = data.reader.extract();

		// 3. Check User input
		if (input.is.ctrlZ) {
			if (index > 0) {
				index = 0; data.chosen.request = nullptr;
			}
			else {
				data.nextPage = page.father;
				data.leave = true;
			}
		}
		if (input.is.freeEnter) {
			if (data.chosen.request != nullptr) {
				Date dateLimit = data.company->today() + reqDeadline;
				bool success = data.company->setRequestDeadline(data.chosen.request, dateLimit);
				if (success) {
					data.infoLog = "Successfully modified the request.";
					index = 0; data.chosen.request = nullptr;
				}
				else {
					data.errorLog = "Failed to modify the request.";
				}
			}
			else {
				data.errorLog = "No request selected.";
			}
		}
		if (input.is.integer) {
			if (data.chosen.request != nullptr) {
				reqDeadline = input.integer;
			}
			else {
				unsigned uns = input.integer;
				if (input.integer > 0 && uns <= reqVector.size()) {
					index = uns;
					data.chosen.request = reqVector[index - 1];
					data.infoLog = "Chose request #" + to_string(index) + ".";
				}
				else {
					data.errorLog = "No request with that index.";
				}
			}
		}
		if (input.is.plainText) {
			if (data.chosen.request != nullptr) {
				data.errorLog = "Please confirm or cancel the deadline modification first.";
			}
			else {
				Store* store = data.company->getStore(input.plainText);
				if (store != nullptr) {
					data.chosen.store = store;
					data.chosen.publication = nullptr;
					data.infoLog = "Filtered table for requests from store '" + input.plainText + "'.";
				}
				else {
					Publication* publication = data.company->getPublication(input.plainText);
					if (publication != nullptr) {
						data.chosen.store = nullptr;
						data.chosen.publication = publication;
						data.infoLog = "Filtered table for requests of publication '" + input.plainText + "'.";
					}
					else {
						data.errorLog = "No store or publication with name '" + input.plainText + "' was found.";
					}
				}
			}
		}

		system("cls");
	} while (!data.leave);
}
}