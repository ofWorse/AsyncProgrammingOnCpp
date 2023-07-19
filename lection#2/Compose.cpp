// --- КОМПОЗИЦИЯ ФУНКЦИЙ ---
// c++ -std=c++ Compose.cpp
#include <iostream>
using namespace std;

// базовый случай для рекурсивной компиляции:
template<typename F, typename G>
auto Compose(F&& f, G&& g) { return [=](auto x) { return f(g(x)); }; }

// рекурсия по аргументам во время компиляции:
template<typename F, typename ... R>
auto Compose(F&& f, R&& ... r) {
	return [=](auto x) { return f(Compose(r...)(x)); }; 
}

// конструкция [=] означает захват значения всех переменных,
// доступных в текущей области видимости, и включить их в замыкание
// лямбда функции.

