// --- КЛАССЫ-ОБЕРТКИ, std::function<прототип> --- //
// позволяет обращаться с функциями как с данными
#include <functional>
#include <iostream>
using namespace std;

void PrintNumber(int val) { cout << val << endl; }

// Класс с перегруженной операцией вызова
struct PrintNumber {
	void operator()(int i) { cout << i << endl; }
};

// Понадобится для вызова метода
struct FooClass {
	int number;
	FooClass(int pnum) : number(pnum) {}
	void PrintNumber(int val) const {
		cout << number + val << endl;
	}
};

int main() {
	// обертка над обычной функцией
	std::function<void(int)> displaynum = PrintNumber;
	// просто вызов
	displaynum(0xF000);
	// вызов посредством std::__invoke
	std::__invoke(displaynum, 0xF000);
	
	// обертка над лямбда функцией
	std::function<void()> lambdaprint = []() { PrintNumber(786); };
	lambdaprint();
	std::__invoke(lambdaprint);

	// обертка над методом класса
	std::function<void(const FooClass&, int)> 
		classdisplay = &FooClass::PrintNumber;
	// создать экземпляр
	const FooClass fooinstance(100);
	classdisplay(fooinstance, 100);
}
