#pragma once

#include "Classes.h"
#include "Date.h"


/**
* @brief It has the info about a given publication that is asked by a store and its quantity among other atributes
*/
class Request
{
  protected:
	Company *const company;
	Publication *publication;
	Store *store;
	Date requestDate;
	Date deliveryLimit;
	unsigned int quantity;

  public:
	// Constructors
	/**
	 * @brief Reads the info string and creates a request object.
	 * 
	 * Making use of helper functions found on Supplements.h, goes through the info string
	 * and retrieves the attributes necessary to create the request object.
	 * 
	 * @param info A string with all the necessary information to create a request object.
	 * @param comp A pointer to the company, the main object of the program.
	 */
	Request(string info, Company *company);

	/**
	 * @brief Receives discriminated parameters and creates a store object.
	 * @param comp A pointer to the company, the main object of the program.
	 * @param publ A pointer to the publication that is being requested.
	 * @param store A pointer to the store that is requesting more stock.
	 * @param quantity The number of publications to be produced.
	 */
	Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit);


	Request(Company *company, Publication *publ, Store *store, unsigned int quantity, Date requestDate, Date limit);


	// Gets

	/**
	 * @brief Returns a pointer to the publication that is being requested.
	 * @return A pointer to the publication.
	 */
	Publication *getPublication() const;

	/**
	 * @brief Returns a pointer to store that is requesting more stock.
	 * @return A pointer to the store.
	 */
	Store *getStore() const;

	/**
	 * @brief Returns the request date.
	 * @return The date when the request was made.
	 */
	Date getRequestDate() const;

	Date getDeliveryLimit() const;

	/**
	 * @brief Returns the quantity of publications requested.
	 * @return The number of requested publications.
	 */
	unsigned int getQuantity() const;

	// Writers

	/**
	 * @brief Creates and returns a formated string containing data of the request.
	 * @return a string containing information of the request
	 */
	virtual string writeInfo() const;

	/**
	 * @brief Returns a string to be written to a file.
	 * 
	 * Creates and returns a string contaning information of the request and
	 * specially formated to be written to a file.
	 * 
	 * @return a string containing information of the request
	 */
	virtual string writeToFile() const;

	void setDeliveryLimit(Date newLimit);

	bool operator<(const Request &r2) const;
};

class Suspended : public Request
{
private:
	Date suspensionDate;

public:
	Suspended(Company *company, Publication *publ, Store *store, unsigned int quantity, Date limit, Date suspensionDate);
	Suspended(Company *company, Publication *publ, Store *store, unsigned int quantity, Date requestDate, Date limit, Date suspensionDate);

	Suspended(string info, Company* company);
	Date getSuspensionDate() const;
	string writeInfo() const;
	string writeToFile() const;
	bool operator==(const Suspended& req2) const;
};

