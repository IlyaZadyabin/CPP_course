#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(numbers.begin(), numbers.end(), [](const int& num) {return num < 0;});

	bool first = true;
	while(it > numbers.begin()) {
		it--;
		if (!first) {
			std::cout << " ";
		}
		std::cout << *it;
		first = false;
	}
}

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	cout << endl;
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	cout << endl;
	PrintVectorPart({6, 1, 8, 5, 4});
	cout << endl;
	return 0;
}
