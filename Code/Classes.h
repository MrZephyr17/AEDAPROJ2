#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <priority_queue>

#define MAIN_WIDTH					105 /* > 60 */
#define MAX_WIDTH					130 /* > MAIN_WIDTH */
#define TOKEN_SPLITTERS				":-><="
#define LIST_SPLITTERS				",;"
#define PAGE_SPLITTERS				",;.- "
#define DEFAULT_SKIP_SYMBOL			"$"

#define FILE_LINE_SEPARATOR			"\n"
#define FILE_ITEM_SEPARATOR			";"
#define DEFAULT_PAIR_SEPARATOR      ","

#define TYPE_BOOK					"Book"
#define TYPE_MAGAZINE				"Magazine"

#define DEFAULT_STORES_FILE			"stores.txt"
#define DEFAULT_COLLECTIONS_FILE	"collections_publications.txt"
#define DEFAULT_EMPLOYEES_FILE		"employees.txt"
#define DEFAULT_REQUESTS_FILE		"requests.txt"
#define DEFAULT_CURRENT_DAY			Date(23, 11, 2017)

#define DEFAULT_BOOK_QT_REQ			20
#define DEFAULT_MAGAZINE_QT_REQ		150
#define DEFAULT_DESCRIPTION			"Placeholder description"
#define DEFAULT_PRICE				16.0
#define DEFAULT_MAGAZINE_FREQ		7


using namespace std;

// ***** _COMPANY_H_ *****
class Company;

// ***** _STORE_H_ *****
class Store;
struct PublicationLog;

// ***** _EMPLOYEE_H_ *****
class Employee;

// ***** _REQUEST_H_ *****
class Request;

// ***** _COLLECTION_H_ *****
class Collection;
class BookCollection;
class MagazineCollection;

// ***** _PUBLICATION_H_ *****
class Publication;
class Book;
class Magazine;

// ***** _DATA_H_ *****
class Date;

// ***** _EXCEPTIONS_H_ *****
template <class T> class DuplicateElement;
template <class T> class NonExistentElement;
class NonExistentId;
template <class T> class MalformedFileItem;


// ***** _CONSOLE_H_ *****
struct Input;
struct Token;
class InputReader;
class Page;
class Menu;
struct ManagerData;
using Manager = void(const Page&);

// ***** _TABLE_H_ *****
struct TableOptions;
struct TableEntry;
class Table;

// ***** _FORM_H_ *****
struct FormOptions;
struct FormEntry;
class Form;
using Forms = map<string, Form>;