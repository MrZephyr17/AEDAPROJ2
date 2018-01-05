// ****************************************************************************************************
// ****************************************** MANAGERS_CPP__ ******************************************
// ****************************************************************************************************
#include "managers.h"
#include "Supplements.h"
#include "Table.h"
#include "Form.h"

#include "Company.h"
#include "Employee.h"
#include "Publication.h"
#include "Request.h"
#include "Store.h"



#include <iostream>

namespace Managers {
namespace Aux {
	void toPage(ManagerData &data, Input input) {
		if (input.is.integer) {
			string next = data.nextPage + to_string(input.integer) + ".";
			if (data.menu->has(next)) {
				data.nextPage = next;
				data.leave = true;
			}
			else {
				data.errorLog = "Page not found: " + next;
			}
		}
		if (input.is.plainText) {
			vector<string> v = split(input.plainText, PAGE_SPLITTERS, true);
			if (v.size() > 0) {
				trim(v);
				string next = data.nextPage + join(v, ".") + ".";
				if (data.menu->has(next)) {
					data.nextPage = next;
					data.leave = true;
				}
				else {
					data.errorLog = "Page not found: " + next;
				}
			}
			else {
				data.errorLog = "Command not recognized: " + input.plainText;
			}
		}
	}

	bool validStoreName(string storeName) {
		return isalpha(storeName[0]) && (storeName.length() < 30);
	}

	bool validStoreContact(int storeContact) {
		return (storeContact >= 1e8) && (storeContact < 1e9);
	}

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

	void clear(ManagerData &data) {
		data.is.load = false;
		data.is.create = false;
		data.is.save = false;
		data.is.discard = false;
		data.is.newStore = false;
		data.is.newEmployee = false;
		data.is.newRequest = false;
		data.is.newPublication = false;
		data.errorLog.clear();
		data.infoLog.clear();
		data.token = Token();
	};
}

namespace Writer {
	string writeStoreDetails(Company* company, Store* store)
	{
		string text;
		Employee* emp = store->getManager();
		vector<LocalPublication> pubs = store->getPublications();

		text += encaps("Store Information", SHORT_WIDTH, '=', true) + "\n";
		text += "  >> Store: " + store->getName() + "\n";
		text += "  >> Contact: " + store->getContact() + "\n";
		text += "  >> Manager: " + (emp ? emp->getName() : "---") + "\n";

		Table pubTable("Publications", 3, pubs.size());
		pubTable.header(0, "Name");
		pubTable.header(1, "Price");
		pubTable.header(2, "Stock");
		for (unsigned i = 0; i < pubs.size(); ++i) {
			Publication* pub = pubs[i].getPublication();
			pubTable.data(0, i, pub->getName());
			pubTable.data(1, i, to_string(pub->getPrice()));
			pubTable.data(2, i, to_string(pubs[i].getStock()));
		}

		text += pubTable.write();
		return text;
	}

	string writeStores(Company* company, Store* sel)
	{
		string text;
		auto stores = company->getStores();

		text += encaps("Stores in ICNM", SHORT_WIDTH, '=', true) + "\n";

		unsigned int line = 0;
		for (auto it = stores.cbegin(); it != stores.cend(); ++it) {
			Store* store = *it;
			string tmp = " [" + store->getName() + "] ";
			if (store == sel) tmp = " ->[" + store->getName() + "]<- ";

			if (line > 0 && (line + tmp.size() > SHORT_WIDTH)) {
				text += "\n";
				line = 0;
			}
			text += tmp;
			line += tmp.size();
		}

		text += "\n";
		return text;
	}


