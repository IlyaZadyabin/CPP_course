#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <deque>

using namespace std;

struct Record {
	int64_t time{};
	int client_id{};
	int rooms{};
};

class Hotel {
public:
	static int time_of_last_book;

	void DeleteOldRecords() {
		while ((time_record.front().time + shift <= time_of_last_book) && (!time_record.empty())) {
			rooms -= time_record.front().rooms;
			time_record.pop_front();
		}
	}
	void AddClient(int64_t time, int client_id, int room_count) {
		time_of_last_book = time;
		time_record.push_back({time, client_id, room_count});
		uniq_clients[client_id]++;
		rooms += room_count;
	}

	int getRooms() {
		DeleteOldRecords();
		return rooms;
	}
	int getClients() {
		DeleteOldRecords();
		set<int> tmp;
		for (auto & item : time_record) {
			tmp.insert(item.client_id);
		}
		return tmp.size();
	}
private:
	static const int shift = 86'400;

	deque<Record> time_record;
	map<int,int> uniq_clients;
	int rooms{};
};

int Hotel::time_of_last_book = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	map<string, Hotel> hotels;
	string hotel_name;
	int Q;

	cin >> Q;
	for(auto i = 0; i < Q; i++) {
		string command;
		cin >> command;
		if (command == "CLIENTS") {
			cin >> hotel_name;
			std::cout << hotels[hotel_name].getClients() << std::endl;
		} else if (command == "ROOMS") {
			cin >> hotel_name;
			std::cout << hotels[hotel_name].getRooms() << std::endl;
		} else if (command == "BOOK") {
			int64_t time;
			int client_id;
			int room_cnt;
			cin >> time >> hotel_name >> client_id >> room_cnt;
			Hotel::time_of_last_book = time;
//			for (auto & [name, hotel] : hotels) {
//				hotel.DeleteOldRecords();
//			}
			hotels[hotel_name].AddClient(time, client_id, room_cnt);
		}
	}
}

//
//void test() {
//	Booking manager;
//	std::string marriot{ "mariott" };
//	std::string hilton{ "hilton" };
//	// Test empty bookings
//	ASSERT_EQUAL(manager.CLIENTS(marriot), 0);
//	ASSERT_EQUAL(manager.ROOMS(marriot), 0);
//
//	manager.ADD(0, "mariott", 1, 10);
//	manager.ADD(0, "mariott", 2, 1);
//	manager.ADD(0, "mariott", 3, 1);
//	manager.ADD(0, "mariott", 4, 1);
//	manager.ADD(0, "hilton", 1, 1);
//	manager.ADD(1, "hilton", 2, 1);

//CLIENTS mariot
//ROOMS mariot
//BOOK 0 mariot 1 10
//BOOK 0 mariot 2 1
//BOOK 0 mariot 3 1
//BOOK 0 mariot 4 1
//BOOK 0 hilton 1 1
//BOOK 0 hilton 2 1
//CLIENTS mariot
//ROOMS mariot
//CLIENTS hilton
//ROOMS hilton
//BOOK 86400 mariot 1 1
//CLIENTS mariot
//ROOMS mariot
//CLIENTS hilton
//ROOMS hilton
//BOOK 86401 mariot 5 1
//CLIENTS mariot
//ROOMS mariot
//CLIENTS hilton
//ROOMS hilton

//
//	// Test correctness
//	ASSERT_EQUAL(manager.CLIENTS(marriot), 4);
//	ASSERT_EQUAL(manager.ROOMS(marriot), 13);
//	ASSERT_EQUAL(manager.CLIENTS(hilton), 2);
//	ASSERT_EQUAL(manager.ROOMS(hilton), 2);
//
//	// Test event past 1 day resets statics
//	manager.ADD(86400, "mariott", 1, 1);
//	ASSERT_EQUAL(manager.CLIENTS(marriot), 1);
//	ASSERT_EQUAL(manager.ROOMS(marriot), 1);
//	ASSERT_EQUAL(manager.CLIENTS(hilton), 1);
//	ASSERT_EQUAL(manager.ROOMS(hilton), 1);

//
//	// Test no clients and room for the last day
//	manager.ADD(86401, "mariott", 5, 1);
//	ASSERT_EQUAL(manager.CLIENTS(marriot), 2);
//	ASSERT_EQUAL(manager.ROOMS(marriot), 2);
//	ASSERT_EQUAL(manager.CLIENTS(hilton), 0);
//	ASSERT_EQUAL(manager.ROOMS(hilton), 0);
//}
