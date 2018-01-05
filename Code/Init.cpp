// ****************************************************************************************************
// ******************************************** INIT_CPP__ ********************************************
// ****************************************************************************************************
#include "Company.h"
#include "Publication.h"
#include "Console.h"
#include "Managers.h"
#include "Supplements.h"
#include "Store.h"
#include "Request.h"
#include "Employee.h"
#include <iostream>



void Company::init() {
	menu = new Menu(this);
	this->currentDay.setCurrentDay();

	// ** 1. Read files in order **
	{
		getPublicationsFile();
		getStoresFile();
		getEmployeesFile();
		getRequestsFile();
		getSuspendedRequestsFile();

		{
			cout << " Publications File: " << publicationsFileName << endl;
			cout << " Stores File: " << storesFileName << endl;
			cout << " Employees File: " << employeesFileName << endl;
			cout << " Requests File: " << requestsFileName << endl;
			cout << " Suspended Requests File: " << suspendedRequestsFileName << endl;
		}

		readPublicationsFile();
		readStoresFile();
		readEmployeesFile();
		readRequestsFile();
		readSuspendedRequestsFile();
		for (auto it1 : publications) cout << (it1)->writeInfo();
		
		for (auto it2 : stores) cout << (it2)->writeInfo();

		for (auto it3 : employees) cout << (it3)->writeInfo();

		for (auto it4 : productionPlan) cout << (it4)->writeInfo();

		for (auto it5 : suspendedRequests) cout << (it5)->writeInfo();

		cin.get();

		//system("cls");
	}

	{
		// ....
	}

	// ** 2. Initiate pages and menu **
	initMenu();

	// ** 3. Interactive Menu **
	menu->init("", "4.");

	// ** 4. Exit & Save **
	{
		savePublicationsToFile();
		saveStoresToFile();
		saveEmployeesToFile();
		saveRequestsToFile();
		saveSuspendedRequestsToFile();
		cout << menu->writeLog();
		cout << "Program terminated successfully...." << endl;
	}

	// End
}


