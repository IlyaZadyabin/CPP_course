#include "../Week4/test_runner.h"

using namespace std;

template <typename T>
class Table {
public:
	Table(size_t r, size_t c) : rows(r), cols(c) {
		Resize(rows, cols);
	}

	const vector<T>& operator[](size_t idx) const {
		return table[idx];
	}
	vector<T>& operator[](size_t idx) {
		return table[idx];
	}
	void Resize(size_t new_rows, size_t new_cols) {
		table.resize(new_rows);
		for (auto & row : table) {
			row.resize(new_cols);
		}
		rows = new_rows;
		cols = new_cols;
	}
	pair<size_t, size_t> Size() const {
		if (!rows || !cols) {
			return make_pair(0, 0);
		} else {
			return make_pair(rows, cols);
		}
	}
private:
	vector<vector<T>> table;
	size_t rows, cols;
};


void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}