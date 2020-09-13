#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

bool IsPalindrom(const string& str) {}

void test_empty() {
	AssertEqual(IsPalindrom(""), true);
	AssertEqual(IsPalindrom("madam"), 1);
	AssertEqual(IsPalindrom("o"), 1);
	AssertEqual(IsPalindrom(""), 1);
	AssertEqual(IsPalindrom(" "), 1);
	AssertEqual(IsPalindrom("  "), 1);
	AssertEqual(IsPalindrom("top pot"), 1);
}

void test_single() {
	AssertEqual(IsPalindrom("a"), true);
	AssertEqual(IsPalindrom("aa"), true);
	AssertEqual(IsPalindrom("ab"), false);
	AssertEqual(IsPalindrom("b a"), false);
	AssertEqual(IsPalindrom("XabbaY"), false);
	AssertEqual(IsPalindrom("baobab"), false);
	AssertEqual(IsPalindrom(" "), true);
	AssertEqual(IsPalindrom("777777"), true);
	AssertEqual(IsPalindrom("_"), true);
}

void test_first_last() {
	AssertEqual(IsPalindrom("abbbb"), false);
	AssertEqual(IsPalindrom("abbccbba"), true);
	AssertEqual(IsPalindrom("abba"), true);
	AssertEqual(IsPalindrom("777778"), false);
}

void test_middle() {
	AssertEqual(IsPalindrom("ge               ek"), false);
	AssertEqual(IsPalindrom("aabcaa"), false);
	AssertEqual(IsPalindrom("aaacaaaa"), false);
	AssertEqual(IsPalindrom("aaA"), false);
	AssertEqual(IsPalindrom("___AbA__"), false);
}

void test_spaces() {
	AssertEqual(IsPalindrom("  "), true);
	AssertEqual(IsPalindrom("a ba"), false);
	AssertEqual(IsPalindrom("ab  ba"), true);
}

int main() {
	TestRunner runner;
	runner.RunTest(test_empty, "empty string");
	runner.RunTest(test_single, "test one symbol");
	runner.RunTest(test_first_last, "test first and last symbols");
	runner.RunTest(test_middle, "test middle symbol");
	runner.RunTest(test_spaces, "test spaces");
	return 0;
}