#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <unordered_map>

using namespace std;

namespace Ini {
	using Section = unordered_map<string, string>;

	class Document {
	public:
		explicit Document() = default;
		Document(istream &input) {
			string line, name, value, key;

			while(getline(input, line)) {
				if (line.empty()) {
					continue;
				}
				if (line[0] == '[') {
					line = line.substr(1, line.size() - 2);
					name = line;
					AddSection(name);
				} else {
					auto del = line.find('=');
					key = line.substr(0, del);
					value = line.substr(del + 1, line.size() - 1);
					auto &table = sections[name];
					table[key] = value;
				}
			}
		}
		Section &AddSection(const string& name) {
			return sections[name];
		}

		const Section &GetSection(const string &name) const {
			return sections.at(name);
		}

		size_t SectionCount() const {
			return sections.size();
		}

	private:
		unordered_map <string, Section> sections;
	};

	Document Load(istream &input) {
		return Document{input};
	}
}