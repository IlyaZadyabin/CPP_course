#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2);

template <typename T> auto Sqr (const vector<T>& vi);
template <typename Key, typename Value> auto Sqr (const map<Key, Value>& m);

template <typename T>
T Sqr(T num) {
	return num * num;
}

template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2) {
	First f = p1.first * p2.first;
	Second s = p1.second * p1.second;
	return make_pair(f, s);
}

template <typename T>
auto Sqr (const vector<T>& vi) {
	vector<T> ans;

	ans.reserve(vi.size());
	for (auto & item : vi) {
		ans.push_back(Sqr(item));
	}
	return ans;
}

template <typename Key, typename Value>
auto Sqr (const map<Key, Value>& m) {
	map<Key, Value> ans;

	for (auto & [key, value] : m) {
  		ans[key] = Sqr(value);
	}
	return ans;
}

int main()
{
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
