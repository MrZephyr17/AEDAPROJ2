#pragma once

#include "Classes.h"
#include "Date.h"

class Employee
{
private:
	Company* const company;
	string name;
	Date birthDate;
	Store* store;

public:
	// Constructors
	/**
	 * @brief Reads the info string and creates an employee object.
	 * 
	 * Making use of helper functions found on Supplements.h, goes through the info string
	 * and retrieves the attributes necessary to create the employee object.
	 * 
	 * @param info A string with all the necessary information to create an employee object.
	 * @param comp A pointer to the company, the main object of the program.
	 */ 
	Employee(string info, Company* company);

	/**
	 * @brief Receives discriminated parameters and creates an employee object.
	 * @param company A pointer to the company, the main object of the program.
	 * @param name the name of the employee.
	 * @param birthDate the birthdate of the employee.
	 */ 
	Employee(Company* company, string name, Date birthDate);

	// Gets
	/**
	 * @brief Returns the name of the employee in a string.
	 * @return the name of the employee
	 */ 
	string getName() const;

	/**
	 * @brief Returns the birthdate of the employee.
	 * @return the birthdate of the employee
	 */ 
	Date getBirthDate() const;

	/**
	 * @brief Returns the store managed by the employee.
	 * @return pointer to the store managed by the employee.
	 */ 
	Store* getStore() const;

	// Sets
	void setName(string newName); // LOL
	void setBirthDate(Date newBirthDate); // LOL !

	/**
	 * @brief Assigns the employee to a new store.
	 * @param newStore the store now managed by the employee.
	 */ 
	void setStore(Store* newStore);

	// Operation

	// Writers

	/**
	 * @brief Creates and returns a formated string containing data of the employee.
	 * @return a string containing information of the employee
	 */ 
	string writeInfo() const;
	
	/**
	 * @brief Returns a string to be written to a file.
	 * 
	 * Creates and returns a string contaning information of the employee and
	 * specially formated to be written to a file.
	 * 
	 * @return a string containing information of the employee
	 */ 
	string writeToFile() const;
};

