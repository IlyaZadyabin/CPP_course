#include "profile.h"
#include "test_runner.h"
#include <deque>
#include <iostream>
#include <map>
#include <string_view>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		const string_view source_view = GetCopy(source);
		const string_view target_view = GetCopy(target);
		forward_dict[source_view] = target_view;
		backward_dict[target_view] = source_view;
	}
	string_view TranslateForward(string_view source) const {
		auto it = forward_dict.find(source);
		if (it != forward_dict.end()) {
			return it->second;
		} else {
			return string_view{};
		}
	}
	string_view TranslateBackward(string_view target) const {
		auto it = backward_dict.find(target);
		if (it != backward_dict.end()) {
			return it->second;
		} else {
			return string_view{};
		}
	}

private:
	string_view GetCopy(string_view s) {
		for (const auto* map_ptr : {&forward_dict, &backward_dict}) {
			const auto it = map_ptr->find(s);
			if (it != map_ptr->end()) {
				return it->first;
			}
		}
		return row.emplace_back(s);
	}

	map<string_view, string_view> forward_dict;
	map<string_view, string_view> backward_dict;
	deque<string> row;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}