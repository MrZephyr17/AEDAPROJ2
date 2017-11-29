#pragma once

#include "Classes.h"
#include "Date.h"
/**
* @brief The class harbors all the information about the collections,employees,stores and requests.
*/
class Company
{
private:
	vector<Store*> stores;
	vector<Employee*> employees;
	vector<Request*> productionPlan;
	vector<Collection*> collections;
	string storesFileName, collectionsFileName, employeesFileName, requestsFileName;

	Menu* menu;
	Date currentDay = DEFAULT_CURRENT_DAY;

public:
	// ~Company();

	// (Init.cpp) 
	/**
	* @brief  Main function inside Company object.
	*
	* Reads files, initiates menu, and exits the program when necessary.
	*/
	void init();

	/**
	* @brief Initiates the main user interface.
	*
	* Stores in form of strings the information that is to be shown to the user
	* as part of the interface, as in all the pages and sub-pages.
	*/
	void initMenu();

	// (Files.cpp) Get fileNames.
	/**
	* @brief Gets the stores file name from the user.
	*
	* Asks the user to enter a stores file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output  ???
	*
	*/
	void getStoresFile(bool output = false);

	/**
	* @brief Gets the collections and publications file name from the user.
	*
	* Asks the user to enter a collections file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output
	*
	*/
	void getCollectionsFile(bool output = false);

	/**
	* @brief Gets the employees file name from the user.
	*
	* Asks the user to enter an employees file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output
	*
	*/
	void getEmployeesFile(bool output = false);

	/**
	* @brief Gets the requests file name from the user.
	*
	* Asks the user to enter a requests file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output
	*
	*/
	void getRequestsFile(bool output = false);

	// (Files.cpp) Read files and initialize vectors.
	/**
	* @brief Reads the stores file previously provided.
	*
	* Reads the stores file and, in case it is correctly formated, creates stores objects
	* and stores them its vector.
	*/
	void readStoresFile();

	/**
	* @brief Reads the collections file previously provided.
	*
	* Reads the collections file and, in case it is correctly formated, creates collections objects
	* and stores them its vector.
	*/
	void readCollectionsFile();

	/**
	* @brief Reads the employees file previously provided.
	*
	* Reads the employees file and, in case it is correctly formated, creates employees objects
	* and stores them its vector.
	*/
	void readEmployeesFile();

	/**
	* @brief Reads the requests file previously provided.
	*
	* Reads the requests file and, in case it is correctly formated, creates requests objects
	* and stores them its vector.
	*/
	void readRequestsFile();

	// (Files.cpp) Read vectors and save to files.

	/**
	* @brief Saves the stores objects to their file.
	*
	* Saves the stores in the same format as they were read and to the same file.
	*/
	void saveStoresToFile();

	/**
	* @brief Saves the collections objects to their file.
	*
	* Saves the collections in the same format as they were read and to the same file.
	*/
	void saveCollectionsToFile();

	/**
	* @brief Saves the employees objects to their file.
	*
	* Saves the employees in the same format as they were read and to the same file.
	*/
	void saveEmployeesToFile();

	/**
	* @brief Saves the requests objects to their file.
	*
	* Saves the requests in the same format as they were read and to the same file.
	*/
	void saveRequestsToFile();

	// (Company.cpp) Add newly created object and update all other objects.
	// Incomplete
	/**

	* @brief  Add newly created store and update all other stores.
	* @param newS the new Store to be added.
	*/
	void addStore(Store* newS);

	/**
	* @brief  Add newly created collection and update all other collections.
	* @param newC the new Collection to be added.
	*/
	void addCollection(Collection* newC);
	/**
	* @brief  Add newly created employee and update all other employees.
	* @param newE the new Employee to be added.
	*/
	void addEmployee(Employee* newE);
	/**
	* @brief  Add newly created request and update all other requests.
	* @param newR the new Request to be added.
	*/
	void addRequest(Request* newR);

	// (Company.cpp) Remove existing object and update all other objects.
	// Incomplete


	/**
	* @brief  Remove existing store and update all other stores.
	* @param store the Store to be removed.
	*/
	void removeStore(Store* store);
	/**
	* @brief  Remove existing collection and update all other collections.
	* @param collection the Collection to be removed.
	*/
	void removeCollection(Collection* collection);
	/**
	* @brief  Remove existing employee and update all other employees.
	* @param employee the Employee to be removed.
	*/
	void removeEmployee(Employee* employee);
	/**
	* @brief  Remove existing request and update all other requests.
	* @param request the Request to be removed.
	*/
	void removeRequest(Request* request);

