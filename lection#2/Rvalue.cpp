#include <iostream>
using namespace std;

int main() {
	int i = 0;
	cout << i << endl; // 0
	int& ri = i;
	ri = 20;
	cout << i << endl; // 20
	return 0;
}
