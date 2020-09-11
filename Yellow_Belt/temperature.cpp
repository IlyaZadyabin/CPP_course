#include <iostream>
#include <vector>

int main()
{
	int N, t, K = 0;
	int64_t av_temp = 0;
	std::cin >> N;

	std::vector<int> t_vec;

	for (int i = 0; i < N; i++) {
		std::cin >> t;
		t_vec.push_back(t);
		av_temp += t;
	}
	av_temp /= N;

	for (int i : t_vec) {
		K += (i > av_temp);
	}

	std::cout << K << std::endl;
	for (int i = 0; i < static_cast<int>(t_vec.size()); i++) {
		if (t_vec[i] > av_temp) {
			std::cout << i << std::endl;
		}
	}
}