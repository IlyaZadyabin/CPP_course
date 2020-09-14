#include "sum_reverse_sort.h"
#include <algorithm>
#include <iostream>

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	int n = s.length();
	std::string ans = s;

	for (int i = 0; i < n; i++)
		ans[i] = s[n - i - 1];
	return ans;
}

void Sort(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
}
