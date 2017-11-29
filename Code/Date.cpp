#include "Date.h"
#include "Supplements.h"
#include <iostream>

namespace Months {
	constexpr Date::Month January = 1;
	constexpr Date::Month February = 2;
	constexpr Date::Month March = 3;
	constexpr Date::Month April = 4;
	constexpr Date::Month May = 5;
	constexpr Date::Month June = 6;
	constexpr Date::Month July = 7;
	constexpr Date::Month August = 8;
	constexpr Date::Month September = 9;
	constexpr Date::Month October = 10;
	constexpr Date::Month November = 11;
	constexpr Date::Month December = 12;
}

bool Date::validDate(const Date& date)
{
	return (date.day > 0) && (date.day <= numberOfDaysInMonth(date.month, date.year));
}

std::string Date::string_month(Month month)
{
	using namespace Months;
	switch (month)
	{
	case January: return "January";
	case February: return "February";
	case March: return "March";
	case April: return "April";
	case May: return "May";
	case June: return "June";
	case July: return "July";
	case August: return "August";
	case September: return "September";
	case October: return "October";
	case November: return "November";
	case December: return "December";
	default: return "";
	}
}

Date::Date(Day d, Month m, Year y) :
	day(d), month(m), year(y)
{
	if (!validDate(*this)) {
		auto d = InvalidDate(*this);
		cout << d.day << endl;
		cout << d.month << endl;
		cout << d.year << endl;
	}
}

Date::Date(string s)
{
	vector<string> separated = split(s, "-");

	this->day = stoi(separated.at(0));
	this->month = stoi(separated.at(1));
	this->year = stoi(separated.at(2));

	if (!validDate(*this)) {
		throw InvalidDate(*this);
	}
}

Date::Date() :
	day(0), month(0), year(0) {}


Date::Day Date::getDay() const
{
	return day;
}

Date::Month Date::getMonth() const
{
	return month;
}

Date::Year Date::getYear() const
{
	return year;
}

bool Date::setDay(Day d)
{
	Day tmp = day;
	day = d;
	if (!validDate(*this)) {
		day = tmp;
		return false;
	}
	return true;
}

bool Date::setMonth(Month m)
{
	Month tmp = month;
	month = m;
	if (!validDate(*this)) {
		month = tmp;
		return false;
	}
	return true;
}

bool Date::setYear(Year y)
{
	Year tmp = year;
	year = y;
	if (!validDate(*this)) {
		year = tmp;
		return false;
	}
	return true;
}

string Date::write() const {
	return ((day > 9) ? "" : "0") + to_string(day) + "-" + ((month > 9) ? "" : "0") + to_string(month) + "-" + std::to_string(year);
}


unsigned int Date::numberOfDaysInMonth(Month month, Year year)
{
	using namespace Months;
	switch (month)
	{
	case January:
	case March:
	case May:
	case July:
	case August:
	case October:
	case December:
		return 31;
	case February:
		if (numberOfDaysInYear(year) == 365)
			return 28;
		else
			return 29;
	case April:
	case June:
	case September:
	case November:
		return 30;
	default:
		return 0;
	}
}

unsigned int Date::numberOfDaysInYear(Year year)
{
	if (year % 4)
		return 365;
	else if (year % 100)
		return 366;
	else
		return 365;
}


Date& Date::operator++()
{
	using namespace Months;
	if (day == numberOfDaysInMonth(month, year)) {
		day = 1;
		if (month == December) {
			month = January;
			++year;
		}
		else {
			++month;
		}
	}
	else {
		++day;
	}
	return *this;
}

Date Date::operator++(int)
{
	using namespace Months;
	Date tmp = *this;
	if (day == numberOfDaysInMonth(month, year)) {
		day = 1;
		if (month == December) {
			month = January;
			++year;
		}
		else {
			++month;
		}
	}
	else {
		++day;
	}
	return tmp;
}


Date operator+(const Date& date, unsigned int days) {
	using namespace Months;
	Date tmp = date;

	if (days == 0) return tmp;

	if (tmp.month == February && tmp.day == 29) {
		tmp.month = March;
		tmp.day = 1;
		--days;
	}

	bool early = tmp.month <= 2;

	while (days > 365) {
		days -= Date::numberOfDaysInYear(early ? tmp.year : (tmp.year + 1));
		++tmp.year;
	}

	while (days > 30) {
		days -= Date::numberOfDaysInMonth(tmp.month, tmp.year);
		if (tmp.month == December) {
			tmp.month = January;
			++tmp.year;
		}
		else {
			++tmp.month;
		}
	}

	tmp.day += days;
	while (tmp.day > Date::numberOfDaysInMonth(tmp.month, tmp.year)) {
		tmp.day -= Date::numberOfDaysInMonth(tmp.month, tmp.year);
		if (tmp.month == 12) {
			tmp.month = January;
			++tmp.year;
		}
		else {
			++tmp.month;
		}
	}

	return tmp;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.day == rhs.day && lhs.month == rhs.month && lhs.year == rhs.year;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return lhs.day != rhs.day || lhs.month != rhs.month || lhs.year != rhs.year;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return lhs.year < rhs.year ||
		(lhs.year == rhs.year && lhs.month < rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day);
}


bool operator>(const Date& lhs, const Date& rhs)
{
	return lhs.year > rhs.year ||
		(lhs.year == rhs.year && lhs.month > rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day > rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return lhs.year < rhs.year ||
		(lhs.year == rhs.year && lhs.month < rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day <= rhs.day);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return lhs.year > rhs.year ||
		(lhs.year == rhs.year && lhs.month > rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day >= rhs.day);
}

ostream & operator<<(ostream & o, const Date & d)
{
	o << d.day << "-" << d.month << "-" << d.year << endl;

	return o;
}