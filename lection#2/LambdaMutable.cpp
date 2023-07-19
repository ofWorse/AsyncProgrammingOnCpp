#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cstdlib>
using namespace std;

int main() {
	vector<int> vec;
	int init = 0; //       список параметров \/ обязан быть пустым.
	generate_n(back_inserter(vec), 10, [init]() mutable
			{ return init++; });
	ostream_iterator<int> outIter(cout, " ");
	copy(vec.begin(), vec.end(), outIter);
	cout << endl << "init: " << init << endl;
	return 0;
}
