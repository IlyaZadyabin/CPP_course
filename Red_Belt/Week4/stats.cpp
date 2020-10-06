#include "stats.h"
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <algorithm>
using namespace std;

void Stats::AddMethod(string_view method) {
	if (methodStats.find(method) != methodStats.end()) {
		methodStats[method]++;
	} else {
		methodStats["UNKNOWN"]++;
	}
}
void Stats::AddUri(string_view uri) {
	if (uriStats.find(uri) != uriStats.end()) {
		uriStats[uri]++;
	} else {
		uriStats["unknown"]++;
	}
}
const map<string_view, int>& Stats::GetMethodStats() const {
	return methodStats;
}
const map<string_view, int>& Stats::GetUriStats() const {
	return uriStats;
}


HttpRequest ParseRequest(string_view line) {
	vector <string_view > result;

	for(int i = 0; line[0] == ' '; i++) {
		line.remove_prefix (1);
	}

	while(true) {
		size_t space = line.find(' ');
		result. push_back (line.substr (0, space));
		if (space == line.npos) {
			break;
		} else {
			line.remove_prefix (space + 1);
		}
	}
	return {result[0], result[1], result[2]};
}