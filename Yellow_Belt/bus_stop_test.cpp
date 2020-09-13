#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string type;
	is >> type;
	if (type == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_cnt;
		is >> stop_cnt;
		string stop;
		q.stops.clear();
		for (int i = 0; i < stop_cnt; i++) {
			is >> stop;
			q.stops.push_back(stop);
		}
	} else if (type == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (type == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (type == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	string stop;
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (!r.buses.empty()) {
		bool first = true;
		for (auto &bus : r.buses) {
			if(!first) {
				os << " ";
			}
			os << bus;
			first = false;
		}
	} else {
		os << "No stop";
	}
	return os;
}

struct StopsForBusResponse {
	vector<string> stops;
	vector<BusesForStopResponse> busesForStop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (!r.stops.empty()) {
		int i = 0;
		for (auto & stop : r.busesForStop) {
			os << "Stop ";
			if (stop.buses.empty()) {
				os << r.stops[i++] << ": no interchange";
			} else {
				os << r.stops[i++] << ": " << stop;
			}
			if (i != r.stops.size()) {
				os << endl;
			}
		}
	} else {
		os << "No bus";
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> busMap;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (!r.busMap.empty()) {
		int i = 0;
		for (auto & [bus, stops] : r.busMap) {
			os << "Bus " << bus << ":";
			for (auto  & stop : stops) {
				os << " " << stop;
			}
			if (i != r.busMap.size() - 1) {
				os << endl;
			}
			i++;
		}
	} else {
		os << "No buses";
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		busMap[bus] = stops;
		busOrder.push_back(bus);
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse buses;
		vector<string> stops;

		for (auto & bus : busOrder) {
			stops = busMap.at(bus);
			for (auto &cur_stop : stops) {
				if (cur_stop == stop) {
					buses.buses.push_back(bus);
					break;
				}
			}
		}
		buses.stop = stop;
		return buses;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse stops;
		if (busMap.find(bus) != busMap.end()) {
			stops.stops = busMap.at(bus);
			for (auto & stop : stops.stops) {
				auto buses = GetBusesForStop(stop);
				int i;
				for (i = 0; i < static_cast<int>(buses.buses.size()); i++) {
					if (buses.buses[i] == bus) {
						break;
					}
				}
				buses.buses.erase(buses.buses.begin() + i);
				stops.busesForStop.push_back(buses);
			}
		}
		return stops;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse busStops;

		busStops.busMap = busMap;
		return busStops;
	}

private:
	map<string, vector<string>> busMap;
	vector<string> busOrder;
};

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}

	return 0;
}