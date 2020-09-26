#include "airline_ticket.h"
#include "test_runner.h"
#include <algorithm>
#include <numeric>
#include <tuple>
using namespace std;

bool operator < (const Date& left, const Date& right) {
	return tie(left.year, left.month, left.day) < tie(right.year, right.month, right.day);
}

bool operator == (const Date& left, const Date& right) {
	return tie(left.year, left.month, left.day) == tie(right.year, right.month, right.day);
}

ostream & operator << (ostream & os, const Date& date) {
	os << to_string(date.year) << "-" << to_string(date.month) << "-" << to_string(date.day);
	return os;
}

bool operator < (const Time& left, const Time& right) {
	return tie(left.hours, left.minutes) < tie(right.hours, right.minutes);
}

bool operator == (const Time& left, const Time& right) {
	return tie(left.hours, left.minutes) == tie(right.hours, right.minutes);
}

ostream & operator << (ostream & os, const Time& time) {
	os << to_string(time.hours) << ":" << to_string(time.minutes);
	return os;
}

#define SORT_BY(field)  \
	[](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
		return lhs.field < rhs.field; \
	}

void TestSortBy() {
	vector<AirlineTicket> tixs = {
			{"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
			{"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
			{"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
			{"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
			{"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
	};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
}




