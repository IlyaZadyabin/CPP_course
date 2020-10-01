#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <deque>
#include <set>

using namespace std;

class Manager {
public:
	void Book(int64_t time, string& hotel, int user_id, int rooms){
		Records[hotel].push_back({time, user_id, rooms});
		hotel_unique_clients[hotel][user_id]++;
		hotel_rooms_count[hotel] += rooms;
		cur_time = time;
	}

	int getRooms(const string& hotel) {
		if (!Records.count(hotel))
			return 0;

		DeleteOldRecords(hotel);
		return hotel_rooms_count[hotel];
	}

	int getClients(const string& hotel) {
		if (!Records.count(hotel))
			return 0;

		DeleteOldRecords(hotel);
		return hotel_unique_clients[hotel].size();
	}

private:
	static const int DAY = 86'400;
	map<string, deque<tuple<int64_t, int, int>>> Records;
	map<string, map<int, int>> hotel_unique_clients;
	map<string, int> hotel_rooms_count;
	int64_t cur_time = static_cast<int64_t>(-1e18);

	void DeleteOldRecords(const string& hotel) {
		auto &events = Records.at(hotel);
		while (!events.empty()) {
			tuple<int64_t, int, int> event = events.front();
			auto &[time_, user_id, rooms] = event;

			if (time_ + DAY <= cur_time) {
				hotel_rooms_count[hotel] -= rooms;
				hotel_unique_clients[hotel][user_id]--;

				if (hotel_unique_clients[hotel][user_id] <= 0) {
					hotel_unique_clients[hotel].erase(user_id);
				}
				events.pop_front();
			} else {
				break;
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Manager manager;

	int Q;
	cin >> Q;

	for (int query_id = 0; query_id < Q; ++query_id) {
		string command, hotel;

		cin >> command;
		if (command == "CLIENTS") {
			cin >> hotel;
			cout << manager.getClients(hotel) << '\n';
		} else if (command == "ROOMS"){
			cin >> hotel;
			cout << manager.getRooms(hotel) << '\n';
		} else if (command == "BOOK") {
			int64_t time;
			int client_id, room_count;
			cin >> time >> hotel >> client_id >> room_count;
			manager.Book(time, hotel, client_id, room_count);
		}
	}
}