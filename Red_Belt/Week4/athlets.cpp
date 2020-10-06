#include <list>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n;
	list<int> order;
	vector<list<int>::iterator> position(100'000, order.end());

	cin >> n;
	for (auto i = 0; i < n; i++) {
		int cur, next;
		cin >> cur >> next;
		position[cur] = order.insert(position[next], cur);
	}

	for (auto & x : order) {
		cout << x << '\n';
	}
}