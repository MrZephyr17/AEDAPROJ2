// ********************************************************************************
// ********************************* TABLE_CPP__ **********************************
// ********************************************************************************
#include "table.h"
#include "supplements.h"
#include <numeric> // std::accumulate


// ** Accessors **

string Table::title() const {
	return title_;
}

Table& Table::title(string str) {
	title_ = str;
	return *this;
}

string Table::header(size_t column) const {
	assert(column < header_.size());
	return header_[column].text;
}

Table& Table::header(size_t column, string entry) {
	if (column >= header_.size()) {
		header_.resize(column + 1);
	}
	header_[column].text = entry;
	return *this;
}

Table& Table::header_push(string entry) {
	TableEntry new_entry;
	new_entry.text = entry;
	header_.push_back(new_entry);
	return *this;
}

string Table::data(size_t column, size_t line) const {
	assert(column < data_.size() && line < data_[column].size());
	return data_[column][line].text;
}

Table& Table::data(size_t column, size_t line, string entry) {
	if (column >= data_.size()) {
		data_.resize(column + 1);
	}
	if (line >= data_[column].size()) {
		data_[column].resize(line + 1);
	}
	data_[column][line].text = entry;
	return *this;
}

Table& Table::data_push(size_t column, string entry) {
	if (column >= data_.size()) {
		data_.resize(column + 1);
	}
	TableEntry new_entry;
	new_entry.text = entry;
	data_[column].push_back(new_entry);
	return *this;
}

string Table::footnote() const {
	return footnote_;
}

Table& Table::footnote(string str) {
	footnote_ = str;
	return *this;
}





// ** Methods **

void Table::resize(size_t width, size_t height) {
	header_.resize(width);
	data_.resize(width);
	for (auto it = data_.begin(); it != data_.end(); ++it) {
		it->resize(height);
	}
}

pair<size_t, size_t> Table::size() const {
	size_t width, height = 0;

	if (options.include_header) {
		width = header_.size();
	}
	else {
		width = data_.size();
	}

	for (auto it = data_.cbegin(); it != data_.cend(); ++it) {
		if (height < it->size()) {
			height = it->size();
		}
	}

	return{ width, height };
}





// ** Constructors **

Table::Table(string title, size_t width, size_t height) :
	title_(title) {
	resize(width, height);
}

Table::Table(string title) :
	title_(title) {}





// ** Writers **

pair<vector<size_t>, size_t> Table::analyze() const {
	auto sizes = size();
	vector<size_t> column_widths(sizes.first, 0);

	if (options.include_header) {
		for (size_t i = 0; i < header_.size(); ++i) {
			column_widths[i] = header_[i].text.length();
		}
	}

	for (size_t i = 0; i < data_.size(); ++i) {
		for (auto li = data_[i].cbegin(); li != data_[i].cend(); ++li) {
			if (column_widths[i] < li->text.length()) {
				column_widths[i] = li->text.length();
			}
		}
	}

	return{ column_widths, sizes.second };
}

string Table::write() const {
	size_t number_columns;
	auto sizes = analyze();
	if (options.include_header) {
		number_columns = header_.size();
	}
	else {
		number_columns = data_.size();
	}
	size_t table_width = accumulate(sizes.first.begin(), sizes.first.end(), 0);
	table_width += options.column_space.length() * (number_columns - 1);

	string text;

	// Title
	if (options.include_title) {
		text = write_title(table_width);
	}

	if (options.include_header) {
		text += write_header(table_width, sizes.first);
	}

	text += write_data(table_width, sizes.first, sizes.second);

	if (options.include_footnote) {
		text += write_footnote(table_width);
	}

	return text;
}

string Table::write_title(size_t table_width) const {
	string text = options.line_lead;
	text += encaps(" " + title_ + " ", table_width, options.title_encaps, true) + "\n";

	if (options.title_separator != '\0') {
		text += options.line_lead + string(table_width, options.title_separator) + "\n";
	}

	return text;
}

string Table::write_header(size_t table_width, const vector<size_t> &column_widths) const {
	string text = options.line_lead;

	for (size_t i = 0; i < header_.size(); ++i) {
		if (i > 0) text += options.column_space;
		text += encaps(header_[i].text, column_widths[i]);
	}
	text += "\n";

	if (options.header_separator != '\0') {
		text += options.line_lead + string(table_width, options.header_separator) + "\n";
	}

	return text;
}

string Table::write_data(size_t table_width, const vector<size_t> &column_widths, size_t height) const {
	string text;
	string line_sep;

	if (options.data_separator != '\0') {
		line_sep = options.line_lead + string(table_width, options.data_separator) + "\n";
	}

	for (size_t i = 0; i < height; ++i) {
		text += options.line_lead;
		for (size_t j = 0; j < data_.size(); ++j) {
			if (j > 0) text += options.column_space;
			if (i < data_[j].size()) {
				text += encaps(data_[j][i].text, column_widths[j]);
			}
			else {
				text += encaps("", column_widths[j]);
			}
		}
		text += "\n" + line_sep;
	}

	if (options.footnote_separator != '\0') {
		text += options.line_lead + string(table_width, options.footnote_separator) + "\n";
	}

	return text;
}

string Table::write_footnote(size_t table_width) const {
	return options.line_lead + options.footnote_lead + footnote_ + "\n";
}