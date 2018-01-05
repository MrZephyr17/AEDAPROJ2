// ****************************************************************************************************
// ****************************************** CONSOLE_CPP__ *******************************************
// ****************************************************************************************************
#include "console.h"
#include "supplements.h"
#include <iostream>
#include <sstream>

void Input::write() const {
	stringstream ss("Input:");
	ss << boolalpha;
	ss << "\n  is.ctrlZ = " << is.ctrlZ;
	ss << "\n  is.free_enter = " << is.freeEnter;
	ss << "\n  is.integer = " << is.integer;
	ss << "\n  is.plain_text = " << is.plainText;
	ss << "\n  is.other = " << is.other;
	ss << "\n  is.positive = " << is.positive;
	ss << "\n  is.nonnegative = " << is.nonnegative;
	ss << "\n  is.empty = " << is.empty;
	ss << "\n integer = " << to_string(integer);
	ss << "\n plain_text = " << plainText;
	cout << ss.str() << endl;
}

void Token::write() const {
	stringstream ss("Token:");
	ss << boolalpha;
	ss << "\n  is.key_only = " << is.keyOnly;
	ss << "\n  is.key_order = " << is.keyOrder;
	ss << "\n  is.key_value = " << is.keyValue;
	ss << "\n  is.full = " << is.full;
	ss << "\n key = " << key;
	ss << "\n order = " << to_string(order);
	ss << "\n  value:";
	cout << ss.str() << endl;
	value.write();
}

ManagerData::ManagerData(const Page& page) :
	menu(page.menu), company(page.menu->company), nextPage(page.menu->nextPage) {}

Input InputReader::extract(string str) {
	if (str.length() > 0) {
		cout << str;
	}

	string command;
	getline(cin, command);

	Input input;

	if (trim(command).length() == 0) {
		if (cin.eof()) {
			input.is.ctrlZ = true;
		}
		else {
			input.is.freeEnter = true;
		}
	}
	else {
		input = classify(trim(command));
	}

	cin.clear();
	return input;
}

Input InputReader::classify(string str) {
	Input input;

	istringstream ss(str);
	int n = 0;
	string text;

	ss >> n;
	getline(ss, text);
	input.plainText = str;

	if (ss.eof() && ss.fail() && trim(text).length() == 0) {
		input.is.integer = true;
		input.integer = n;
		input.is.nonnegative = n >= 0;
		input.is.positive = n > 0;
	}
	else if (ss.eof() != ss.fail()) {
		input.is.plainText = true;
		input.is.empty = str.length() == 0;
	}
	else {
		input.is.other = true;
	}

	return input;
}

Token InputReader::tokenize(string str) {
	Token token;
	vector<string> parts = split(str, TOKEN_SPLITTERS);
	if (parts.size() > 2) {
		token.key = str;
		token.is.keyOnly = true;
	}
	else {
		string first = trim(parts[0]);
		size_t end_key = first.find_last_not_of("0123456789");
		// Key purely numeric
		if (end_key == string::npos) {
			token.key = first;
			token.is.keyOnly = true;
		}
		// Key has no numeric component, same thing
		else if (end_key + 1 == first.size()) {
			token.key = first;
			token.is.keyOnly = true;
		}
		else {
			token.key = first.substr(0, end_key + 1);
			token.order = stoi(first.substr(end_key + 1));
			token.is.keyOrder = true;
		}

		if (parts.size() == 2) {
			token.value = classify(trim(parts[1]));
			if (token.is.keyOnly) {
				token.is.keyOnly = false;
				token.is.keyValue = true;
			}
			else {
				token.is.keyOrder = false;
				token.is.full = true;
			}
		}
	}

	return token;
}

void Page::init() const {
	manager(*this);
}

Page::Page(string father, string main_content, Menu* menu, Manager* manager) :
	father(father), mainContent(main_content), menu(menu), manager(manager) {}

bool Menu::has(const string & pageID) const {
	return pages.find(pageID) != pages.end();
}

void Menu::toPage(const string& pageID) {
	assert(has(pageID));
	pages[pageID].init();
}

void Menu::init(string entry_page, string exit_page) {
	nextPage = entry_page;
	do {
		toPage(nextPage);
	} while (nextPage != exit_page);
}

string Menu::writeLog() const {
	if (consoleLog.size() > 0) {
		return wrap(join(consoleLog, "\n"), " --> Log: ");
	}
	else {
		return "";
	}
}

Menu::Menu(Company* company) :
	company(company) {}
