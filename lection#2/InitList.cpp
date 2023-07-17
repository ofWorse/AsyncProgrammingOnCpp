// --- ЕДИНООБРАЗНЫЙ СИНТАКСИС ИНИЦИАЛИЗАЦИИ --- 
#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

template<class T>
struct VectorWrapper {
	vector<T> vctr;
	VectorWrapper(initializer_list<T> list) : vctr(list) {}
	void append(initializer_list<T> list)
		{ vctr.insert(vctr.end(), list.begin(), list.end()); }
};

int main() {
	VectorWrapper<int> vcw = { 1,2,3,4,5 }; // инициализация списком
	vcw.append({ 6,7,8 }); // инициализация аргумента списком
	for(auto n : vcw.vctr) cout << n << " ";
	cout << endl;	
	return 0;
}
