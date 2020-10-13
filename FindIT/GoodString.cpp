#include <iostream>
#include <string>
#include <algorithm>

bool isLegalSymbol(const char& s) {
	return (s == 'I' || s == 'i' || s == 'B' || s == 'b' || s == 'S' || s == 's');
}

std::string CheckIfGood(std::string& str) {
	bool is_good = true;
	bool I_presents = false, B_presents = false, S_presents = false;

	str.erase(
				std::remove_if(str.begin(), str.end(), [](auto & s) { return (!isLegalSymbol(s)); }),
				str.end()
			);

	for (auto & letter : str) {
		if (toupper(letter) == 'I') {
			if (B_presents || S_presents) {
				is_good = false;
				break;
			}
			I_presents = true;
		} else if (toupper(letter) == 'B') {
			if (!I_presents || S_presents) {
				is_good = false;
				break;
			}
			B_presents = true;
		} else if (toupper(letter) == 'S') {
			if (!I_presents || !B_presents) {
				is_good = false;
				break;
			}
			S_presents = true;
		}
	}
	if (is_good && I_presents && B_presents && S_presents) {
		return str;
	} else {
		return std::string("0");
	}
}

int main() {
	for (std::string line; std::getline(std::cin, line);) { //получаем строку
		std::cout << CheckIfGood(line) << std::endl; //в качестве ответа возвращаем строку
	}
	return 0;
}