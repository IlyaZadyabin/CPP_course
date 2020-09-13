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

class Rational {
public:
	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {
	}

	int Denominator() const {
	}
};

void test_basic_fraction() {
	Rational f;
	AssertEqual(f.Numerator(), 0);
	AssertEqual(f.Denominator(), 1);
}

void test_reducing() {
	Rational f(6, 8);
	AssertEqual(f.Numerator(), 3);
	AssertEqual(f.Denominator(), 4);
	Rational f1(15, 35);
	AssertEqual(f1.Numerator(), 3);
	AssertEqual(f1.Denominator(), 7);
}

void test_negative() {
	Rational f(-1, 2);
	AssertEqual(f.Numerator(), -1);
	AssertEqual(f.Denominator(), 2);
	Rational f1(1, -2);
	AssertEqual(f1.Numerator(), -1);
	AssertEqual(f1.Denominator(), 2);
}

void test_positive() {
	Rational f(-2, -3);
	AssertEqual(f.Numerator(), 2);
	AssertEqual(f.Denominator(), 3);
}

void test_zero_numerator() {
	Rational f(0, 5);
	AssertEqual(f.Numerator(), 0);
	AssertEqual(f.Denominator(), 1);
}

int main() {
	TestRunner runner;
	runner.RunTest(test_basic_fraction, "test_basic_fraction");
	runner.RunTest(test_reducing, "test_reducing");
	runner.RunTest(test_negative, "test_negative");
	runner.RunTest(test_positive, "test_positive");
	runner.RunTest(test_zero_numerator, "test_zero_numerator");
	return 0;
}