#pragma once

#include "Classes.h"

/**
* @brief A class that harbors publications
* it has the information about its name type devo time, belongs to a company.
*/
class Collection
{
protected:
	friend class Publication;

	Company* const company;
	string name;
	string type;
	unsigned int minProductionTime;

public:
	// Constructors
	/**
	* @brief Reads the info string and creates a collection object.
	*
	* Making use of helper functions found on Supplements.h, goes through the info string
	* and retrieves the attributes necessary to create the employee object.
	*
	* @param info A string with all the necessary information to create an collection object.
	* @param comp A pointer to the company, the main object of the program.
	*/
	Collection(string info, Company* company);
	/**
	* @brief Receives discriminated parameters and creates an collection object.
	* @param company A pointer to the company, the main object of the program.
	* @param name the name of the collection.
	* @param type the type of collection (Book or magazine).
	*/
	Collection(Company* company, string name, string type, unsigned int time);

	// Gets
	/**
	* @brief Returns the name of the collection in a string.
	* @return the name of the employee
	*/
	string getName() const;
	/**
	* @brief Returns the type of the collection in a string.
	* @return the name of the employee
	*/
	string getType() const;
	/**
	* @brief Returns the name of the employee in a unsigned integer.
	* @return the value of the minimum production time of the collection.
	*/
	unsigned int getMinProductionTime() const;

	// Sets
	/**
	* @brief Changes the name of the selected collection.
	* @param newName the new name of the selected Collection
	*/
	void setName(string newName);
	/**
	* @brief Changes the type of the selected collection.
	* @param newType the new name of the selected Collection
	*/
	void setType(string newType);
	/**
	* @brief Changes the minimum production time of the selected collection.
	* @param newTime the new minimum production time of the selected Collection
	*/
	void setMinProductionTime(unsigned int newTime);

	// Operations
	/**
	* @brief Returns all publications.
	* @return All publications
	*/
	virtual vector<Publication*> getAllPublications() const;
	/**
	* @brief Returns a publication of the collection.
	* @param name A string of the name of the publication we are looking for.
	* @return The publication object that we searched for
	*/
	virtual Publication* getPublication(string name) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param pub1 The publication object we are searching for
	*/
	virtual bool hasPublication(Publication* publ) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param name The name of the publication we are searching for
	*/
	virtual bool hasPublication(string name) const;

	// Writers
	/**
	* @brief Writes the information of the collection to a string
	*
	* Creates a string with the contents of collection, the name,
	* the type and Minimum Production Time so we can dysplay that same
	* information after to the user
	*
	* @return the string with the information
	*/
	virtual string writeInfo() const;
	/**
	* @brief Writes the information of the collection to a string
	*
	* Creates a string with the contents of collection, the name,
	* the type and Minimum Production Time in a predefined structure
	* so we can then save that same info to a file afterwards
	*
	* @return the string with the information
	*/
	virtual string writeToFile() const;
};

/**
* @brief A Class that the main focus is to harbor a "Collection of Books"
* Has a vector in which it stores Book objects
*/
class BookCollection : public Collection
{
private:
	friend class Book;
	typedef vector<Book*>::iterator book_it;

	vector<Book*> books;
	book_it getBook(Book* book);

public:
	// Constructors
	/**
	* @brief Reads the info string and creates a BookCollection
	*
	* Making use of helper functions found on Supplements.h, goes through the info string
	* and retrieves the attributes necessary to create the BookCollection object.
	*
	* @param info A string with all the necessary information to create an BookCollection object.
	* @param comp A pointer to the company, the main object of the program.
	*/
	BookCollection(string info, Company* company);
	/**
	* @brief Receives discriminated parameters and creates a BookCollection
	* @param comp A pointer to the company, the main object of the program.
	* @param name A string with the name desired for the BookCollection object.
	* @param type A string with the type desired for the BookCollection object.
	* @param time A unsigned int with the mininum production time desired for the BookCollection object.
	*/
	BookCollection(Company* company, string name, string type, unsigned int time);

	// Gets
	/**
	* @brief Gets the books of the book collection
	* @return a vector with the books contained in that collection.
	*/
	vector<Book*> getBooks() const;
	/**
	* @brief Returns the book of the book collection.
	* @param name A string of the name of the book we are looking for.
	* @return The book object that we searched for.
	*/
	Book* getBook(string name) const;

	// Sets

