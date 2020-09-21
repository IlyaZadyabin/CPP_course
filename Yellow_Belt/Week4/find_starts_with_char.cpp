#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	std::string pref;
	pref.push_back(prefix);

	auto r = equal_range(range_begin, range_end, pref,
		[&](std::string const& s1, std::string const& s2)
		{
			if (auto cmp = std::strncmp(s1.data(), s2.data(), pref.size()))
				return cmp < 0;
			return false;
		});
	return make_pair(r.first, r.second);
}
//
//int main() {
//	const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
//
//	const auto m_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
//	for (auto it = m_result.first; it != m_result.second; ++it) {
//		cout << *it << " ";
//	}
//	cout << endl;
//
//	const auto p_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
//	cout << (p_result.first - begin(sorted_strings)) << " " <<
//		 (p_result.second - begin(sorted_strings)) << endl;
//
//	const auto z_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
//	cout << (z_result.first - begin(sorted_strings)) << " " <<
//		 (z_result.second - begin(sorted_strings)) << endl;
//
//	return 0;
//}
