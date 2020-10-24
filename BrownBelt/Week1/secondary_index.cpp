#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;
};

class Database {
public:
	bool Put(const Record& record) {
		auto it = data.find(record.id);
		if (it == data.end()) {
			auto [data_iter, flag] = data.insert({record.id, Rec{record, {}, {}, {} }});
			auto& rec = data_iter->second;

			rec.timestamp_it = timestamp_map.insert({record.timestamp, &rec.record});
			rec.karma_it = karma_map.insert({record.karma, &rec.record});
			rec.user_it = user_map.insert({record.user, &rec.record});
			return true;
		} else {
			return false;
		}
	}
	const Record* GetById(const string& id) const {
		auto it = data.find(id);
		if (it != data.end()) {
			return &it->second.record;
		} else {
			return nullptr;
		}
	}
	bool Erase(const string& id) {
		auto it = data.find(id);
		if (it != data.end()) {
			const auto& rec = it->second;
			timestamp_map.erase(rec.timestamp_it);
			karma_map.erase(rec.karma_it);
			user_map.erase(rec.user_it);
			data.erase(it);
			return true;
		} else {
			return false;
		}
	}

	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		auto start = timestamp_map.lower_bound(low);
		auto end = timestamp_map.upper_bound(high);
		for (auto it = start; it != end; it++) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const {
		auto start = karma_map.lower_bound(low);
		auto end = karma_map.upper_bound(high);
		for (auto it = start; it != end; it++) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const {
		auto start = user_map.lower_bound(user);
		auto end = user_map.upper_bound(user);
		for (auto it = start; it != end; it++) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

private:
	struct Rec {
		Record record;
		multimap<int, const Record*>::iterator timestamp_it;
		multimap<int, const Record*>::iterator karma_it;
		multimap<string, const Record*>::iterator user_it;
	};

	unordered_map<string, Rec> data;
	multimap<int, const Record*> timestamp_map;
	multimap<int, const Record*> karma_map;
	multimap<string, const Record*> user_map;
};

void TestRangeBoundaries() {
	const int good_karma = 1000;
	const int bad_karma = -10;

	Database db;
	db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
	db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

	int count = 0;
	db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestSameUser() {
	Database db;
	db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
	db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

	int count = 0;
	db.AllByUser("master", [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestReplacement() {
	const string final_body = "Feeling sad";

	Database db;
	db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
	db.Erase("id");
	db.Put({"id", final_body, "not-master", 1536107260, -10});

	auto record = db.GetById("id");
	ASSERT(record != nullptr);
	ASSERT_EQUAL(final_body, record->title);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestRangeBoundaries);
	RUN_TEST(tr, TestSameUser);
	RUN_TEST(tr, TestReplacement);
	return 0;
}