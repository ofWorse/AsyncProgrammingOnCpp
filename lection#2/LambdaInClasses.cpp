#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

template<typename T>
class MyInitializer {
private: 
	int _val, _power;
public:
	MyInitializer(int base, int power) : _val(base), _power(power) {}
	void initializeVector(vector<T>& vec) {
		for_each(vec.begin(), vec.end(), [this](T& val) mutable
									{
										val = _val;
										_val *= _power;
									});
	}
};

int main() {
	vector<int> vec(11);
	MyInitializer<int> initializer(1, 2);
	initializer.initializeVector(vec);
	for_each(vec.begin(), vec.end(), [](int val) {cout << val << " ";});
	cout << endl;
	return EXIT_SUCCESS;
}