	string writePublicationDetails(Company* company, Publication* publication)
	{
		string text;
		string type = publication->getType();
		string name;

		if (type == TYPE_BOOK) {
			Book* book = static_cast<Book*>(publication);
			text += " >> Book: " + book->getName() + "\n";
			text += " >> Description: " + book->getDescription() + "\n";
			text += " >> Collection: " + book->getCollection() + "\n";
			text += " >> Release Date: " + book->getReleaseDate().write() + "\n";
			text += " >>  Price: " + to_string(book->getPrice()) + "\n";
			text += " >>  Edition: " + to_string(book->getEdition()) + "\n";
		}
		else if (type == TYPE_MAGAZINE) {
			Magazine* magazine = static_cast<Magazine*>(publication);
			text += " >> Magazine: " + magazine->getName() + "\n";
			text += " >> Description: " + magazine->getDescription() + "\n";
			text += " >> Collection: " + magazine->getCollection() + "\n";
			text += " >> Release Date: " + magazine->getReleaseDate().write() + "\n";
			text += " >>  Price: " + to_string(magazine->getPrice()) + "\n";
			text += " >>  Volume: " + to_string(magazine->getVolume()) + "\n";
			text += " >>  Number: " + to_string(magazine->getNumber()) + "\n";
		}
		else throw "Invalid type";

		auto stores = company->getStores();
		Table stockTable("Stocks of publication " + publication->getName(), 2, stores.size());
		stockTable.header(0, "Stock");
		stockTable.header(1, "Store");

		unsigned i = 0;
		for (auto store : stores) {
			LocalPublication stock = store->getPublication(publication);
			stockTable.data(0, i, to_string(stock.getStock()));
			stockTable.data(1, i, store->getName());
			++i;
		}

		text += stockTable.write();
		return text;
	}

	string writePublications(Company* company, Publication* sel)
	{
		string text;
		auto publications = company->getPublications();

		text += encaps("Publications in ICNM", SHORT_WIDTH, '=', true) + "\n";

		unsigned int line = 0;
		for (auto it = publications.cbegin(); it != publications.cend(); ++it) {
			Publication* publication = *it;
			string tmp = " [" + publication->getName() + "] ";
			if (publication == sel) tmp = " ->[" + publication->getName() + "]<- ";

			if (line > 0 && (line + tmp.size() > SHORT_WIDTH)) {
				text += "\n";
				line = 0;
			}
			text += tmp;
			line += tmp.size();
		}

		text += "\n";
		return text;
	}


	string writeEmployeeDetails(Company* company, Employee* employee)
	{
		string text;
		Store* store = employee->getStore();

		text += "  >> Employee: " + employee->getName() + "\n";
		text += "  >> Store: " + (store ? store->getName() : "---") + "\n";
		text += "  >> Date of Birth: " + employee->getBirthDate().write() + "\n";
		return text;
	}

	string writeEmployees(Company* company, Employee* sel)
	{
		string text;
		auto employees = company->getEmployees();

		text += encaps("Employees in INCM", SHORT_WIDTH, '=', true) + "\n";

		unsigned int line = 0;
		for (auto it = employees.cbegin(); it != employees.cend(); ++it) {
			Employee* employee = *it;
			string tmp = " [" + employee->getName() + "] ";
			if (employee == sel) tmp = " ->[" + employee->getName() + "]<- ";

			if (line > 0 && (line + tmp.size() > SHORT_WIDTH)) {
				text += "\n";
				line = 0;
			}
			text += tmp;
			line += tmp.size();
		}

		text += "\n";
		return text;
	}


	string writeRequest(Company* company, Request* request)
	{
		string text;

		text += " >>>> From Store: " + request->getStore()->getName() + "\n";
		text += " >>>> Of Publication: " + request->getPublication()->getName() + "\n";
		text += " >> Quantity: " + to_string(request->getQuantity()) + "\n";
		text += " >> Request Date: " + request->getRequestDate().write() + "\n";
		text += " >> Deadline: " + request->getDeliveryLimit().write() + "\n";

		return text;
	}

