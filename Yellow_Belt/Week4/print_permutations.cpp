#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool great(int lhs, int rhs) {
	return lhs > rhs;
}

void print_vec(vector<int> &v) {
	bool first = true;
	for (auto & item : v) {
		if(!first) {
			cout << " ";
		}
		cout << item;
		first = false;
	}
}

int main()
{
	int N;
	cin >> N;
	vector<int> v;

	for (int i = N; i >= 1; i--) {
		v.push_back(i);
	}

	std::sort(v.begin(), v.end(), great);
	do {
		print_vec(v);
		cout << endl;
	} while(std::prev_permutation(v.begin(), v.end()));
}