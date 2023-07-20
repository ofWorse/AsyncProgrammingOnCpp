// --- СУММА ТИПОВ: ТИП VARIANT --- //
#include <variant>
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

int main() {
	std::variant <int, float, string> v, w;
	v = 12.0f; // индекс типа данных из variant<1,2,3,4...N>
	cout << std::get<1>(v) << endl;
	w = 20;
	cout << std::get<0>(w) << endl;
	w = "Hello"s; 
	cout << std::get<2>(w) << endl;
	return 0;
}

