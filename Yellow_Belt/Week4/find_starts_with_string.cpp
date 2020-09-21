#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
	auto r = equal_range(range_begin, range_end, prefix,
		 [&](std::string const& s1, std::string const& s2)
		 {
			 if (auto cmp = std::strncmp(s1.data(), s2.data(), prefix.size()))
				 return cmp < 0;
			 return false;
		 });
	return make_pair(r.first, r.second);
}

//
//int main() {
//	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
//
//	const auto mo_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
//	for (auto it = mo_result.first; it != mo_result.second; ++it) {
//		cout << *it << " ";
//	}
//	cout << endl;
//
//	const auto mt_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
//	cout << (mt_result.first - begin(sorted_strings)) << " " <<
//		 (mt_result.second - begin(sorted_strings)) << endl;
//
//	const auto na_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
//	cout << (na_result.first - begin(sorted_strings)) << " " <<
//		 (na_result.second - begin(sorted_strings)) << endl;
//
//	return 0;
//}