	string writeRequests(Company* company, Store* store)
	{
		auto reqs = company->getRequests(store);

		Table reqTable("Requests from store " + store->getName(), 4, reqs.size());
		reqTable.header(0, "Quantity");
		reqTable.header(1, "Publication");
		reqTable.header(2, "Deadline");
		reqTable.header(3, "Status");

		unsigned i = 0;
		for (auto req : reqs) {
			reqTable.data(0, i, to_string(req->getQuantity()));
			reqTable.data(1, i, req->getPublication()->getName());
			reqTable.data(2, i, req->getDeliveryLimit().write());
			reqTable.data(3, i, "ACTIVE");
			++i;
		}

		return reqTable.write();
	}

	string writeRequests(Company* company, Publication* publication)
	{
		auto reqs = company->getRequests(publication);

		Table reqTable("Requests of publication " + publication->getName(), 4, reqs.size());
		reqTable.header(0, "Quantity");
		reqTable.header(1, "Store");
		reqTable.header(2, "Deadline");
		reqTable.header(3, "Status");

		unsigned i = 0;
		for (auto req : reqs) {
			reqTable.data(0, i, to_string(req->getQuantity()));
			reqTable.data(1, i, req->getStore()->getName());
			reqTable.data(2, i, req->getDeliveryLimit().write());
			reqTable.data(3, i, "ACTIVE");
			++i;
		}

		return reqTable.write();
	}

	string writeRequests(Company* company, Store* store, Publication* publication)
	{
		auto reqs = company->getRequests(store, publication);

		Table reqTable("Requests", 3, reqs.size());
		reqTable.options.include_header = false;
		reqTable.options.include_title = false;
		reqTable.header(0, "Quantity");
		reqTable.header(1, "Deadline");
		reqTable.header(2, "Status");

		unsigned i = 0;
		for (auto req : reqs) {
			reqTable.data(0, i, to_string(req->getQuantity()));
			reqTable.data(1, i, req->getDeliveryLimit().write());
			reqTable.data(2, i, "ACTIVE");
			++i;
		}

		return reqTable.write();
	}

	string writeRequests(Company* company)
	{
		auto reqs = company->getRequests();

		Table reqTable("List of all Requests in INCM", 5, reqs.size());
		reqTable.header(0, "Quantity");
		reqTable.header(1, "Store");
		reqTable.header(2, "Publication");
		reqTable.header(3, "Deadline");
		reqTable.header(4, "Status");

		unsigned i = 0;
		for (auto req : reqs) {
			reqTable.data(0, i, to_string(req->getQuantity()));
			reqTable.data(1, i, req->getStore()->getName());
			reqTable.data(2, i, req->getPublication()->getName());
			reqTable.data(3, i, req->getDeliveryLimit().write());
			reqTable.data(4, i, "ACTIVE");
			++i;
		}

		return reqTable.write();
	}


	string writeRequestsNumbered(vector<Request*> reqs, unsigned int index)
	{
		Table reqTable("Requests", 7, reqs.size());
		reqTable.header(0, " ");
		reqTable.header(1, "#");
		reqTable.header(2, "Quantity");
		reqTable.header(3, "Store");
		reqTable.header(4, "Publication");
		reqTable.header(5, "Deadline");
		reqTable.header(6, "Status");
		for (unsigned i = 0; i < reqs.size(); ++i) {
			Request* req = reqs[i];
			if (index == (i + 1)) reqTable.data(0, i, "X");
			reqTable.data(1, i, to_string(i + 1));
			reqTable.data(2, i, to_string(req->getQuantity()));
			reqTable.data(3, i, req->getStore()->getName());
			reqTable.data(4, i, req->getPublication()->getName());
			reqTable.data(5, i, req->getDeliveryLimit().write());
			reqTable.data(6, i, "ACTIVE");
		}

		return reqTable.write();
	}

