template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {}
	~TestRunner() = default;

private:
	int fail_count;
};

inline void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}