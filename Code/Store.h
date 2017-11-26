#pragma once

#include "Classes.h"
#include "Date.h"

struct PublicationLog
{
	unsigned int stock;
	map<Date, unsigned int> sales;
	PublicationLog(unsigned int stock);
	PublicationLog(unsigned int stock, map<Date, unsigned int> sales);
};

class Store
{
private:
	typedef map<Publication*, PublicationLog>::iterator stock_it;
	Company* const company;
	Employee* manager;
	string name;
	string contact;
	map<Publication*, PublicationLog> stock;

	stock_it getPubl(Publication* publ);

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
	Employee* getEmployee() const;

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
	vector<Request*> getRequests(Collection* collection) const;

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
	void addToStock(Publication* publ, unsigned int s);
	bool sellPublication(Publication* publ, unsigned int quantity);
	void makeFixedRequest(Publication* publ, unsigned int quantity);
	
	void addPublication(Publication* publ, unsigned int st);
	void addCollection(Collection* collection);
	void makeRequest(Publication* publ) const;
	void makeRequests(Collection* collection) const;
	void removePublication(Publication* publ);
	void removeCollection(Collection* collection);

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
};

