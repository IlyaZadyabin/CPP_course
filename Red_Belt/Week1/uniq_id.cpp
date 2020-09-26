#include <string>
#include <vector>
using namespace std;

#define g(a) _##a
#define f(a) g(a)
#define UNIQ_ID f(__LINE__)

int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = {"hello", "world"};
	vector<int> UNIQ_ID = {1, 2, 3, 4};
}
