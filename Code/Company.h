#pragma once

#include "Classes.h"
#include "Date.h"

class Company
{
private:
	vector<Store*> stores;
	vector<Employee*> employees;
	vector<Request*> productionPlan;
	vector<Collection*> collections;
	string storesFileName, collectionsFileName, employeesFileName, requestsFileName;

	Menu* menu;
	Date currentDay;

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
	void addStore(Store* newS);
	void addCollection(Collection* newC);
	void addEmployee(Employee* newE);
	void addRequest(Request* newR);

	// (Company.cpp) Remove existing object and update all other objects.
	// Incomplete
	void removeStore(Store* store);
	void removeCollection(Collection* collection);
	void removeEmployee(Employee* employee);
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
	vector<Request*> getRequests(const Store* store) const;
	vector<Request*> getRequests(const Publication* publ) const;
	vector<Request*> getRequests(const Collection* collection) const;
	Date today() const; // LOL achei engracado :P

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
