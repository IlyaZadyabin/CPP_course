#pragma once
#include <iostream>

using namespace std;

class Date {
public:
	Date(int y, int m, int d) : year(y), month(m), day(d) {}
	Date() = default;
	int getYear() const;
	int gedDay() const;
	int getMonth() const;
private:
	int year;
	int month;
	int day;
};

ostream &operator<<(ostream & os, const Date& d);

Date ParseDate(istream & is);