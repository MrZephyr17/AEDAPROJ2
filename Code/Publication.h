#pragma once

#include "Classes.h"
#include "Date.h"




/** @defgroup publication publication
* @{
*
* Classes to represent a publication (book or magazine), with methods to help store them in their appropriate data
* structures.
*/

class LocalPublication
{
private:
	Publication* publication;
	unsigned int stock;
public:

	/**
	*	@brief Creates an empty local publication.
	*/
	LocalPublication();

	/**
	*	@brief Creates a local publication with the given parameters
	*	@param publication the publication to be stored locally
	*	@param stock the number of copies to be stored in the store
	*/
	LocalPublication(Publication *publication, unsigned int stock);

	/**
	*	@brief Gets the associated publication
	*   @return pointer to the associated publication
	*/
	Publication* getPublication() const;

	/**
	*	@brief Gets the stock of the publication on the store
	*	@return Number of copies of the publication on the store
	*/
	unsigned int getStock() const;

	/**
	*	@brief Sets the stock of the publication.
	*	@param stock the new stock of the publication.
	*/
	void setStock(unsigned int stock);

	/**
	*	@brief Adds some copies to the local stock
	*	@param quantity the number of copies to be added to the stock.
	*/
	void addStock(unsigned int quantity);

	/**
	*	@brief Writes information of the object to a string.
	*	@return a formatted string containing information on the local publication.
	*/
	string write() const;

	bool operator<(const LocalPublication& p2) const;
	bool operator==(const LocalPublication& p2) const;
	bool operator!=(const LocalPublication& p2) const;
};



/**
*@brief Class for the publications that are in the collection, each publication can be a book or a magazine
*/
class Publication
{
protected:

	Company* const company;
	string name;
	string description;
	string collection;
	Date releaseDate;
	double price;

	string type;

public:
	// Constructors
	/**
	* @brief Receives discriminated parameters and creates a publication object.
	* @param name the name of this specific publication.
	* @param description the description of this specific publication.
	* @param collection A pointer to the collection that the publication will be placed in.
	* @param date the date of the creation of the publication.
	* @param price The price of the publication.
	* @param type Type of the publication (book or magazine).
	*/
	Publication(string name, string description, string collection, Date releaseDate, double price, string type);

	/**
	*	@brief Creates a publication after reading the publications file
	*	@param info A string with information about a publication
	*	@param company The company associated with the publication
	*/
	Publication(string info, Company* company);

	// Gets
	/**
	* @brief gets the name of the the specific publication.
	* @return the name of the publication.
	*/
	string getName() const;

	/**
	* @brief gets the description of the the specific publication.
	* @return the description of the publication.
	*/
	string getDescription() const;

	/**
	* @brief gets the collection of the the specific publication.
	* @return the colletion of the publication.
	*/
	string getCollection() const;

	/**
	* @brief gets the date of the the specific publication.
	* @return the date of the publication.
	*/
	Date getReleaseDate() const;

	/**
	* @brief gets the price of the the specific publication.
	* @return the price of the publication.
	*/
	double getPrice() const;

	/**
	* @brief Gets the type of the the specific publication.
	* @return the type of the publication.
	*/
	string getType() const;
	
	/** 
	*	@brief Gets a vector containing all of the active requests related to the publication
	*	@return A vector of pointers to the requests related to the publication
	*/
	vector<Request*> getRequests() const;

	// Sets
	/**
	* @brief changes the name of the the specific publication.
	* @param newName The new name of the publication.
	*/
	void setName(string newName);
	/**
	* @brief changes the description of the the specific publication.
	* @param newDescription The new description of the publication.
	*/
	void setDescription(string newDescription);
	/**
	* @brief changes the price of the the specific publication.
	* @param newPrice A double that will be the new price of the publication.
	*/
	void setPrice(double newPrice);

	// Operations

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the publication.
	* @return a string containing information of the publication
	*/
	virtual string writeInfo() const;

	/**
	* @brief Creates and returns a formated string containing data of the publication to be written to a file.
	* @return a string containing information of the publication
	*/
	virtual string writeToFile() const;

	bool operator<(const Publication& publ) const;
};



/**
*@brief A specific type of publication that is a book
*/
class Book : public Publication
{
	unsigned int edition;

public:
	// Constructors
	/**
	* @brief Receives discriminated parameters and creates a book object.
	* @param name the name of this specific book.
	* @param description the description of this specific book.
	* @param collection A pointer to the collection that the book will be placed in.
	* @param date the date of the creation of the book.
	* @param price The price of the book.
	*/
	Book(string name, string description, string collection, Date date, double price, unsigned int edition = 1);

	/**
	*	@brief Creates a book after reading the publications file
	*	@param info A string with information about a book
	*	@param company The company associated with the book
	*/
	Book(string info, Company* company);

	// Gets
	/**
	* @brief gets the volume of the the specific book.
	* @return the version of the book.
	*/
	unsigned int getEdition() const;

	// Operations

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the book.
	* @return a string containing information of the book.
	*/
	string writeInfo() const;

	/**
	* @brief Creates and returns a formated string containing data of the book to be written to a file.
	* @return a string containing information of the book
	*/
	string writeToFile() const;
};
/**
*@brief A specific type of publication that is a Magazine it has volume and number.
*/
class Magazine : public Publication
{
	unsigned int volume;
	unsigned int number;

public:
	// Constructors
	/**
	* @brief Receives discriminated parameters and creates a magazine object.
	* @param name the name of this specific magazine.
	* @param description the description of this specific magazine.
	* @param collection A pointer to the collection that the magazine will be placed in.
	* @param date the date of the creation of the magazine.
	* @param price The price of the magazine.
	* @param v The volume of the magazine.
	* @param n The number of the magazine.
	*/
	Magazine(string name, string description, string collection, Date date, double price, unsigned int v, unsigned int n);

	/**
	*	@brief Creates a magazine after reading the publications file
	*	@param info A string with information about a magazine
	*	@param company The company associated with the magazine
	*/
	Magazine(string info, Company* company);

	// Gets
	/**
	* @brief gets the volume of the the specific magazine.
	* @return the volume of the magazine.
	*/
	unsigned int getVolume() const;
	/**
	* @brief gets the number of the the specific magazine.
	* @return the number of the magazine.
	*/
	unsigned int getNumber() const;

	// Operations

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the magazine.
	* @return a string containing information of the magazine
	*/
	string writeInfo() const;

	/**
	* @brief Creates and returns a formated string containing data of the magazine to be written to a file.
	* @return a string containing information of the magazine
	*/
	string writeToFile() const;
};

/** @} end of publication */