	string writeRequestsNumbered(vector<Request*> reqs, Store* store, unsigned int index)
	{
		Table reqTable("Requests of store " + store->getName(), 6, reqs.size());
		reqTable.header(0, " ");
		reqTable.header(1, "#");
		reqTable.header(2, "Quantity");
		reqTable.header(3, "Publication");
		reqTable.header(4, "Deadline");
		reqTable.header(5, "Status");
		for (unsigned i = 0; i < reqs.size(); ++i) {
			Request* req = reqs[i];
			if (index == (i + 1)) reqTable.data(0, i, "X");
			reqTable.data(1, i, to_string(i + 1));
			reqTable.data(2, i, to_string(req->getQuantity()));
			reqTable.data(3, i, req->getPublication()->getName());
			reqTable.data(4, i, req->getDeliveryLimit().write());
			reqTable.data(5, i, "ACTIVE");
		}

		return reqTable.write();
	}

	string writeRequestsNumbered(vector<Request*> reqs, Publication* publication, unsigned int index)
	{
		Table reqTable("Requests for publication " + publication->getName(), 6, reqs.size());
		reqTable.header(0, " ");
		reqTable.header(1, "#");
		reqTable.header(2, "Quantity");
		reqTable.header(3, "Store");
		reqTable.header(4, "Deadline");
		reqTable.header(5, "Status");
		for (unsigned i = 0; i < reqs.size(); ++i) {
			Request* req = reqs[i];
			if (index == (i + 1)) reqTable.data(0, i, "X");
			reqTable.data(1, i, to_string(i + 1));
			reqTable.data(2, i, to_string(req->getQuantity()));
			reqTable.data(3, i, req->getStore()->getName());
			reqTable.data(4, i, req->getDeliveryLimit().write());
			reqTable.data(5, i, "ACTIVE");
		}

		return reqTable.write();
	}


	string writeSuspended(Company* company, Suspended* suspended)
	{
		string text;
		text += " >>>> From Store: " + suspended->getStore()->getName() + "\n";
		text += " >>>> Of Publication: " + suspended->getPublication()->getName() + "\n";
		text += " >> Quantity: " + to_string(suspended->getQuantity()) + "\n";
		text += " >> Request Date: " + suspended->getRequestDate().write() + "\n";
		text += " >> Deadline: " + suspended->getDeliveryLimit().write() + "\n";
		text += " >>> Suspension Date: " + suspended->getSuspensionDate().write() + "\n";

		return text;
	}

	string writeSuspended(Company* company, Store* store)
	{
		auto suspendeds = company->getSuspendedRequests(store);

		Table susTable("Suspended requests from store " + store->getName(), 4, suspendeds.size());
		susTable.header(0, "Quantity");
		susTable.header(1, "Publication");
		susTable.header(2, "Deadline");
		susTable.header(3, "Status");

		unsigned i = 0;
		for (auto sus : suspendeds) {
			susTable.data(0, i, to_string(sus->getQuantity()));
			susTable.data(1, i, sus->getPublication()->getName());
			susTable.data(2, i, sus->getDeliveryLimit().write());
			susTable.data(3, i, "SUSPENDED");
			++i;
		}

		return susTable.write();
	}

	string writeSuspended(Company* company, Publication* publication)
	{
		auto suspendeds = company->getSuspendedRequests(publication);

		Table susTable("Suspended requests of publication " + publication->getName(), 4, suspendeds.size());
		susTable.header(0, "Quantity");
		susTable.header(1, "Store");
		susTable.header(2, "Deadline");
		susTable.header(3, "Status");

		unsigned i = 0;
		for (auto sus : suspendeds) {
			susTable.data(0, i, to_string(sus->getQuantity()));
			susTable.data(1, i, sus->getStore()->getName());
			susTable.data(2, i, sus->getDeliveryLimit().write());
			susTable.data(3, i, "SUSPENDED");
			++i;
		}

		return susTable.write();
	}

	string writeSuspended(Company* company, Store* store, Publication* publication)
	{
		auto suspendeds = company->getSuspendedRequests(store, publication);

		Table susTable("Suspended requests", 3, suspendeds.size());
		susTable.options.include_header = false;
		susTable.options.include_title = false;
		susTable.header(0, "Quantity");
		susTable.header(1, "Deadline");
		susTable.header(2, "Status");

		unsigned i = 0;
		for (auto sus : suspendeds) {
			susTable.data(0, i, to_string(sus->getQuantity()));
			susTable.data(1, i, sus->getDeliveryLimit().write());
			susTable.data(2, i, "SUSPENDED");
			++i;
		}

		return susTable.write();
	}

