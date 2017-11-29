#pragma once

#include "Classes.h"
#include "Date.h"

/**
*@brief Class for the publications that are in the collection, each publication can be a book or a magazine
*/
class Publication
{
protected:
	friend class Collection;

	string name;
	string description;
	Collection* const collection;
	const Date date;
	double price;

public:
	// Constructors
	/**
	* @brief Receives discriminated parameters and creates a publication object.
	* @param name the name of this specific publication.
	* @param description the description of this specific publication.
	* @param collection A pointer to the collection that the publication will be placed in.
	* @param date the date of the creation of the publication.
	* @param price The price of the publication.
	*/
	Publication(string name, string description, Collection* collection, Date date, double price);

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
	Collection* getCollection() const;
	/**
	* @brief gets the date of the the specific publication.
	* @return the date of the publication.
	*/
	Date getDate() const;
	/**
	* @brief gets the price of the the specific publication.
	* @return the price of the publication.
	*/
	double getPrice() const;

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
};

/**
*@brief A specific type of publication that is a book
*/
class Book : public Publication
{
	friend class BookCollection;
	string version;

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
	Book(string name, string description, Collection* collection, Date date, double price, string version = "Original version"); // Ou o caralho

																																 // Gets
																																 /**
																																 * @brief gets the volume of the the specific book.
																																 * @return the version of the book.
																																 */
	string getVersion() const;

	// Operations

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the book.
	* @return a string containing information of the book.
	*/
	string writeInfo() const;
};
/**
*@brief A specific type of publication that is a Magazine it has volume and number.
*/
class Magazine : public Publication
{
private:
	friend class MagazineCollection;

	const unsigned int volume;
	const unsigned int number;

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
	Magazine(string name, string description, Collection* collection, Date date, double price, unsigned int v, unsigned int n);

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
};
