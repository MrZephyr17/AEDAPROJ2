// ****************************************************************************************************
// ******************************************** INIT_CPP__ ********************************************
// ****************************************************************************************************
#include "Company.h"
#include "Collection.h"
#include "Console.h"
#include "Managers.h"
#include "Supplements.h"
#include "Store.h"
#include "Request.h"
#include "Employee.h"
#include <iostream>


void Company::init() {
	menu = new Menu(this);

	// ** 1. Read files in order **
	{
		getCollectionsFile();

		getStoresFile();
		getEmployeesFile();
		getRequestsFile();

		readCollectionsFile();
		for (auto it1 : collections) cout << (it1)->writeInfo();
		readStoresFile();
		for (auto it2 : stores) cout << (it2)->writeInfo();

		readEmployeesFile();
		for (auto it3 : employees) cout << (it3)->writeInfo();

		readRequestsFile();
		for (auto it4 : productionPlan) cout << (it4)->writeInfo();


		cin.get();

		//system("cls");
	}

	// ** 2. Initiate pages and menu **
	initMenu();

	// ** 3. Interactive Menu **
	menu->init("", "4.");

	// ** 4. Exit & Save **
	{
		saveCollectionsToFile();
		saveStoresToFile();
		saveEmployeesToFile();
		saveRequestsToFile();
		cout << menu->writeLog();
		cout << "Program terminated successfully...." << endl;
	}

	// End
}


