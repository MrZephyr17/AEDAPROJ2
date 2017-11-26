#pragma once
// ****************************************************************************************************
// ******************************************* MANAGERS_H__ *******************************************
// ****************************************************************************************************
#include "Classes.h"
#include "Company.h"

#include "Console.h"
#include "Supplements.h"
#include "Table.h"
#include "Form.h"

#include <iostream>

namespace Managers {
namespace Aux {
	string writeLogs(ManagerData &data);
	//void choose_line(ManagerData &data, const Input &input);
	//void choose_stop(ManagerData &data, const Input &input);
	//void choose_driver(ManagerData &data, const Input &input);
	void clear(ManagerData &data);
	//string write(Line* line);
	//string write(Stop* stop);
	//string write(Driver* driver);
	//string write_lineIDs(ManagerData &data);
	//string write_stopIDs(ManagerData &data);
	//string write_driverIDs(ManagerData &data);
}

void Navigator(const Page& page);
void Controller11(const Page& page);
void Controller12(const Page& page);
void Controller13(const Page& page);
void Controller14(const Page& page);
void Controller211(const Page& page);
void Controller212(const Page& page);
void Controller213(const Page& page);
}