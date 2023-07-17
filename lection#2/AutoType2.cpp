#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

int main() {
	vector<double> vtdbl = { 0, 3.14, 2.718, 10.00 };
	auto vtdbl2 = vtdbl; // тип будет выведен
	auto size = vtdbl2.size(); // size_t
	auto &rvec = vtdbl; // ссылка н объект выведенного типа 
	cout << size << endl;
	for(auto it = vtdbl.begin(); it != vtdbl.end(); it++)
		cout << *it << " ";
	cout << endl;
	for(auto it = vtdbl2.begin(); it != vtdbl2.end(); it++)
		cout << *it << " ";
	cout << endl;
	rvec[0] = 100; // данное присваивание изменит первый элемент vtdbl
	for(auto it = vtdbl.begin(); it != vtdbl.end(); it++)
		cout << *it << " ";
	cout << endl;
	
	return 0;
}
