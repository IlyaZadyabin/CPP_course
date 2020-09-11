#include  <iostream>

int main()
{
	int N;
	uint64_t R, W, H, D, ans = 0;
	std::cin >> N >> R;

	for (int i = 0; i < N; i++) {
		std::cin >> W >> H >> D;
		ans += W * H * D * R;
	}
	std::cout << ans;
}