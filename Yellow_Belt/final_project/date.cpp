#include <iostream>

using namespace std;

class Date {
public:
	Date(int y, int m, int d) : year(y), month(m), day(d) {}
	Date() = default;

	int getYear() const  {
		return year;
	}
	int gedDay() const {
		return day;
	}
	int getMonth() const {
		return month;
	}
private:
	int year;
	int month;
	int day;
};

ostream &operator<<(ostream & os, const Date& d) {
	os << d.getYear() << "-" << d.getMonth() << "-" << d.gedDay();
	return os;
}

Date ParseDate(istream & is) {
	int d, m, y;
	char del1, del2;
	is >> d >> del1 >> m >> del2 >> y;
	return Date(y, m, d);
}