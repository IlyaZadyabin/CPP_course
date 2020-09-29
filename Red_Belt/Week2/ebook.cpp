#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
	ReadingManager()
			: user_page_counts_(MAX_USER_COUNT_ + 1, 0),
			  users_() {}

	void Read(int user_id, int page_count) {
		if (user_page_counts_[user_id] == 0) {
			AddUser(user_id);
		}
		if (page_ratings.find(user_page_counts_[user_id]) != page_ratings.end()) {
			page_ratings[user_page_counts_[user_id]]--;
		}
		user_page_counts_[user_id] = page_count;
		page_ratings[page_count]++;
	}

	double Cheer(int user_id) const {
		if (user_page_counts_[user_id] == 0) {
			return 0;
		}
		const int user_count = GetUserCount();
		if (user_count == 1) {
			return 1;
		}
		const int page_count = user_page_counts_[user_id];
		int users_with_higher_rating = 0;
		for (auto it = page_ratings.find(page_count); it != page_ratings.end(); it++) {
			users_with_higher_rating += it->second;
		}
		return (user_count - users_with_higher_rating) * 1.0 / (user_count - 1);
	}

private:
	static const int MAX_USER_COUNT_ = 100'000;

	vector<int> user_page_counts_;
	vector<int> users_;
	map<int, int> page_ratings;

	int GetUserCount() const {
		return users_.size();
	}
	void AddUser(int user_id) {
		users_.push_back(user_id);
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}