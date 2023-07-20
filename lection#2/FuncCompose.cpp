// --- ОПЕРАЦИЯ КОМПОЗИЦИИ ФУНКЦИЙ ---
#include <iostream>
#include <string>
#include <utility>
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

// унарная функция с замыканием,
// использован пакет параметров вариадического шаблона
template<class F>
struct PipableClosure : F {
	template<class... Xs>
	PipableClosure(Xs&&... xs) : // Xs - универсальная ссылка
	F(std::forward<Xs>(xs)...) {} // совершенная передача
};

// преобразователь функции в замыкание 
template<class F>
auto MakePipeClosure(F f) {
	return PipableClosure<F>(std::move(f));
}

// замыкание функции двух аргументов
template<class F>
struct PipableClosureBinary {
	template<class... Ts>
	auto operator()(Ts... xs) const {
		return MakePipeClosure(
				[=](auto x) -> decltype(auto) { return F()(x, xs...);});
	}
};

// операция композиции,
// использована совершенная передача
template<class T, class F>
// сохраняет модификатор доступа в отличии от auto
decltype(auto) operator|(T&& x, const PipableClosure<F>& pfn) {
	return pfn(std::forward<T>(x));
}

int main() {
	// замыкание унарной функции
	const PipableClosure<AddOne> fnclosure = {};
	int value = 1 | fnclosure | fnclosure; // 1 + 1 + 1
	cout << value << endl;

	// замыкание функции двух аргументов
	const PipableClosureBinary<SumFunction> sumFunction = {};
	//          1 + 2 + 5 + 1
	int vakue = 1 | sumFunction(2) | sumFunction(5) | fnclosure;
	cout << vakue << endl;
	return 0;
}


