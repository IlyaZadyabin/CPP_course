#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	auto prev_it = s.begin();
	auto next_space_it = s.begin();
	vector<string> vec_of_words;

	while (next_space_it != s.end()) {
		next_space_it = find(next_space_it + 1, s.end(), ' ');
		vec_of_words.emplace_back(prev_it, next_space_it);
		prev_it = next_space_it + 1;
	}
	return vec_of_words;
}

int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}
