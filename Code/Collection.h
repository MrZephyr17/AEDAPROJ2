#pragma once

#include "Classes.h"

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
	Collection(string info, Company* company);
	Collection(Company* company, string name, string type, unsigned int time);

	// Gets
	string getName() const;
	string getType() const;
	unsigned int getMinProductionTime() const;

	// Sets
	void setName(string newName);
	void setType(string newType);
	void setMinProductionTime(unsigned int newTime);

	// Operations
	virtual Publication* getPublication(string name) const;
	virtual bool hasPublication(Publication* publ) const;
	virtual bool hasPublication(string name) const;
	// virtual void makeRequests();

	// Writers
	virtual string writeInfo() const;
	virtual string writeToFile() const;
	//search functions com polimorfimo
};


class BookCollection : public Collection
{
private:
	friend class Book;
	typedef vector<Book*>::iterator book_it;

	vector<Book*> books;
	book_it getBook(Book* book);

public:
	// Constructors
	BookCollection(string info, Company* company);
	BookCollection(Company* company, string name, string type, unsigned int time);

	// Gets
	vector<Book*> getBooks() const;
	Book* getBook(string name) const;

	// Sets

	// Operations
	Publication* getPublication(string name) const;
	bool hasPublication(Publication* publ) const;
	bool hasPublication(string name) const;
	void addBook(Book* book);
	void removeBook(Book* book);
	void updateBook(Book* oldB, Book* newB);
	

	// Writers
	string writeInfo() const;
	string writeToFile() const;
};


class MagazineCollection : public Collection
{
private:
	friend class Magazine;

	Magazine* magazine;
	unsigned int releaseFrequency;
	//vector<Magazine*> oldMagazines;

public:
	// Constructors
	MagazineCollection(string info, Company* company);
	MagazineCollection(Company* company, string name, string type, unsigned int time, unsigned int freq);

	// Gets
	Magazine* getMagazine() const;
	unsigned int getReleaseFrequency() const;

	// Sets
	void setReleaseFrequency(unsigned int newFreq);

	// Operations
	Publication* getPublication(string name) const;
	bool hasPublication(Publication* publ) const;
	bool hasPublication(string name) const;
	void updateMagazine();
	bool isPublishDate();

	// Writers
	string writeInfo() const;
	string writeToFile() const;
};
