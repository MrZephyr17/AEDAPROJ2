#pragma once

#include "Classes.h"
#include "Date.h"



/**
* @brief It harbors information about its own publications, requests, stock and it belongs the company
*/
class Store
{
private:
	Company* const company;
	Employee* manager;
	string name;
	string contact;
	priority_queue<LocalPublication> stock; 

public:
	// Constructors
	/**
	 * @brief Reads the info string and creates a store object.
	 * 
	 * Making use of helper functions found on Supplements.h, goes through the info string
	 * and retrieves the attributes necessary to create the store object.
	 * 
	 * @param info A string with all the necessary information to create a store object.
	 * @param comp A pointer to the company, the main object of the program.
	 */ 
	Store(string info, Company* comp);

	/**
	 * @brief Receives discriminated parameters and creates a store object.
	 * @param company A pointer to the company, the main object of the program.
	 * @param name The name/place of the store.
	 * @param contact The phone number of the store.
	 * @param manager The employee responsible for the store (may be inexistent).
	 */ 
	Store(Company* company, string name, string contact, Employee* manager = nullptr);
	
	// Gets
	/**
	 * @brief Gets the manager of the store.
	 * 
	 * @return A pointer to the employee responsible for the store.
	 */ 
	Employee* getManager() const;

	/**
	 * @brief Gets the name of the store.
	 * 
	 * @return the name of the store.
	 */ 
	string getName() const;

	/**
	 * @brief Gets the contact of the store.
	 * 
	 * @return the contact of the store.
	 */ 
	string getContact() const;

	/**
	 * @brief Gets the requests made by the store.
	 * 
	 * @return a vector containing the requests made by the store.
	 */ 
	vector<Request*> getRequests() const;

	/**
	 * @brief Gets the requests made by the store of a specific collection.
	 * @param collection the collection of the requests that should be returned.
	 * @return a vector containing the requests made by the store of the given collection.
	 */ 
	vector<Request*> getRequests(string collection) const;

	/**
	 * @brief Gets the requests made by the store of a specific publication.
	 * @param publ the publication of the requests that should be returned.
	 * @return a vector containing the requests made by the store of the given publication.
	 */ 
	vector<Request*> getRequests(Publication* publ) const;

	// Sets
	/**
	 * @brief Changes the name of the store to the given one.
	 * 
	 * @param newName the new name of the store.
	 */ 
	void setName(string newName);

	/**
	 * @brief Changes the contact of the store to the given one.
	 * 
	 * @param newContact the new contact of the store.
	 */ 
	void setContact(string newContact);

	/**
	 * @brief Changes the manager of the store to the given one.
	 * 
	 * @param newManager the new manager of the store.
	 */ 
	void setManager(Employee* newManager);

	// Operations
	/**
	* @brief Checks if stock has publications
	* @return If store has any publications
	*/
	bool noStock() const;
	/**
	* @brief Checks if its possible for the store to sell a given quantity for a selected publication
	* @param publ The target publication
	* @param quantity the quantity 
	*/
	bool sellPublication(Publication* publ, unsigned int quantity);
	/**
	* @brief Makes a request of a publication for the store
	*
	* @param publ the publication we want to request.
	* @param quantity the quantity of the publication.
	*/
	void makeRequest(Publication* publ, unsigned int quantity, Date limit);
	/**
	* @brief Adds a publication and its stock.
	*
	* @param publ the target publication.
	* @param st the stock added.
	*/
	void addPublication(Publication* publ, unsigned int st);


	/**
	* @brief Removes a publication from the store
	*
	* @param publ the target publication.
	*/
	bool removePublication(Publication* publ);


	// Writers
	/**
	 * @brief Creates and returns a formated string containing data of the store.
	 * @return a string containing information of the store
	 */ 
	string writeInfo() const;

	/**
	 * @brief Returns a string to be written to a file.
	 * 
	 * Creates and returns a string contaning information of the store and
	 * specially formated to be written to a file.
	 * 
	 * @return a string containing information of the store
	 */ 
	string writeToFile() const;



	vector<Publication*> stockLowerThan(unsigned int n) const;

	vector<LocalPublication> getPublications() const;

	void receiveProduction(Publication* publication, unsigned int quantity);

	LocalPublication getPublication(Publication* publication) const;

	void removePublication(LocalPublication publication);

	bool operator<(const Store& s2) const;
};

