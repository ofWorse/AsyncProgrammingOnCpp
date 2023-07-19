#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main() {
	vector<int> vec;
	int init(0);
	generate_n(back_inserter(vec), 10, [&]() mutable 
			{ return init++; });
	ostream_iterator<int> outIter(cout, " ");
	copy(vec.begin(), vec.end(), outIter);
	cout << endl << "init: " << init << endl;
	// так как мы обратились к тому же участку памяти, 
	// в котором располежено значение init, на выходе мы получим не
	// 0, а 10.
	return EXIT_SUCCESS;
}
