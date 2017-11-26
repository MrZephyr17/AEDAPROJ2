// ****************************************************************************************************
// ****************************************** MANAGERS_CPP__ ******************************************
// ****************************************************************************************************
#include "managers.h"

namespace Managers {
namespace Aux {
string writeLogs(ManagerData &data) {
	string text;
	if (data.infoLog.length() > 0) {
		text = wrap(data.infoLog, " >INFO> ") + "\n";
	}
	if (data.errorLog.length() > 0) {
		text += wrap(data.errorLog, " >ERROR> ") + "\n";
	}
	text += wrap(data.instructions, " >>> ");
	text += " >>>>> ";

	return text;
}
/*
void choose_line(ManagerData &data, const Input &input) {
	Line* candidate = data.company->get_line(input.integer);
	if (candidate == nullptr) {
		data.errorLog = "Line not found: " + to_string(input.integer);
	}
	else {
		data.chosen.line = candidate;
		data.is.new_line = true;
	}
}
*/

void clear(ManagerData &data) {
	data.is.load = false;
	data.is.create = false;
	data.is.save = false;
	data.is.discard = false;
	data.is.newStore = false;
	data.is.newCollection = false;
	data.is.newEmployee = false;
	data.is.newRequest = false;
	data.is.newPublication = false;
	data.errorLog.clear();
	data.infoLog.clear();
	data.token = Token();
};

/*
string write(Line* line) {
	return line != nullptr ? "[" + to_string(line->id) + "]" : "";
}
*/
/*
string write_lineIDs(ManagerData &data) {
	auto line = data.chosen.line;
	auto &bus_lines = data.company->bus_lines;

	if (bus_lines.size() == 0) return "No bus lines!\n";

	vector<string> IDs;
	for (auto it = bus_lines.cbegin(); it != bus_lines.cend(); ++it) {
		if (it->second == line) {
			IDs.push_back("-->" + write(line) + "<--");
		}
		else {
			IDs.push_back(write(it->second));
		}
	}

	vector<string> v(1);
	v[0] = " Bus lines:";

	for (auto it = IDs.cbegin(); it != IDs.cend(); ++it) {
		if (v.back().size() + it->size() + 1 > MAX_WIDTH) {
			v.push_back("");
		}
		v.back() += " " + *it;
	}

	return join(v, "\n") + "\n";
}
*/
}
}