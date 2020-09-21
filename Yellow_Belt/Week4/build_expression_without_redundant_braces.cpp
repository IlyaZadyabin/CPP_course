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

bool cmp_priority(const char c1, const char c2) {
	return (c1 == '*' || c1 == '/') && (c2 == '+' || c2 == '-');
}

int main()
{
	int x, N;
	cin >> x >> N;

	deque<string> expression;
	string operation, prev_operation("*");
	getline(cin, operation);
	expression.push_back(to_string(x));
	for (int i = 0; i < N; i++) {
		getline(cin, operation);
		if (cmp_priority(operation[0], prev_operation[0])) {
			expression.push_front("(");
			expression.push_back(")");
		}
		expression.push_back(" ");
		expression.push_back(operation);
		prev_operation = operation;
	}
	print_dequeue(expression);
}