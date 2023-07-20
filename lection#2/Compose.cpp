// --- КОМПОЗИЦИЯ ФУНКЦИЙ ---
// c++ -std=c++ Compose.cpp
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// базовый случай для рекурсивной компиляции:
template<typename F, typename G>
auto Compose(F&& f, G&& g) { return [=](auto x) { return f(g(x)); }; }

// рекурсия по аргументам во время компиляции:
template<typename F, typename ... R>
auto Compose(F&& f, R&& ... r) {
	return [=](auto x) { return f(Compose(r...)(x)); }; 
}

auto CurriedAdd3(int x) {
	return [x](int y) { // захват переменной x
		return [x, y](int z) { return x + y + z; };
	};
}

template<typename... Ts> 
auto particalFunctionAdd(Ts... xs) {
	static_assert(sizeof...(xs) <= 3);
	
	if constexpr (sizeof...(xs) == 3) 
		return (0 + ... + xs);
	else {
		return [xs...](auto... ys) {
			return particalFunctionAdd(xs..., ys...);
		};
	}
}

int main() {
	// композиция двух функций
	auto val = Compose(
		[](int const a) { return std::to_string(a); }, 
		[](int const a ) { return a * a; }) (4); // val = 16
	cout << val << endl;

	// вызов каррированной функции
	auto p = CurriedAdd3(4)(5)(6);
	cout << p << endl;

	// компиляуия многих функций
	auto func = Compose(
			[](int const n) { return std::to_string(n); },// 100s ^
			[](int const n) { return n * n; },            // 100  |
			[](int const n) { return n + n; },            // 10   |
			[](int const n) { return std::abs(n); });     // 5    |
	cout << func(5) << endl; // 100

	// Частичное применение функции
	particalFunctionAdd(1,2,3);
	particalFunctionAdd(1, 2)(3);
	particalFunctionAdd(1)(2)(3);

	return 0;
}
