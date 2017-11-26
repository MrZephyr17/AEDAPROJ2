#pragma once
// ****************************************************************************************************
// ******************************************** TABLE_H__ *********************************************
// ****************************************************************************************************
#include "form.h"
#include "supplements.h"


FormEntry::FormEntry(string id, string left, string right, string footnote) :
	id(id), left(left), right(right), footnote(footnote) {}

Form& Form::add(FormEntry entry) {
	data.push_back(entry);
	return *this;
}

Form& Form::remove(const string& id) {
	for (auto it = data.begin(); it != data.end(); ++it) {
		if (it->id == id) {
			data.erase(it);
			break;
		}
	}
	return *this;
}

Form& Form::toggle_all(bool selected) {
	for (auto it = data.begin(); it != data.end(); ++it) {
		it->selected = selected;
	}
	return *this;
}

bool Form::has(const string& id) const {
	for (auto it = data.cbegin(); it != data.end(); ++it) {
		if (it->id == id) return true;
	}
	return false;
}

FormEntry& Form::get(const string& id) {
	for (auto it = data.begin(); it != data.end(); ++it) {
		if (it->id == id) return *it;
	}
	assert(false);
	throw false;
}

string& Form::right(const string& id) {
	return get(id).right;
}

bool Form::pop() {
	if (data.size() == 0) {
		return false;
	}
	else {
		data.pop_back();
		return true;
	}
}

void Form::clear() {
	for (auto it = data.begin(); it != data.end(); ++it) {
		it->right.clear();
	}
}

void Form::empty() {
	data.clear();
}

string Form::write() const {
	string text;

	if (options.include_title) {
		size_t width = options.title_width - options.title_lead.length();
		if (options.title_encaps != '\0') {
			text = options.title_lead
				+ encaps(" " + title + " ", width, options.title_encaps, true);
		}
		else {
			text += options.title_lead + title;
		}
		if (options.title_separator != '\0') {
			text += options.title_lead + string(width, options.title_separator);
		}
		text += "\n";
	}

	for (auto it = data.cbegin(); it != data.cend(); ++it) {
		text += write_entry(*it);
		text += options.entry_separator;
	}

	return text;
}

Form::Form(string title) :
	title(title) {}

string Form::write_entry(const FormEntry &entry) const {
	string text;
	if (entry.selected) {
		text = options.selected_lead;
	}
	else {
		text = options.line_lead;
	}

	if (options.include_id) {
		text += "(" + entry.id + ")" + options.idspace;
	}

	text += entry.left + options.pairing;

	if (entry.right.length() > 0) {
		text += entry.right + "\n";
	}
	else {
		text += options.empty_replacer + "\n";
	}

	if (options.include_footnote) {
		text += options.footnote_lead + entry.footnote + "\n";
	}

	return text;
}


