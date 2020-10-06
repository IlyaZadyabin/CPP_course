#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
using namespace std;

class Stats {
public:
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;

private:
	vector<string> data = {"GET", "POST", "PUT", "DELETE", "UNKNOWN",
						   "/", "/order", "/product", "/basket", "/help", "unknown"};
	map<string_view, int> methodStats = {
			{data[0], 0}, {data[1], 0}, {data[2], 0}, {data[3], 0}, {data[4], 0}
	};
	map<string_view, int> uriStats = {
			{data[5], 0}, {data[6], 0}, {data[7], 0}, {data[8], 0}, {data[9], 0}, {data[10], 0}
	};
};

HttpRequest ParseRequest(string_view line);