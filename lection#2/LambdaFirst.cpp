#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	auto num_vec = vector<int> { 10, 23, -33, 15, -7, 60, 80 };
	// лямбда функция для распознавания положительных чисел 
	auto filter = [](int const value) { return value > 0; };
	auto cnt = count_if(begin(num_vec), end(num_vec), filter);
	cout << cnt << endl;
	return 0;
}
