#include "date.h"
#include "database.h"
#include <vector>

class Database {
	void Add(const Date & date, const string & event) {
		base[date].push_back(event);
	}
	void Del
private:
	map<Date, vector<string>> base;
};