// ****************************************************************************************************
// ******************************************* FILES_CPP__ ********************************************
// ****************************************************************************************************
#include "Company.h"
#include "Store.h"
#include "Employee.h"
#include "Request.h"

#include "Exceptions.h"
#include "Console.h"
#include "Supplements.h"

#include <iostream>
#include <fstream>




void Company::getStoresFile(bool output) {
	cout << menu->writeLog();
	cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a stores file)\n";
	cout << "Stores information file name (press Enter for default: ";
	cout << DEFAULT_STORES_FILE;
	cout << "): ";

	string fileName;
	getline(cin, fileName);
	if (cin && trim(fileName).length() == 0) {
		fileName = DEFAULT_STORES_FILE;
	}
	cin.clear();
	if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
		system("cls");
		string consoleLog = "Stores information data file not read.";
		menu->consoleLog.push_back(consoleLog);
		storesFileName = DEFAULT_SKIP_SYMBOL;
		return;
	}

	fstream file(trim(fileName), output ? ios::out : ios::in);

	if (!file.is_open()) {
		do {
			file.clear();
			cout << "File '" + trim(fileName) + "' could not be opened.\n";
			cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a stores file)\n";
			cout << "Stores information file name: ";

			getline(cin, fileName);
			if (cin && trim(fileName).length() == 0) {
				fileName = DEFAULT_STORES_FILE;
			}
			cin.clear();
			if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
				system("cls");
				string consoleLog = "Stores information data file not read.";
				menu->consoleLog.push_back(consoleLog);
				storesFileName = DEFAULT_SKIP_SYMBOL;
				return;
			}

			file.open(trim(fileName), output ? ios::out : ios::in);
		} while (!file.is_open());
	}

	system("cls");
	file.close();

	string consoleLog = "Stores information data file selected: '" + trim(fileName) + "'.";
	menu->consoleLog.push_back(consoleLog);

	storesFileName = trim(fileName);
}


void Company::getPublicationsFile(bool output) {
	cout << menu->writeLog();
	cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a collections file)\n";
	cout << "Collections information file name (press Enter for default: ";
	cout << DEFAULT_PUBLICATIONS_FILE;
	cout << "): ";

	string fileName;
	getline(cin, fileName);
	if (cin && trim(fileName).length() == 0) {
		fileName = DEFAULT_PUBLICATIONS_FILE;
	}
	cin.clear();
	if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
		system("cls");
		string consoleLog = "Collections information data file not read.";
		menu->consoleLog.push_back(consoleLog);
		publicationsFileName = DEFAULT_SKIP_SYMBOL;
		return;
	}

	fstream file(trim(fileName), output ? ios::out : ios::in);

	if (!file.is_open()) {
		do {
			file.clear();
			cout << "File '" + trim(fileName) + "' could not be opened.\n";
			cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a collections file)\n";
			cout << "Collections information file name: ";

			getline(cin, fileName);
			if (cin && trim(fileName).length() == 0) {
				fileName = DEFAULT_PUBLICATIONS_FILE;
			}
			cin.clear();
			if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
				system("cls");
				string consoleLog = "Collections information data file not read.";
				menu->consoleLog.push_back(consoleLog);
				publicationsFileName = DEFAULT_SKIP_SYMBOL;
				return;
			}

			file.open(trim(fileName), output ? ios::out : ios::in);
		} while (!file.is_open());
	}

	system("cls");
	file.close();

	string consoleLog = "Collections information data file selected: '" + trim(fileName) + "'.";
	menu->consoleLog.push_back(consoleLog);

	publicationsFileName = trim(fileName);
}


void Company::getEmployeesFile(bool output) {
	cout << menu->writeLog();
	cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a employees file)\n";
	cout << "Employees information file name (press Enter for default: ";
	cout << DEFAULT_EMPLOYEES_FILE;
	cout << "): ";

	string fileName;
	getline(cin, fileName);
	if (cin && trim(fileName).length() == 0) {
		fileName = DEFAULT_EMPLOYEES_FILE;
	}
	cin.clear();
	if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
		system("cls");
		string consoleLog = "Employees information data file not read.";
		menu->consoleLog.push_back(consoleLog);
		employeesFileName = DEFAULT_SKIP_SYMBOL;
		return;
	}

	fstream file(trim(fileName), output ? ios::out : ios::in);

	if (!file.is_open()) {
		do {
			file.clear();
			cout << "File '" + trim(fileName) + "' could not be opened.\n";
			cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a employees file)\n";
			cout << "Employees information file name: ";

			getline(cin, fileName);
			if (cin && trim(fileName).length() == 0) {
				fileName = DEFAULT_EMPLOYEES_FILE;
			}
			cin.clear();
			if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
				system("cls");
				string consoleLog = "Employees information data file not read.";
				menu->consoleLog.push_back(consoleLog);
				employeesFileName = DEFAULT_SKIP_SYMBOL;
				return;
			}

			file.open(trim(fileName), output ? ios::out : ios::in);
		} while (!file.is_open());
	}

	system("cls");
	file.close();

	string consoleLog = "Employees information data file selected: '" + trim(fileName) + "'.";
	menu->consoleLog.push_back(consoleLog);

	employeesFileName = trim(fileName);
}


