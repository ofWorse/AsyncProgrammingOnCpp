// --- АВТОМАТИЧЕСКИЙ ВЫВОД ТИПОВ --- //
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<string> vt = { "first", "second", "third", "fourth" };
	// явно указываем тип
	for(vector<string>::iterator it = vt.begin(); it != vt.end(); it++)
		cout << *it << " ";
	// поручить вывод типа компилятору
	for(auto it2 = vt.begin(); it2 != vt.end(); it2++) 	
		cout << *it2 << " ";
	return 0;
}
