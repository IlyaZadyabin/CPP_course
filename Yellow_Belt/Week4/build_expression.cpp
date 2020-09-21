#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;

void print_dequeue(const deque<string> & d) {
	for (auto & item : d) {
		std::cout << item;
	}
	std::cout << std::endl;
}

int main()
{
	int x, N;
	cin >> x >> N;

	deque<string> expression;
	string operation;
	getline(cin, operation);
	expression.push_back(to_string(x));
	for (int i = 0; i < N; i++) {
		expression.push_front("(");
		expression.push_back(")");
		expression.push_back(" ");
		getline(cin, operation);
		expression.push_back(operation);
	}
	print_dequeue(expression);
}