#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;

int64_t singleThreadSum(const vector<vector<int>>& matrix, int first_row, int last_row) {
	int64_t ans = 0;

	for (size_t i = first_row; i < last_row; i++) {
		ans += accumulate(matrix[i].begin(), matrix[i].end(), 0);
	}
	return ans;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	vector<future<int64_t>> futures;
	size_t amount_of_threads, prev_border = 0, cur_border = 0;
	amount_of_threads = matrix.size() < 4 ? matrix.size() : 4;

	for (size_t i = 0; i < amount_of_threads; i++) {
		prev_border = cur_border;
		if (i == amount_of_threads - 1) {
			cur_border = matrix.size();
		} else {
			cur_border += matrix.size() / amount_of_threads;
		}
		futures.push_back(
				async ([&matrix, prev_border, cur_border] {
					return singleThreadSum(matrix, prev_border, cur_border);
				})
		);
	}

	int64_t ans = 0;
	for (auto & f : futures) {
		ans += f.get();
	}
	return ans;
}

void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
}