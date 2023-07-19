#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
	auto num_vec = vector<int> { 10, 23, -30, 15, -7, 70, 60 };
	// определение бинарной операции поместить в аргумент
	auto acum = std::accumulate(
			std::begin(num_vec),
			std::end(num_vec),
			0,
			[](auto const s, auto const n) { return s + n; });
	cout << acum << endl;
	return 0;
}
