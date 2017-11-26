#pragma once

#include "Classes.h"
#include "Date.h"

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
	Publication(string name, string description, Collection* collection, Date date, double price);
	
	// Gets
	string getName() const;
	string getDescription() const;
	Collection* getCollection() const;
	Date getDate() const;
	double getPrice() const;

	// Sets
	void setName(string newName);
	void setDescription(string newDescription);
	void setPrice(double newPrice);

	// Operations

	// Writers
	virtual string writeInfo() const;
};


class Book : public Publication
{
	friend class BookCollection;
	string version;

  public:
	// Constructors
	Book(string name, string description, Collection* collection, Date date, double price, string version = "Original version"); // Ou o caralho
	
	// Gets
	string getVersion() const;

	// Operations
	
	// Writers
	string writeInfo() const;
};

class Magazine : public Publication
{
  private:
	friend class MagazineCollection;

	const unsigned int volume;
	const unsigned int number;

  public:
	// Constructors
	Magazine(string name, string description, Collection* collection, Date date, double price, unsigned int v, unsigned int n);
	
	// Gets
	unsigned int getVolume() const;
	unsigned int getNumber() const;

	// Operations

	// Writers
	string writeInfo() const;
};
