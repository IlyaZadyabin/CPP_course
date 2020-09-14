#include "phone_number.h"
#include <iostream>
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
	stringstream s;
	char plus;
	s << international_number;
	s >> plus;
	std::getline(s, country_code_, '-');
	std::getline(s, city_code_, '-');
	s >> local_number_;

	if (plus != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw invalid_argument(international_number);
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