	string writeSuspended(Company* company)
	{
		auto suspendeds = company->getSuspendedRequests();

		Table susTable("List of all Suspended requests in INCM", 5, suspendeds.size());
		susTable.header(0, "Quantity");
		susTable.header(1, "Store");
		susTable.header(2, "Publication");
		susTable.header(3, "Deadline");
		susTable.header(4, "Status");

		unsigned i = 0;
		for (auto sus : suspendeds) {
			susTable.data(0, i, to_string(sus->getQuantity()));
			susTable.data(1, i, sus->getStore()->getName());
			susTable.data(2, i, sus->getPublication()->getName());
			susTable.data(3, i, sus->getDeliveryLimit().write());
			susTable.data(4, i, "SUSPENDED");
			++i;
		}

		return susTable.write();
	}


	string writeSuspendedNumbered(vector<Suspended*> suspendeds, unsigned int index)
	{
		Table susTable("Suspended Requests", 7, suspendeds.size());
		susTable.header(0, " ");
		susTable.header(1, "#");
		susTable.header(2, "Quantity");
		susTable.header(3, "Store");
		susTable.header(4, "Publication");
		susTable.header(5, "Deadline");
		susTable.header(6, "Status");
		for (unsigned i = 0; i < suspendeds.size(); ++i) {
			Suspended* sus = suspendeds[i];
			if (index == (i + 1)) susTable.data(0, i, "X");
			susTable.data(1, i, to_string(i + 1));
			susTable.data(2, i, to_string(sus->getQuantity()));
			susTable.data(3, i, sus->getStore()->getName());
			susTable.data(4, i, sus->getPublication()->getName());
			susTable.data(5, i, sus->getDeliveryLimit().write());
			susTable.data(6, i, "ACTIVE");
		}

		return susTable.write();
	}

	string writeSuspendedNumbered(vector<Suspended*> suspendeds, Store* store, unsigned int index)
	{
		Table susTable("Suspended Requests of store " + store->getName(), 6, suspendeds.size());
		susTable.header(0, " ");
		susTable.header(1, "#");
		susTable.header(2, "Quantity");
		susTable.header(3, "Publication");
		susTable.header(4, "Deadline");
		susTable.header(5, "Status");
		for (unsigned i = 0; i < suspendeds.size(); ++i) {
			Suspended* sus = suspendeds[i];
			if (index == (i + 1)) susTable.data(0, i, "X");
			susTable.data(1, i, to_string(i + 1));
			susTable.data(2, i, to_string(sus->getQuantity()));
			susTable.data(3, i, sus->getPublication()->getName());
			susTable.data(4, i, sus->getDeliveryLimit().write());
			susTable.data(5, i, "ACTIVE");
		}

		return susTable.write();
	}

	string writeSuspendedNumbered(vector<Suspended*> suspendeds, Publication* publication, unsigned int index)
	{
		Table susTable("Suspended Requests for publication " + publication->getName(), 6, suspendeds.size());
		susTable.header(0, " ");
		susTable.header(1, "#");
		susTable.header(2, "Quantity");
		susTable.header(3, "Store");
		susTable.header(4, "Deadline");
		susTable.header(5, "Status");
		for (unsigned i = 0; i < suspendeds.size(); ++i) {
			Suspended* sus = suspendeds[i];
			if (index == (i + 1)) susTable.data(0, i, "X");
			susTable.data(1, i, to_string(i + 1));
			susTable.data(2, i, to_string(sus->getQuantity()));
			susTable.data(3, i, sus->getStore()->getName());
			susTable.data(4, i, sus->getDeliveryLimit().write());
			susTable.data(5, i, "ACTIVE");
		}

		return susTable.write();
	}
}
}