void Company::getRequestsFile(bool output) {
	cout << menu->writeLog();
	cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a requests file)\n";
	cout << "Requests information file name (press Enter for default: ";
	cout << DEFAULT_REQUESTS_FILE;
	cout << "): ";

	string fileName;
	getline(cin, fileName);
	if (cin && trim(fileName).length() == 0) {
		fileName = DEFAULT_REQUESTS_FILE;
	}
	cin.clear();
	if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
		system("cls");
		string consoleLog = "Requests information data file not read.";
		menu->consoleLog.push_back(consoleLog);
		requestsFileName = DEFAULT_SKIP_SYMBOL;
		return;
	}

	fstream file(trim(fileName), output ? ios::out : ios::in);

	if (!file.is_open()) {
		do {
			file.clear();
			cout << "File '" + trim(fileName) + "' could not be opened.\n";
			cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a requests file)\n";
			cout << "Requests information file name: ";

			getline(cin, fileName);
			if (cin && trim(fileName).length() == 0) {
				fileName = DEFAULT_REQUESTS_FILE;
			}
			cin.clear();
			if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
				system("cls");
				string consoleLog = "Requests information data file not read.";
				menu->consoleLog.push_back(consoleLog);
				requestsFileName = DEFAULT_SKIP_SYMBOL;
				return;
			}

			file.open(trim(fileName), output ? ios::out : ios::in);
		} while (!file.is_open());
	}

	system("cls");
	file.close();

	string consoleLog = "Requests information data file selected: '" + trim(fileName) + "'.";
	menu->consoleLog.push_back(consoleLog);

	requestsFileName = trim(fileName);
}


void Company::getSuspendedRequestsFile(bool output) {
	cout << menu->writeLog();
	cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a requests file)\n";
	cout << "Requests information file name (press Enter for default: ";
	cout << DEFAULT_SUSPENDED_REQUESTS_FILE;
	cout << "): ";

	string fileName;
	getline(cin, fileName);
	if (cin && trim(fileName).length() == 0) {
		fileName = DEFAULT_SUSPENDED_REQUESTS_FILE;
	}
	cin.clear();
	if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
		system("cls");
		string consoleLog = "Requests information data file not read.";
		menu->consoleLog.push_back(consoleLog);
		requestsFileName = DEFAULT_SKIP_SYMBOL;
		return;
	}

	fstream file(trim(fileName), output ? ios::out : ios::in);

	if (!file.is_open()) {
		do {
			file.clear();
			cout << "File '" + trim(fileName) + "' could not be opened.\n";
			cout << "  (Write " << DEFAULT_SKIP_SYMBOL << " to skip opening a requests file)\n";
			cout << "Requests information file name: ";

			getline(cin, fileName);
			if (cin && trim(fileName).length() == 0) {
				fileName = DEFAULT_SUSPENDED_REQUESTS_FILE;
			}
			cin.clear();
			if (trim(fileName) == DEFAULT_SKIP_SYMBOL) {
				system("cls");
				string consoleLog = "Requests information data file not read.";
				menu->consoleLog.push_back(consoleLog);
				requestsFileName = DEFAULT_SKIP_SYMBOL;
				return;
			}

			file.open(trim(fileName), output ? ios::out : ios::in);
		} while (!file.is_open());
	}

	system("cls");
	file.close();

	string consoleLog = "Requests information data file selected: '" + trim(fileName) + "'.";
	menu->consoleLog.push_back(consoleLog);

	suspendedRequestsFileName = trim(fileName);
}




void Company::readStoresFile() {
	ifstream file(storesFileName);
	assert(file.is_open());
	string text, block;

	while (!file.eof()) {
		getline(file, text);
		block += text + "\n";

		if (trim(text).length() == 0 && trim(block).length() > 0) {
			Store* store = new Store(trim(block), this);
			addStore(store);
			block.clear();
		}
	}

	file.close();
	menu->consoleLog.push_back("Stores information read from '" + storesFileName + "'.");
}


