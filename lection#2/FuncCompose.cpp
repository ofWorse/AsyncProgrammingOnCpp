// --- ОПЕРАЦИЯ КОМПОЗИЦИИ ФУНКЦИЙ ---
#include <iostream>
using namespace std;

struct AddOne {
	template<class T>
	auto operator()(T x) const { return x + 1; }
};

struct SumFunction {
	// функция двух аргументов
	template<class T>
	auto operator()(T x, T y) const { return x + y; }
};


