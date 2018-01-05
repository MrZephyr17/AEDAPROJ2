#pragma once
// ****************************************************************************************************
// ********************************************* FORM_H__ *********************************************
// ****************************************************************************************************
#include "Classes.h"

struct FormOptions {
	char title_encaps = '=';
	char title_separator = '\0';
	size_t title_width = MAIN_WIDTH;
	string title_lead = "     ";
	string line_lead = "     ";
	string selected_lead = " --> ";
	string footnote_lead = "      ";
	string idspace = "  ";
	string pairing = ": ";
	string empty_replacer;
	string entry_separator;
	bool include_title = true;
	bool include_id = false;
	bool include_footnote = false;
};

struct FormEntry {
	string id;
	string left;
	string right;
	string footnote;

	bool selected = false;

	// ** Constructor **
	FormEntry(string id, string left, string right = "", string footnote = "");
	FormEntry() = default;
};

class Form {
public:
	FormOptions options;
	string title;
	vector<FormEntry> data;

	// ** Methods **
	Form& add(FormEntry entry);
	Form& remove(const string& id);
	Form& toggle_all(bool selected = true);
	bool has(const string& id) const;
	FormEntry& get(const string& id);
	string& right(const string& id);
	bool pop();
	void clear();
	void empty();

	string write() const;

	Form(string title);
	Form() = default;

private:
	string write_entry(const FormEntry& entry) const;
};