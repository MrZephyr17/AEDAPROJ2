#pragma once
// ****************************************************************************************************
// ******************************************** TABLE_H__ *********************************************
// ****************************************************************************************************
#include "Classes.h"

struct TableOptions {
	char title_encaps = '=';
	char title_separator = '\0';
	char header_separator = '\0';
	char data_separator = '\0';
	char footnote_separator = '\0';
	string column_space = " ";
	string line_lead = " ";
	string footnote_lead = " ";
	bool include_title = true;
	bool include_header = true;
	bool include_footnote = false;
};

struct TableEntry {
	string text;
};

class Table {
public:
	// ** Output configurations **
	TableOptions options;

	// ** Getters and setters **
	string title() const;
	Table& title(string str);
	string header(size_t column) const;
	Table& header(size_t column, string entry);
	Table& header_push(string entry);
	string data(size_t column, size_t line) const;
	Table& data(size_t column, size_t line, string entry);
	Table& data_push(size_t column, string entry);
	string footnote() const;
	Table& footnote(string str);

	// ** Methods **
	void resize(size_t width, size_t height = 0);
	pair<size_t, size_t> size() const;
	string write() const;

	// ** Constructors **
	Table(string title, size_t width, size_t height);
	Table(string title);
	Table() = default;

private:
	string title_;
	vector<TableEntry> header_;
	vector<vector<TableEntry>> data_;
	string footnote_;

	pair<vector<size_t>, size_t> analyze() const;
	string write_title(size_t table_width) const;
	string write_header(size_t table_width, const vector<size_t> &column_widths) const;
	string write_data(size_t table_width, const vector<size_t> &column_widths, size_t number_of_lines) const;
	string write_footnote(size_t table_width) const;
};