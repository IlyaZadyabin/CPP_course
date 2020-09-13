#include <iostream>
#include <map>
#include <exception>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict (map<Key, Value>& m, Key key) {
	if (m.find(key) != m.end()) {
		return m[key];
	} else {
		throw runtime_error("");
	}
}

//int main()
//{
//	map<int, string> m = {{0, "value"}};
//	string& item = GetRefStrict(m, 0);
//	item = "newvalue";
//	cout << m[0] << endl; // выведет newvalue
//}