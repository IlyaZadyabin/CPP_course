#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

auto CheckRank(const Region &reg) {
	return tie(reg.std_name, reg.parent_std_name, reg.names, reg.population);
}

bool operator<(const Region &lhs, const Region &rhs) {
	return (CheckRank(lhs) < CheckRank(rhs));
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	map<Region, int> reg_cnt;
	int max_ans = 0;

	for (const auto &reg : regions) {
		reg_cnt[reg]++;
		if (reg_cnt[reg] > max_ans) {
			max_ans = reg_cnt[reg];
		}
	}

	return max_ans;
}

int main() {
	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   },
								   }) << endl;

	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Toulouse",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   31
										   },
								   }) << endl;

	return 0;
}