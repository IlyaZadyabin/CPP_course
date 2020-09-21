#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
		return;
	} else {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		auto one_third_it = elements.begin() + elements.size() / 3;
		auto two_third_it = elements.begin() + 2 * elements.size() / 3;
		MergeSort(elements.begin(), one_third_it);
		MergeSort(one_third_it, two_third_it);
		MergeSort(two_third_it, elements.end());

		vector<typename RandomIt::value_type> tmp;
		merge(elements.begin(), one_third_it, one_third_it, two_third_it, back_inserter(tmp));
		merge(tmp.begin(), tmp.end(), two_third_it, elements.end(), range_begin);
	}
}

int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
