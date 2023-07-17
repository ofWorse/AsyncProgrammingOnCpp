#include <iostream>
using namespace std;

int foo() { return 10; }
char bar() { return 'g'; } 
auto fancy() -> decltype(1.0f) { return 1; } // тип возврата - float

int main() {
	// тип переменной x такой, как тип возврата функции foo()
	// а тип переменной y - как тип возврата функции bar()
	decltype(foo()) x;
	decltype(bar()) y;
	cout << typeid(x).name() << endl;
	cout << typeid(y).name() << endl;

	struct A { double x; };
	const A *a = new A();
	decltype(a->x) z; // тип данных double
	decltype(a->x) t = z; // тип данных double&
	cout << typeid(z).name() << endl;
	cout << typeid(t).name() << endl;
	return 0;
}
