#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
	vector<int> vec;
	for(int i = 0; i < 10; ++i)
		vec.push_back(i);
	int lower = 0, upper = 0;
	cout << "Enter the value range: ";
	cin >> lower >> upper;

	int result = count_if(vec.begin(), vec.end(),
			//   это список захвата \/ 
						  [lower, upper](int n) 
						  { return lower <= n && n < upper; });
	cout << result << endl;
	return 0;
}
