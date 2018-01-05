#pragma once

#include "Classes.h"
#include "Date.h"
#include "Request.h"
#include "Publication.h"
#include "Supplements.h"


/** @defgroup company company
* @{
*
* The Company class harbors all the information about the collections,employees,stores and requests.
*/


/** @name suspendedHash */
/**@{
*
* Hash function to help store suspended requests in their respective hash table.
*/

struct suspendedHash
{
	int operator() (const Suspended* const& suspended) const
	{
		int v = 0;
		string name = suspended->getPublication()->getName();

		for (unsigned int i = 0; i < name.size(); i++)
			v = 37 * v + name[i];
		return v;
	}

	bool operator() (const Suspended* const& sus1, const Suspended* const& sus2) const
	{
		return *sus1 == *sus2;
	}
};

/** @} end of suspendedHash*/

typedef unordered_set<Suspended*, suspendedHash, suspendedHash> HashSuspendedRequests;

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
	* @param output indicates whether we want to read or write the file
	*
	*/
	void getStoresFile(bool output = false);

	/**
	* @brief Gets the collections and publications file name from the user.
	*
	* Asks the user to enter a collections file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output indicates whether we want to read or write the file
	*
	*/
	void getPublicationsFile(bool output = false);

	/**
	* @brief Gets the employees file name from the user.
	*
	* Asks the user to enter an employees file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output indicates whether we want to read or write the file
	*
	*/
	void getEmployeesFile(bool output = false);

	/**
	* @brief Gets the requests file name from the user.
	*
	* Asks the user to enter a requests file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output indicates whether we want to read or write the file
	*
	*/
	void getRequestsFile(bool output = false);

	/**
	*	@brief Gets the suspended requests file name from the user.
	*
	* Asks the user to enter a suspended requests file name, giving him the option to skip opening it,
	* or to open the default file.
	*
	* @param output indicates whether we want to read or write the file
	*/
	void getSuspendedRequestsFile(bool output = false);


	// (Files.cpp) Read files and initialize vectors.
	/**
	* @brief Reads the stores file previously provided.
	*
	* Reads the stores file and, in case it is correctly formated, creates stores objects
	* and stores them in its set.
	*/
	void readStoresFile();

	/**
	* @brief Reads the collections file previously provided.
	*
	* Reads the collections file and, in case it is correctly formated, creates collections objects
	* and stores them in its set.
	*/
	void readPublicationsFile();

	/**
	* @brief Reads the employees file previously provided.
	*
	* Reads the employees file and, in case it is correctly formated, creates employees objects
	* and stores them in its set.
	*/
	void readEmployeesFile();

	/**
	* @brief Reads the requests file previously provided.
	*
	* Reads the requests file and, in case it is correctly formated, creates requests objects
	* and stores them its set.
	*/
	void readRequestsFile();

	/**
	* @brief Reads the suspended requests file previously provided.
	*
	* Reads the suspended requests file and, in case it is correctly formated, creates suspended requests objects
	* and stores them its set.
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
	* @brief Saves the suspended requests objects to their file.
	*
	* Saves the suspended requests in the same format as they were read and to the same file.
	*/
	void saveSuspendedRequestsToFile();


	// (Company.cpp) Add newly created object and update all other objects.
	/**
	* @brief  Add newly created store and update all other stores.
	* @param newS the new Store to be added.
	* @return true is successful, false if not
	*/
	bool addStore(Store *newS);

	/**
	* @brief  Add newly created collection and update all other collections.
	* @param newC the new Collection to be added.
	* @return true is successful, false if not
	*/
	bool addPublication(Publication *newP);

	/**
	* @brief  Add newly created employee and update all other employees.
	* @param newE the new Employee to be added.
	* @return true is successful, false if not
	*/
	bool addEmployee(Employee *newE);

	/**
	* @brief  Add newly created request and update all other requests.
	* @param newR the new Request to be added.
	* @return true is successful, false if not
	*/
	bool addRequest(Request *newR);

	/**
	* @brief  Add newly created suspended request and update all other suspended requests.
	* @param newSR the new suspended request to be added.
	* @return true is successful, false if not
	*/
	bool addSuspendedRequest(Suspended* newSR);


	// (Company.cpp) Edit existing object, update all other objects if necessary.
	/**
	*	@brief Edits a given store.
	*	@param store The store to be edited.
	*	@param name New name for the store.
	*	@param contact New contact for the store.
	*	@return true is successful, false if not
	*/
	bool editStore(Store* store, string name, unsigned int contact);

	/**
	* @brief Designates an employee to the given store
	* @param store the store to be edited
	* @param employee the employee to become manager of the store
	* @return true is successful, false if not
	*/
	bool designateEmployee(Store* store, Employee* employee);


	// (Company.cpp) Remove existing objects, update all other objects.
	/**
	* @brief  Remove existing store and update all other stores.
	* @param store the Store to be removed.
	* @return true is successful, false if not
	*/
	bool removeStore(Store *store);

	/**
	* @brief  Remove existing publication and update all other publications.
	* @param publication the publication to be removed.
	* @return true is successful, false if not
	*/
	bool removePublication(Publication *publication);

	/**
	* @brief  Remove existing employee and update all other employees.
	* @param employee the Employee to be removed.
	* @return true is successful, false if not
	*/
	bool removeEmployee(Employee *employee);

	/**
	* @brief  Remove existing request and update all other requests.
	* @param request the Request to be removed.
	* @return true is successful, false if not
	*/
	bool removeRequest(Request *request);

	/**
	* @brief  Remove existing suspended request and update all other requests.
	* @param suspended the suspended request to be removed.
	* @return true is successful, false if not
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
	*	@brief Gets the stores of the company
	*	@return A set holding all of the company's stores
	*/
	set<Store*, PComp<Store> > getStores() const;

	/**
	*	@brief Gets the publications of the company
	*	@return A set holding all of the company's publications
	*/
	set<Publication*, PComp<Publication> > getPublications() const;

	/**
	*	@brief Gets the employees of the company
	*	@return A set holding all of the company's employees
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
	* @brief Gets a vector of requests from the provided publication and store.
	* @param store The store that made the requests
	* @param publ The publication specified in the request
	* @return A vector of requests from the provided publication and store.
	*/
	vector<Request*> getRequests(const Store* store, const Publication* publ) const;

	/**
	* @brief Gets a vector with all of the requests
	* @return A vector with all of the requests
	*/
	vector<Request*> getRequests() const;


	/**
	* @brief Gets a vector of suspended requests from the provided store.
	* @param store The store that made the requests
	* @return A vector of suspended requests from the provided store.
	*/
	vector<Suspended*> getSuspendedRequests(const Store* store) const;

	/**
	* @brief Gets a vector of suspended requests from the provided publication.
	* @param publication The publication that was requested
	* @return A vector of suspended requests from the provided publication.
	*/
	vector<Suspended*> getSuspendedRequests(const Publication* publication) const;

	/**
	* @brief Gets a vector of suspended requests from the provided publication and store.
	* @param store The store that made the requests
	* @param publ The publication specified in the request
	* @return A vector of suspended requests from the provided publication and store.
	*/
	vector<Suspended*> getSuspendedRequests(const Store* store, const Publication* publication) const;

	/**
	* @brief Gets a vector with all of the suspended requests
	* @return A vector with all of the suspended requests
	*/
	vector<Suspended*> getSuspendedRequests() const;

	/**
	* @brief this function returns the in-game date of the program
	* returns the current date.
	*/
	Date today() const;


	// (Company.cpp) Other editing functions
	/**
	*	@brief Changes the deadline of a given request
	*	@param request The request to be changed
	*	@param dateLimit The new deadline
	*	@return true if successful, false if not
	*/
	bool setRequestDeadline(Request* request, Date dateLimit);

	/**
	*	@brief Checks if the requests have reached their deadline. If so, sends the production to the respective store.
	*/
	void checkRequests();

	/**
	*	@brief Sends production to a store after a request was completed.
	*	@param publication Copies of this publication will be sent to the store
	*	@param store The store that will receive the production
	*	@param quantity The number of publications to be sent
	*/
	void sendProduction(Publication* publication, Store* store, unsigned int quantity) const;

	/**
	*	@brief Suspends a given request, putting it in the suspended hash table.
	*	@param request The requests to be suspended
	*	@return true if successful, false if not
	*/
	bool suspendRequest(Request* request);

	/**
	*	@brief Ends a suspension of a request, returning it to its original data structure.
	*	@param suspended The request which suspension will end
	*	@return true if successful, false if not
	*/
	bool endSuspension(Suspended* suspended);

	/**
	*	@brief Checks if the suspended requests have been that way for a set number of time. If so, permanently cancels them.
	*/
	void checkSuspendedRequests();

	// (Company.cpp) Check available names
	/**
	*	@brief Checks if there exists an object with a given name in the company's data structures.
	*	@param name The name to be checked
	*	@return true if the name is available, false if not
	*/
	bool nameAvailable(string name) const;
};

/** @} end of company */