void Company::initMenu() {
	string header;

	// Title HEADER
	// Get creative motherfuckers
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

	// Page 0.
	{
		string text = header;
		text += encaps(" � Main Menu � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Lookup information on stores, publications, and more.\n";
		text += "  ** \n";
		text += "  **  2. Edit data on stores and employees, and create books and collections.\n";
		text += "  ** \n";
		text += "  **  3. Manage requests.\n";
		text += "  ** \n";
		text += "  **  4. Save & Exit.\n";
		text += "  ** \n\n";
		text += menu->writeLog();
		text += "\n";
		menu->pages[""] = Page("", text, menu, Managers::Navigator);
	}

	// Page 1.
	{
		string text = header;
		text += encaps(" � (1) Lookup information on stores, publications, and more � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. List of stores; sales and other information per store.\n";
		text += "  ** \n";
		text += "  **  2. List of collections available.\n";
		text += "  ** \n";
		text += "  **  3. List of employees.\n";
		text += "  ** \n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["1."] = Page("", text, menu, Managers::Navigator);
	}

	// Page 1.1.
	{
		string text = header;
		text += encaps(" � (1.1) List of stores; sales and other information per store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.1."] = Page("1.", text, menu, Managers::Controller11); //mudar
	}

	//Page 1.2
	{
		string text = header;
		text += encaps(" � (1.2) List of collections available � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.2."] = Page("1.", text, menu, Managers::Controller12); // mudar 
	}

	//Page 1.3
	{
		string text = header;
		text += encaps(" � (1.2) List of employees � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["1.3."] = Page("1.", text, menu, Managers::Controller13); // mudar 
	}

	//Page 2.
	{
		string text = header;
		text+= encaps(" � (2) Edit data on stores and employees, and create books and collections � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Edit stores.\n";
		text += "  ** \n";
		text += "  **  2. Edit employees.\n";
		text += "  ** \n";
		text += "  **  3. Edit collections.\n";
		text += "  ** \n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["2."] = Page("", text, menu, Managers::Navigator);
	}
	

	//Page 2.1
	{
		string text = header;
		text+= encaps(" � (2.1) Edit stores � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add store.\n";
		text += "  ** \n";
		text += "  **  2. Edit store.\n";
		text += "  ** \n";
		text += "  **  3. Remove store.\n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["2.1."] = Page("2.", text, menu, Managers::Navigator);

	}

	//Page 2.2
	{
		string text = header;
		text += encaps(" � (2.2) Edit employees � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add employee.\n";
		text += "  ** \n";
		text += "  **  2. Remove employee.\n";
		text += "  ** \n";
		text += "  **  3. .....\n";
		text += "  ** \n";
		menu->pages["2.2."] = Page("2.", text, menu, Managers::Navigator);

	}

	//Page 2.3
	{
		string text = header;
		text += encaps(" � (2.3) Edit collections � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add collection.\n";
		text += "  ** \n";
		text += "  **  2. Edit collection.\n";
		text += "  ** \n";
		text += "  **  3. Remove collection.\n";
		text += "  ** \n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["2.3."] = Page("2.", text, menu, Managers::Navigator);
	}

	// Page 2.1.1
	{
		string text = header;
		text += encaps(" � (2.1.1) Add Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.1."] = Page("2.1.", text, menu, Managers::Controller211); // mudar 
	}

	// Page 2.1.2
	{
		string text = header;
		text += encaps(" � (2.1.2) Edit Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.2."] = Page("2.1.", text, menu, Managers::Controller212); // mudar 
	}

	// Page 2.1.3
	{
		string text = header;
		text += encaps(" � (2.1.3) Remove Store � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.1.3."] = Page("2.1.", text, menu, Managers::Controller213); // mudar 
	}

	// Page 2.2.1
	{
		string text = header;
		text += encaps(" � (2.2.1) Add Employee � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.2.1."] = Page("2.2.", text, menu, Managers::Controller221); // mudar 
	}

	// Page 2.2.2
	{
		string text = header;
		text += encaps(" � (2.2.2) Remove Employee � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.2.2."] = Page("2.2.", text, menu, Managers::Controller222); // mudar 
	}

	//Page 2.3.1
	{
		string text = header;
		text += encaps(" � (2.3.1) Add Collection � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.1."] = Page("2.3.", text, menu, Managers::Controller231); // mudar 
	}

	// Page 2.3.2
	{
		string text = header;
		text += encaps(" � (2.3.2) Edit Collection � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.2."] = Page("2.3.", text, menu, Managers::Controller232); // mudar 
	}

	// Page 2.3.3
	{
		string text = header;
		text += encaps(" � (2.3.3) Remove Collection � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["2.3.3."] = Page("2.3.", text, menu, Managers::Controller233); // mudar 
	}


	// Page 3.
	{
		string text = header;
		text += encaps(" � (3) Manage requests � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Edit requests.\n";
		text += "  ** \n";
		text += "  **  2. List requests.\n";
		text += "  ** \n";
		text += "  **  3. ...\n";
		text += "  ** \n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["3."] = Page("", text, menu, Managers::Navigator);
	}

	// Page 3.1
	{
		string text = header;
		text += encaps(" � (3.1) Edit requests � ", MAIN_WIDTH, '=') + "\n";
		text += "  ** \n";
		text += "  **  1. Add request.\n";
		text += "  ** \n";
		text += "  **  2. Cancel request.\n";
		text += "  ** \n";
		text += "  **  3. Change request's delivery date.\n";
		text += "  ** \n";
		text += "  **  4. .....\n";
		text += "  ** \n";
		menu->pages["3.1"] = Page("3.", text, menu, Managers::Navigator); 
	}

	// Page 3.1.1
	{
		string text = header;
		text += encaps(" � (3.1.1) Add request � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.1.1."] = Page("3.1.", text, menu, Managers::Controller311); // mudar 
	}

	
	// Page 3.1.2
	{
		string text = header;
		text += encaps(" � (3.1.2) Cancel request � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.1.2."] = Page("3.1.", text, menu, Managers::Controller312); // mudar 
	}

	// Page 3.1.3
	{
		string text = header;
		text += encaps(" � (3.1.3) Change request's delivery date � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.1.3."] = Page("3.1.", text, menu, Managers::Controller313); // mudar 
	}


	// Page 3.2
	{
		string text = header;
		text += encaps(" � (3.2) List requests � ", MAIN_WIDTH, '=') + "\n";

		menu->pages["3.2"] = Page("3.", text, menu, Managers::Controller32); 
	}

	// Page 4.
	{
		string text = header;
		text += encaps(" � (4) Exit & Save � ", MAIN_WIDTH, '=') + "\n";
		text += "\n";
		menu->pages["4."] = Page("", text, menu, Managers::Navigator);
	}
}
