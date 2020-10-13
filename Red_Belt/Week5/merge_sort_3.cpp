#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
		return;
	} else {
		vector<typename RandomIt::value_type> elements(	make_move_iterator(range_begin),
												  		make_move_iterator(range_end)
												  	 );
		auto one_third_it = elements.begin() + elements.size() / 3;
		auto two_third_it = elements.begin() + 2 * elements.size() / 3;
//		MergeSort(	make_move_iterator(elements.begin()),
//					make_move_iterator(one_third_it)
//				);
//		MergeSort(	make_move_iterator(one_third_it),
//					make_move_iterator(two_third_it)
//				);
//		MergeSort(	make_move_iterator(two_third_it),
//					make_move_iterator(elements.end())
//				);

		MergeSort(elements.begin(), one_third_it);
		MergeSort(one_third_it, two_third_it);
		MergeSort(two_third_it, elements.end());

		vector<typename RandomIt::value_type> tmp;
		merge(	make_move_iterator(elements.begin()),
				make_move_iterator(one_third_it),
				make_move_iterator(one_third_it),
				make_move_iterator(two_third_it),
				back_inserter(tmp)
			);
		merge(	make_move_iterator(tmp.begin()),
				make_move_iterator(tmp.end()),
				make_move_iterator(two_third_it),
				make_move_iterator(elements.end()),
				range_begin
			);
	}
}

void TestIntVector() {
	vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}