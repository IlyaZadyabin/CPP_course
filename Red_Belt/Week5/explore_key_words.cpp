#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l) {
		for (auto it = first; it != last; it++) {
			page_size++;
		}
	}
	size_t size() const {
		return page_size;
	}
	Iterator begin() const {
		return first;
	}
	Iterator end() const {
		return last;
	}
private:
	Iterator first, last;
	size_t page_size{};
};

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator b, Iterator e, size_t p_size) {
		for(auto it = b; it < e; it += p_size) {
			pages.push_back(IteratorRange<Iterator>(it, min(it + p_size, e)));
			amount_of_pages++;
		}
	}

	auto begin() const {
		return pages.begin();
	}
	auto end() const {
		return pages.end();
	}
	size_t size() const {
		return amount_of_pages;
	}
private:
	size_t amount_of_pages{};
	vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator{c.begin(), c.end(), page_size};
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (auto & [key,value] : other.word_frequences) {
			word_frequences[key] += value;
		}
	}
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	size_t pos = 0;
	string_view s(line);
	std::string token;

	while ((pos = s.find(' ')) != std::string::npos) {
		if (0 != pos) {
			token = s.substr(0, pos);

			if (key_words.find(token) != key_words.end()) {
				result.word_frequences[token]++;
			}
		}
		s = s.substr(pos + 1, s.size() - 1);
	}
	token = s;
	if (key_words.find(token) != key_words.end()) {
		result.word_frequences[token]++;
	}
	return result;
}

template <typename Page>
Stats ExploreKeyWordsSingleThread(const set<string>& key_words, Page& page) {
	Stats result;
	for (auto & line : page) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	vector<string> lines;
	Stats result;
	for (string line; getline(input, line);) {
		lines.push_back(move(line));
	}

	size_t page_size = lines.size() / 4;
	vector<future<Stats>> futures;

	for (auto page : Paginate(lines, page_size)) {
		futures.push_back(
					async([&key_words, page] {
						return ExploreKeyWordsSingleThread(key_words, page);
					})
		);
	}
	for (auto & f : futures) {
		result += f.get();
	}
	return result;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
			{"yangle", 6},
			{"rocks", 2},
			{"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}