	// Operations
	/**
	* @brief Returns the book of the book collection.
	* @param name A string of the name of the book we are looking for.
	* @return The book object that we searched for
	*/
	Publication* getPublication(string name) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param pub1 The publication object we are searching for
	*/
	bool hasPublication(Publication* publ) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param name The name of the publication we are searching for
	*/
	bool hasPublication(string name) const;
	/**
	* @brief Adds a book to the collection
	* @param book A book object,the one we are adding to collection.
	*/
	void addBook(Book* book);
	/**
	* @brief Removes a book to the collection
	* @param book A book object,the one we are removing to collection.
	*/
	void removeBook(Book* book);
	/**
	* @brief Updates the info of a selected book in the collection.
	* @param oldB A book object,the one we are replacing.
	* @param newB A book object, the we are adding to the collection
	*/
	void updateBook(Book* oldB, Book* newB);

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the collection.
	* @return a string containing information of the collection
	*/
	string writeInfo() const;

	/**
	* @brief Returns a string of the collection to be written to on a file.
	*
	* Creates and returns a string contaning information of the collection and
	* specially formated to be written to a file.
	*
	* @return a string containing information of the collection
	*/
	string writeToFile() const;

	/**
	* @brief Returns all publications.
	* @return All publications
	*/
	vector<Publication*> getAllPublications() const;

	/**
	* @brief Sorts the books by date
	* @return The books sorted
	*/
	vector<Book*> sortCheaper() const;
};

/**
* @brief A Class that the main focus is to harbor a "Collection of Magazine"
*
* Has a vector in which it stores Magazines objects, it also has the information about
* the release frequency of the collection a value that is constant throught all its publications
*/
class MagazineCollection : public Collection
{
private:
	friend class Magazine;

	Magazine* magazine;
	unsigned int releaseFrequency;
	//vector<Magazine*> oldMagazines;

public:
	// Constructors
	/**
	* @brief Reads the info string and creates a MagazineCollection.
	*
	* Making use of helper functions found on Supplements.h, goes through the info string
	* and retrieves the attributes necessary to create the MagazineCollection.
	*
	* @param info A string with all the necessary information to create an MagazineCollection.
	* @param comp A pointer to the company, the main object of the program.
	*/
	MagazineCollection(string info, Company* company);
	/**
	* @brief Receives discriminated parameters and creates a MagazineCollection.
	* @param comp A pointer to the company, the main object of the program.
	* @param name A string with the name desired for the MagazineCollection.
	* @param type A string with the type desired for the MagazineCollection.
	* @param time A unsigned int with the mininum production time desired for the MagazineCollection.
	*/
	MagazineCollection(Company* company, string name, string type, unsigned int time, unsigned int freq);

	// Gets

	/**
	* @brief Returns the Magazine of the magazine collection.
	* @return The book object that we searched for
	*/
	Magazine* getMagazine() const;
	/**
	* @brief Returns the release frequency of the magazine collection.
	* @return The release frequency.
	*/
	unsigned int getReleaseFrequency() const;

	// Sets
	/**
	* @brief Changes the release frequency of the selected magazine collection.
	* @param newFreq the new frequency for the Collection.
	*/
	void setReleaseFrequency(unsigned int newFreq);

	// Operations
	/**
	* @brief Returns the publication object in the magazine collection.
	* @param name the name of the publication.
	* @return Return the publication.
	*/
	Publication* getPublication(string name) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param pub1 The publication object we are searching for
	*/
	bool hasPublication(Publication* publ) const;
	/**
	* @brief Checks if a publication exists
	*
	* Checks if a publication exists with a publication as its arguments and returns a true or false statement
	*
	* @param name The name of the publication we are searching for
	*/
	bool hasPublication(string name) const;
	/**
	* @brief Updates the info of a selected magazine in the collection.
	* @param oldM A magzine object,the one we are replacing.
	* @param newM A magazine object, the one we are adding to the collection
	*/
	void updateMagazine();
	/**
	* @brief This function checks if the publish date of a magazine is today.
	* return Returns a true statment if the publish date is today and false otherwise.
	*/
	bool isPublishDate();

	// Writers
	/**
	* @brief Creates and returns a formated string containing data of the collection.
	* @return a string containing information of the collection
	*/
	string writeInfo() const;

	/**
	* @brief Returns a string to be written to a file.
	*
	* Creates and returns a string contaning information of the collection and
	* specially formated to be written to a file.
	*
	* @return a string containing information of the collection
	*/
	string writeToFile() const;

	/**
	* @brief Returns all publications.
	* @return All publications
	*/
	vector<Publication*> getAllPublications() const;
};
