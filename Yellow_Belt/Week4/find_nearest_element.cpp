#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
	auto right = numbers.lower_bound(border);
	auto left = numbers.end();

	if(right != numbers.begin()) {
		left = prev(right);
	}

	if (*right == border) {
		return right;
	}

	if (left != numbers.end()) {

		int first_dist = abs(border - *left);
		if (right != numbers.end()) {
			int second_dist = abs(*right - border);

			if (first_dist < second_dist) {
				return left;
			} else if (second_dist < first_dist) {
				return right;
			} else {
				return *left < *right ? left : right;
			}
		} else {
			return left;
		}
	}
	return right;
}

int main() {
	set<int> numbers = {1, 4, 6};
	cout <<
		 *FindNearestElement(numbers, 0) << " " <<
		 *FindNearestElement(numbers, 3) << " " <<
		 *FindNearestElement(numbers, 5) << " " <<
		 *FindNearestElement(numbers, 6) << " " <<
		 *FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}