void Company::readPublicationsFile() {
	ifstream file(publicationsFileName);
	assert(file.is_open());

	while (!file.eof()) {
		string block;
		getline(file, block);

		if (trim(block).length() > 0) {
			try {
				Publication* publication = new Publication(trim(block), this);
				if (publication->getType() == TYPE_BOOK) {
					Book* book = new Book(trim(block), this);
					addPublication(book);
				}
				else if (publication->getType() == TYPE_MAGAZINE) {
					Magazine* mag = new Magazine(trim(block), this);
					addPublication(mag);
				}
				else throw MalformedFileItem<Publication>(publication, "Invalid type");

				delete publication;
			}
			catch (MalformedFileItem<Publication> error) {
				menu->consoleLog.push_back("Malformed publication header text (Error: " + error.message() + ")");
				// ....
			}
		}
	}
	file.close();
	menu->consoleLog.push_back("Publications information read from '" + publicationsFileName + "'.");
}


void Company::readEmployeesFile() {
	ifstream file(employeesFileName);
	assert(file.is_open());

	while (!file.eof()) {
		string text;
		getline(file, text);

		if (trim(text).length() > 0) {
			Employee* employee = new Employee(trim(text), this);
			addEmployee(employee);
		}
	}

	file.close();
	menu->consoleLog.push_back("Employees information read from '" + employeesFileName + "'.");
}


void Company::readRequestsFile() {
	ifstream file(requestsFileName);
	assert(file.is_open());

	while (!file.eof()) {
		string text;
		getline(file, text);

		if (trim(text).length() > 0) {
			Request* request = new Request(trim(text), this);
			addRequest(request);
		}
	}

	file.close();
	menu->consoleLog.push_back("Requests information read from '" + requestsFileName + "'.");
}

void Company::readSuspendedRequestsFile() {
	ifstream file(suspendedRequestsFileName);
	assert(file.is_open());

	while (!file.eof()) {
		string text;
		getline(file, text);

		if (trim(text).length() > 0) {
			Suspended* suspended = new Suspended(trim(text), this);
			addSuspendedRequest(suspended);
		}
	}

	file.close();
	menu->consoleLog.push_back("Requests information read from '" + suspendedRequestsFileName + "'.");
}




void Company::saveStoresToFile() {
	getStoresFile(true);
	ofstream file(storesFileName);
	string text;
	assert(file.is_open());

	for (auto it = stores.cbegin(); it != stores.cend(); ++it) {
		if (it != stores.cbegin()) file << endl;
		file << (*it)->writeToFile();
	}
	file.close();
	menu->consoleLog.push_back("Stores information saved to '" + storesFileName + "'.");
}


void Company::savePublicationsToFile() {
	getPublicationsFile(true);
	ofstream file(publicationsFileName);
	string text;
	assert(file.is_open());

	for (auto it = publications.cbegin(); it != publications.cend(); ++it) {
		if (it != publications.cbegin()) file << endl;
		file << (*it)->writeToFile();
	}
	file.close();
	menu->consoleLog.push_back("Collections information saved to '" + publicationsFileName + "'.");
}


void Company::saveEmployeesToFile() {
	getEmployeesFile(true);
	ofstream file(employeesFileName);
	string text;
	assert(file.is_open());

	for (auto it = employees.cbegin(); it != employees.cend(); ++it) {
		if (it != employees.cbegin()) file << endl;
		file << (*it)->writeToFile();
	}
	file.close();
	menu->consoleLog.push_back("Employees information saved to '" + employeesFileName + "'.");
}


void Company::saveRequestsToFile() {
	getRequestsFile(true);
	ofstream file(requestsFileName);
	string text;
	assert(file.is_open());

	for (auto it = productionPlan.cbegin(); it != productionPlan.cend(); ++it) {
		if (it != productionPlan.cbegin()) file << endl;
		file << (*it)->writeToFile();
	}
	file.close();
	menu->consoleLog.push_back("Requests information saved to '" + requestsFileName + "'.");
}

void Company::saveSuspendedRequestsToFile() {
	getSuspendedRequestsFile(true);
	ofstream file(suspendedRequestsFileName);
	string text;
	assert(file.is_open());

	for (auto it = suspendedRequests.cbegin(); it != suspendedRequests.cend(); ++it) {
		if (it != suspendedRequests.cbegin()) file << endl;
		file << (*it)->writeToFile();
	}
	file.close();
	menu->consoleLog.push_back("Requests information saved to '" + suspendedRequestsFileName + "'.");
}