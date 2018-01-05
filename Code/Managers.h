#pragma once
// ****************************************************************************************************
// ******************************************* MANAGERS_H__ *******************************************
// ****************************************************************************************************
#include "Classes.h"
#include "Console.h"


namespace Managers {
namespace Aux {
void toPage(ManagerData &data, Input input);
bool validStoreName(string storeName);
bool validStoreContact(int storeContact);
string writeLogs(ManagerData &data);
void clear(ManagerData &data);
}

namespace Writer {
string writeStoreDetails(Company* company, Store* store);
string writeStores(Company* company, Store* sel = nullptr);

string writePublicationDetails(Company* company, Publication* publication);
string writePublications(Company* company, Publication* sel = nullptr);

string writeEmployeeDetails(Company* company, Employee* employee);
string writeEmployees(Company* company, Employee* sel = nullptr);

string writeRequest(Company* company, Request* request);
string writeRequests(Company* company, Store* store);
string writeRequests(Company* company, Publication* publication);
string writeRequests(Company* company, Store* store, Publication* publication);
string writeRequests(Company* company);

string writeRequestsNumbered(vector<Request*> reqs, unsigned int index = 0);
string writeRequestsNumbered(vector<Request*> reqs, Store* store, unsigned int index = 0);
string writeRequestsNumbered(vector<Request*> reqs, Publication* publication, unsigned int index = 0);

string writeSuspended(Company* company, Suspended* suspended);
string writeSuspended(Company* company, Store* store);
string writeSuspended(Company* company, Publication* publication);
string writeSuspended(Company* company, Store* store, Publication* publication);
string writeSuspended(Company* company);

string writeSuspendedNumbered(vector<Suspended*> suspendeds, unsigned int index = 0);
string writeSuspendedNumbered(vector<Suspended*> suspendeds, Store* store, unsigned int index = 0);
string writeSuspendedNumbered(vector<Suspended*> suspendeds, Publication* publication, unsigned int index = 0);
}

void Navigator(const Page& page);

void Controller11(const Page& page);
void Controller12(const Page& page);
void Controller13(const Page& page);
void Controller14(const Page& page);
void Controller15(const Page& page);

void Controller211(const Page& page);
void Controller212(const Page& page);
void Controller213(const Page& page);

void Controller221(const Page& page);
void Controller222(const Page& page);

void Controller231(const Page& page);
void Controller232(const Page& page);
void Controller233(const Page& page);

void Controller31(const Page& page);
void Controller32(const Page& page);
void Controller33(const Page& page);
void Controller34(const Page& page);
void Controller35(const Page& page);
void Controller36(const Page& page);
}