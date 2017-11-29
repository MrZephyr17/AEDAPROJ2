#pragma once

#include "Classes.h"

#include <iostream>


/**
* @brief This exception is responsible for catching names that aren't present in the database
*/
class NameNotFound
{
private:
	string name;
	string type;
public:
	/**
	* @brief Creates a NameNotFound exception object.
	* @param name name of the object that was being searched.
	* @param type type of the object that was being searched.
	*/
	NameNotFound(string name, string type);

	/**
	* @brief Creates an error message to be displayed to the user.
	* @return a string contaning a message to be displayed to the user.
	*/
	string message();
};

template <class T>
class DuplicateElement
{
private:
	T* duplicate;

public:
	/**
	* @brief Creates a DuplicateElement exception object.
	* @param el element that already exists in the data base.
	*/
	DuplicateElement(T* el);

	/**
	* @brief Creates an error message to be displayed to the user.
	* @return a string contaning a message to be displayed to the user.
	*/
	string message();
};

template<class T>
DuplicateElement<T>::DuplicateElement(T* el) :
	duplicate(el) {}


template<class T>
string DuplicateElement<T>::message()
{
	string m = "Shit";  //"That element of type " + (typeid(*duplicate).name()) + " already exists!\n";

	return m;
}

/**
* @brief This exception is responsible for catching elements that aren't present in the database
*/
template<class T>
class NonExistentElement
{
private:
	T* element;

public:
	/**
	* @brief Creates a NonExistentElement exception object.
	* @param el element that does not exist in the data base.
	*/
	NonExistentElement(T* el);

	/**
	* @brief Creates an error message to be displayed to the user.
	* @return a string contaning a message to be displayed to the user.
	*/
	string message();
};

template<class T>
NonExistentElement<T>::NonExistentElement(T* el)
{
	element = el;
}

template<class T>
string NonExistentElement<T>::message()
{
	string m;

	m = "That element doesn't exist!\n";

	return m;
}


template <class T>
class MalformedFileItem
{
private:
	T* const el;
	const string msg;
public:
	/**
	* @brief Creates a MalformedFileItem exception object.
	* @param el element that was not properly formated.
	* @param message error message to be displayed to the user.
	*/
	MalformedFileItem(T* element, string message);

	/**
	* @brief Returns an error message to be displayed to the user.
	* @return a string contaning a message to be displayed to the user.
	*/
	string message() const;

	/**
	* @brief Returns a pointer to the malformed element.
	* @return a pointer to the malformed element.
	*/
	T* element() const;
};

template <class T>
MalformedFileItem<T>::MalformedFileItem(T* element, string message) :
	el(element), msg(message) {}

template <class T>
string MalformedFileItem<T>::message() const {
	return msg;
}

template <class T>
T* MalformedFileItem<T>::element() const {
	return el;
}