void Company::initMenu() {
	string header;

	// Title HEADER
	{
		header = " ____  __  __  ____  ____  ____  _  _  ___    __      _  _    __    ___  ____  _____  _  _    __    __   \n"
				 "(_  _)(  \\/  )(  _ \\(  _ \\( ___)( \\( )/ __)  /__\\    ( \\( )  /__\\  / __)(_  _)(  _  )( \\( )  /__\\  (  )  \n"
				 " _)(_  )    (  )___/ )   / )__)  )  ( \\__ \\ /(__)\\    )  (  /(__)\\( (__  _)(_  )(_)(  )  (  /(__)\\  )(__ \n"
				 "(____)(_/\\/\\_)(__)  (_)\\_)(____)(_)\\_)(___/(__)(__)  (_)\\_)(__)(__)\\___)(____)(_____)(_)\\_)(__)(__)(____)\n"
				 "                                                                                                         \n"
				 "              ___    __    ___    __      ____    __      __  __  _____  ____  ____    __                \n"
				 "             / __)  /__\\  / __)  /__\\    (  _ \\  /__\\    (  \\/  )(  _  )( ___)(  _ \\  /__\\               \n"
				 "            ( (__  /(__)\\ \\__ \\ /(__)\\    )(_) )/(__)\\    )    (  )(_)(  )__)  )(_) )/(__)\\              \n"
				 "             \\___)(__)(__)(___/(__)(__)  (____/(__)(__)  (_/\\/\\_)(_____)(____)(____/(__)(__)             \n\n";
	}


	// Page 0. CHECK
	{
		string text = header;
		text += encaps(" � Main Menu � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Lookup information on stores, publications, employees and requests.\n";
		text += "  ** \n";
		text += "  **  2. Edit data on stores and employees, create books and magazines...\n";
		text += "  ** \n";
		text += "  **  3. Manage requests: add requests, delete requests, suspend requests...\n";
		text += "  ** \n";
		text += "  **  4. Save & Exit.\n";
		text += "  **   If you do not wish to save any changes, you can just close the app.\n";
		text += "  ** \n\n";
		text += menu->writeLog();
		text += "\n";
		menu->pages[""] = Page("", text, menu, Managers::Navigator);
	}


	// Page 1. CHECK
	{
		string text = header;
		text += encaps(" � (1) Lookup information on stores, publications, and more � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. List of stores - see also stock and pending requests per publication.\n";
		text += "  ** \n";
		text += "  **  2. List of publications - see also stock and pending requests per store.\n";
		text += "  ** \n";
		text += "  **  3. List of employees - check their personal information and working status.\n";
		text += "  ** \n";
		text += "  **  4. Detailed list of all active requests.\n";
		text += "  ** \n";
		text += "  **  5. Detailed list of suspended requests.\n";
		text += "  ** \n";
		menu->pages["1."] = Page("", text, menu, Managers::Navigator);
	}

	// Page 1.1. CHECK
	{
		string text = header;
		text += encaps(" � (1.1) List of Stores - Stock and pending Requests per publication � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.1."] = Page("1.", text, menu, Managers::Controller11);
	}

	// Page 1.2. CHECK
	{
		string text = header;
		text += encaps(" � (1.2) List of Publications - Stock and pending Requests per store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.2."] = Page("1.", text, menu, Managers::Controller12);
	}

	// Page 1.3. CHECK
	{
		string text = header;
		text += encaps(" � (1.3) List of Employees - Personal information and working status � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.3."] = Page("1.", text, menu, Managers::Controller13);
	}

	// Page 1.4. CHECK
	{
		string text = header;
		text += encaps(" � (1.4) Detailed list of all active requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.4."] = Page("1.", text, menu, Managers::Controller14);
	}

	// Page 1.5. CHECK
	{
		string text = header;
		text += encaps(" � (1.5) Detailed list of suspended requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.5."] = Page("1.", text, menu, Managers::Controller15);
	}


	// Page 2. CHECK
	{
		string text = header;
		text+= encaps(" � (2) Edit data on stores and employees, create books and magazines... � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Edit Stores - add new stores, update them and remove them.\n";
		text += "  ** \n";
		text += "  **  2. Edit Publications - create new books and magazines, reform old ones.\n";
		text += "  ** \n";
		text += "  **  3. Edit Employees - add new employees, employ them and reform them.\n";
		text += "  ** \n";
		menu->pages["2."] = Page("", text, menu, Managers::Navigator);
	}
	
	// Page 2.1. CHECK
	{
		string text = header;
		text+= encaps(" � (2.1) Edit Stores � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add a Store.\n";
		text += "  ** \n";
		text += "  **  2. Update/Edit a Store.\n";
		text += "  ** \n";
		text += "  **  3. Remove a Store.\n";
		text += "  ** \n";
		menu->pages["2.1."] = Page("2.", text, menu, Managers::Navigator);

	}

	// Page 2.1.1. CHECK
	{
		string text = header;
		text += encaps(" � (2.1.1) Add a Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.1."] = Page("2.1.", text, menu, Managers::Controller211);
	}

	// Page 2.1.2. CHECK
	{
		string text = header;
		text += encaps(" � (2.1.2) Update/Edit a Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.2."] = Page("2.1.", text, menu, Managers::Controller212);
	}

	// Page 2.1.3. CHECK
	{
		string text = header;
		text += encaps(" � (2.1.3) Remove a Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.3."] = Page("2.1.", text, menu, Managers::Controller213);
	}

	// Page 2.2. CHECK
	{
		string text = header;
		text += encaps(" � (2.2) Edit Publications � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Create new Book or Magazine.\n";
		text += "  ** \n";
		text += "  **  2. Reform an old Publication.\n";
		text += "  ** \n";
		menu->pages["2.2."] = Page("2.", text, menu, Managers::Navigator);
	}

	// Page 2.2.1. CHECK
	{
		string text = header;
		text += encaps(" � (2.2.1) Create Book or Magazine � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.2.1."] = Page("2.2.", text, menu, Managers::Controller221);
	}

	// Page 2.2.2. CHECK
	{
		string text = header;
		text += encaps(" � (2.2.2) Reform an old Publication � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.2.2."] = Page("2.2.", text, menu, Managers::Controller222);
	}

	// Page 2.3. CHECK
	{
		string text = header;
		text += encaps(" � (2.3) Edit employees � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add an Employee.\n";
		text += "  ** \n";
		text += "  **  2. Designate Employees to existing stores.\n";
		text += "  ** \n";
		text += "  **  3. Reform an Employee.\n";
		text += "  ** \n";
		menu->pages["2.3."] = Page("2.", text, menu, Managers::Navigator);

	}

	// Page 2.3.1. CHECK
	{
		string text = header;
		text += encaps(" � (2.3.1) Add an Employee � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.1."] = Page("2.3.", text, menu, Managers::Controller231); // mudar 
	}

	// Page 2.3.2. CHECK
	{
		string text = header;
		text += encaps(" � (2.3.2) Designate an Employee to a store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.2."] = Page("2.3.", text, menu, Managers::Controller232); // mudar 
	}

	// Page 2.3.3. CHECK
	{
		string text = header;
		text += encaps(" � (2.3.3) Reform an Employee � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.3."] = Page("2.3.", text, menu, Managers::Controller233); // mudar 
	}


	// Page 3. CHECK
	{
		string text = header;
		text += encaps(" � (3) Manage Requests � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Create new Stock Requests.\n";
		text += "  ** \n";
		text += "  **  2. Delete pending Stock Requests.\n";
		text += "  ** \n";
		text += "  **  3. Suspend pending Stock Requests.\n";
		text += "  ** \n";
		text += "  **  4. End suspension of Stock Requests.\n";
		text += "  ** \n";
		text += "  **  5. Remove suspended Stock Requests.\n";
		text += "  ** \n";
		text += "  **  6. Postpone Stock Requests deadlines.\n";
		text += "  ** \n";
		menu->pages["3."] = Page("", text, menu, Managers::Navigator);
	}

	// Page 3.1. CHECK
	{
		string text = header;
		text += encaps(" � (3.1) Create Stock Requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.1."] = Page("3.", text, menu, Managers::Controller31); 
	}

	// Page 3.2. CHECK
	{
		string text = header;
		text += encaps(" � (3.2) Delete (pending) Stock Requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.2."] = Page("3.", text, menu, Managers::Controller32);
	}

	// Page 3.3. CHECK
	{
		string text = header;
		text += encaps(" � (3.3) Suspend (pending) Stock Requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.3."] = Page("3.", text, menu, Managers::Controller33);
	}

	// Page 3.4. CHECK
	{
		string text = header;
		text += encaps(" � (3.4) End suspension of Stock Requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.4."] = Page("3.", text, menu, Managers::Controller34);
	}

	// Page 3.5. CHECK
	{
		string text = header;
		text += encaps(" � (3.5) Remove suspended Stock Requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.5."] = Page("3.", text, menu, Managers::Controller35);
	}

	// Page 3.6. CHECK
	{
		string text = header;
		text += encaps(" � (3.6) Postpone Stock Requests deadlines � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.6."] = Page("3.", text, menu, Managers::Controller36);
	}



	// Page 4. CHECK
	{
		string text = header;
		text += encaps(" � (4) Exit & Save � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["4."] = Page("", text, menu, Managers::Navigator);
	}
}
