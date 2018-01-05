#pragma once

#include "Classes.h"
#include "Date.h"
#include "Request.h"
#include "Publication.h"
#include "Supplements.h"

struct suspendedHash
{
	int operator() (Suspended* const& suspended) const
	{
		int v = 0;
		string name = suspended->getPublication()->getName();

		for (unsigned int i = 0; i < name.size(); ++i)
			v = 37 * v + (int)name.at(i);

		return v;
	}

	bool operator() (Suspended* const& sus1, Suspended* const& sus2) const
	{
		return sus1 == sus2;
	}
};

typedef unordered_set<Suspended*, suspendedHash/*, suspendedHash*/> HashSuspendedRequests;


/**
* @brief The class harbors all the information about the collections,employees,stores and requests.
*/
class Company
{
private:
	set<Store *, PComp<Store> > stores;
	set<Publication*, PComp<Publication> > publications;
	set<Employee *, PComp<Employee> > employees;
	set<Request *, PComp<Request> > productionPlan;
	HashSuspendedRequests suspendedRequests;

	string storesFileName, publicationsFileName, employeesFileName, requestsFileName, suspendedRequestsFileName;

	Menu *menu;
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
	void getPublicationsFile(bool output = false);

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

	/**
	*
	*/
	void getSuspendedRequestsFile(bool output = false);


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
	void readPublicationsFile();

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

	/**
	*
	*/
	void readSuspendedRequestsFile();


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
	void savePublicationsToFile();

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

	/**
	*
	*/
	void saveSuspendedRequestsToFile();


	// (Company.cpp) Add newly created object and update all other objects.
	/**
	* @brief  Add newly created store and update all other stores.
	* @param newS the new Store to be added.
	*/
	bool addStore(Store *newS);

	/**
	* @brief  Add newly created collection and update all other collections.
	* @param newC the new Collection to be added.
	*/
	bool addPublication(Publication *newP);

	/**
	* @brief  Add newly created employee and update all other employees.
	* @param newE the new Employee to be added.
	*/
	bool addEmployee(Employee *newE);

	/**
	* @brief  Add newly created request and update all other requests.
	* @param newR the new Request to be added.
	*/
	bool addRequest(Request *newR);

	/**
	*
	*/
	bool addSuspendedRequest(Suspended* newSR);


	// (Company.cpp) Edit existing object, update all other objects if necessary.
	/**
	*
	*/
	bool editStore(Store* store, string name, unsigned int contact);

	/**
	*
	*/
	bool designateEmployee(Store* store, Employee* employee);


	// (Company.cpp) Remove existing objects, update all other objects.
	/**
	* @brief  Remove existing store and update all other stores.
	* @param store the Store to be removed.
	*/
	bool removeStore(Store *store);

	/**
	* @brief  Remove existing collection and update all other collections.
	* @param collection the Collection to be removed.
	*/
	bool removePublication(Publication *publication);

	/**
	* @brief  Remove existing employee and update all other employees.
	* @param employee the Employee to be removed.
	*/
	bool removeEmployee(Employee *employee);

	/**
	* @brief  Remove existing request and update all other requests.
	* @param request the Request to be removed.
	*/
	bool removeRequest(Request *request);

	/**
	*
	*/
	bool removeSuspended(Suspended* suspended);


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
	Store *getStore(string name) const;

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
	Publication *getPublication(string name) const;

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
	Employee *getEmployee(string name) const;

	/**
	*
	*/
	set<Store*, PComp<Store> > getStores() const;

	/**
	*
	*/
	set<Publication*, PComp<Publication> > getPublications() const;

	/**
	*
	*/
	set<Employee*, PComp<Employee> > getEmployees() const;

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
	vector<Request*> getRequests(const Store *store) const;

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
	vector<Request*> getRequests(const Publication *publ) const;

	/**
	*
	*/
	vector<Request*> getRequests(const Store* store, const Publication* publ) const;

	/**
	*
	*/
	vector<Request*> getRequests() const;

	/**
	*
	*/
	vector<Suspended*> getSuspendedRequests(const Store* store) const;

	/**
	*
	*/
	vector<Suspended*> getSuspendedRequests(const Publication* publication) const;

	/**
	*
	*/
	vector<Suspended*> getSuspendedRequests(const Store* store, const Publication* publication) const;

	/**
	*
	*/
	vector<Suspended*> getSuspendedRequests() const;

	/**
	* @brief this function returns the in-game date of the program
	* returns the current date.
	*/
	Date today() const;


	// (Company.cpp) Other editing functions
	/**
	*
	*/
	bool setRequestDeadline(Request* request, Date dateLimit);

	/**
	*
	*/
	void checkRequests();

	/**
	*
	*/
	void sendProduction(Publication* publication, Store* store, unsigned int quantity) const;

	/**
	*
	*/
	bool suspendRequest(Request* request);

	/**
	*
	*/
	bool endSuspension(Suspended* suspended);

	/**
	*
	*/
	void checkSuspendedRequests();

	// (Company.cpp) Check available names
	/**
	*
	*/
	bool nameAvailable(string name) const;
};