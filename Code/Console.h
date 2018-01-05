#pragma once
// ****************************************************************************************************
// ******************************************* CONSOLE_H__ ********************************************
// ****************************************************************************************************
#include "Classes.h"



// **************************************************
// ****************** Class INPUT *******************
// **************************************************
struct Input {
private:
	struct InputType {
		bool ctrlZ = false;
		bool integer = false;
		bool plainText = false;
		bool freeEnter = false;
		bool other = false;

		bool positive = false;
		bool nonnegative = false;
		bool empty = false;
	};
public:
	InputType is;
	int integer = 0;
	string plainText;
	void write() const;
};



// **************************************************
// ****************** Class TOKEN *******************
// **************************************************
struct Token {
private:
	struct TokenType {
		bool keyOnly = false;
		bool keyOrder = false;
		bool keyValue = false;
		bool full = false;
	};
public:
	TokenType is;
	string key;
	unsigned order = 0;
	Input value;
	void write() const;
};



// **************************************************
// *************** Class INPUT_READER ***************
// **************************************************
class InputReader {
public:
	static Input extract(string str = "");
	static Input classify(string str);
	static Token tokenize(string str);
};



// **************************************************
// ******************* Class PAGE *******************
// **************************************************
class Page {
public:
	Menu* menu;
	string father;
	string mainContent;

	void init() const;

	Page(string father, string main_content, Menu* menu, Manager* manager);
	Page() = default;

private:
	Manager* manager;
};



// **************************************************
// ******************* Class MENU *******************
// **************************************************
class Menu {
public:
	friend class Page;
	map<string, Page> pages;
	Company* const company;
	string nextPage;
	vector<string> consoleLog;

	bool has(const string& pageID) const;
	void toPage(const string& pageID);
	void init(string entry_page, string exit_page);
	string writeLog() const;

	Menu(Company* company);
};



// **************************************************
// *************** Class MANAGER_DATA ***************
// ************** VERSION FOR AEDA 2017 *************
// **************************************************
struct ManagerData {
private:
	struct State {
		bool clear = true;
		bool load = false;
		bool create = false;

		bool save = false;
		bool discard = false;
		bool editing = false;
		bool creating = false;

		bool newStore = false;
		bool newEmployee = false;
		bool newRequest = false;
		bool newPublication = false;
	};
	struct Chosen {
		Store* store = nullptr;
		Employee* employee = nullptr;
		Request* request = nullptr;
		Suspended* suspended = nullptr;
		Publication* publication = nullptr;
	};
public:
	Menu* const menu;
	Company* const company;
	string& nextPage;
	string instructions;
	string infoLog, errorLog;
	bool leave = false;

	State is;
	Chosen chosen;
	InputReader reader;
	Token token;

	ManagerData(const Page& page);
};