	// (Company.cpp) Gets

	/**
	* @brief Gets a store with the provided name.
	*
	* Making use of a template function, searches through the stores vector
	* and returns the address of the store with the given name.
	* In case it doesn't exist, an exception is thrown.
	*
	* @param The name of the store to get.
	* @return The address of the store with the given name.
	*/
	Store* getStore(string name) const;

	/**
	* @brief Gets a collection with the provided name.
	*
	* Making use of a template function, searches through the collections vector
	* and returns the address of the collection with the given name.
	* In case it doesn't exist, an exception is thrown.
	*
	* @param The name of the collection to get.
	* @return The address of the collection with the given name.
	*/
	Collection* getCollection(string name) const;

	/**
	* @brief Gets a publication with the provided name.
	*
	* Making use of a template function, searches through the publication vector
	* and returns the address of the publication with the given name.
	* In case it doesn't exist, an exception is thrown.
	*
	* @param The name of the publication to get.
	* @return The address of the publication with the given name.
	*/
	Publication* getPublication(string name) const;

	/**
	* @brief Gets an employee with the provided name.
	*
	* Making use of a template function, searches through the employees vector
	* and returns the address of the employee with the given name.
	* In case it doesn't exist, an exception is thrown.
	*
	* @param The name of the employee to get.
	* @return The address of the employee with the given name.
	*/
	Employee* getEmployee(string name) const;
	/**
	* @brief Gets the vector of requests from the provided store.
	*
	* Copies the requests of the provided store and pastes it to the vector
	* if its the store we are looking for
	* finally it returns the vector of requests of the given store
	*
	* @param The store of which we wil pull the vector.
	* @return The vector of requests adresses that the store contains
	*/
	vector<Request*> getRequests(const Store* store) const;
	/**
	* @brief Gets the vector of requests from the provided publication.
	*
	* Copies the requests of the provided publication and pastes it to the vector
	* if its the publication we are looking for
	* finally it returns the vector of requests of the given publication
	*
	* @param The publication of which we wil pull the vector.
	* @return The vector of requests adresses that the publication contains
	*/
	vector<Request*> getRequests(const Publication* publ) const;
	/**
	* @brief Gets the vector of requests from the provided collection.
	*
	* Copies the requests of the provided collection and pastes it to the vector
	* if its the collection we are looking for
	* finally it returns the vector of requests of the given collection
	*
	* @param The publication of which we wil pull the vector.
	* @return The vector of requests adresses that the publication contains
	*/
	vector<Request*> getRequests(const Collection* collection) const;
	/**
	* @brief this function returns the in-game date of the program
	* returns the current date.
	*/
	Date today() const;

	/**
	* @brief Writes to a string a list of all of the stores.
	*
	* @return a string containing the names of all the existing stores.
	*/
	string writeStores();

	/**
	* @brief Writes to a string the information of a given store.
	*
	* Searches the stores vector for the given store and gets a string
	* containing data about it.
	*
	* @param st the store which information we want to display.
	* @return a string containing the information of the provided store.
	*/
	string writeStore(Store* st);

	/**
	* @brief Writes to a string the information of a given collection.
	*
	* Searches the collections vector for the given collection and gets a string
	* containing data about it.
	*
	* @param col the collection which information we want to display.
	* @return a string containing the information of the provided collection.
	*/
	string writeCollection(Collection* col);

	/**
	* @brief Writes to a string a list of all of the collections.
	*
	* @return a string containing the names of all the existing collections.
	*/
	string writeCollections();

	/**
	* @brief Writes to a string the information of a given employee.
	*
	* Searches the employees vector for the given employee and gets a string
	* containing data about it.
	*
	* @param emp the employee which information we want to display.
	* @return a string containing the information of the provided employee.
	*/
	string writeEmployee(Employee* emp);

	/**
	* @brief Writes to a string a list of all of the employees.
	*
	* @return a string containing the names of all the existing employees.
	*/
	string writeEmployees();

	// Operations
	//void updateRequests();
	//void sendStock(vector<Request*> ready);
	//void nextDay();
	//void checkLowStockStores(); // ou semelhante...

	//vector<Publication*> searchByYear(unsigned int year);
	// ou: searchByDate; searchByDescription; ....
};
