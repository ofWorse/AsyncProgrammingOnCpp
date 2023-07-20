// --- ВЫРАЖЕНИЯ-СВЕРТКИ ---
// c++ -std=c+1z
#include <iostream>
#include <functional>
using namespace std;

template<typename... Ts>
auto AddFoldLeftUn(Ts... args) { return (... + args); }
template<typename... Ts>
auto AddFoldLeftBin(int n, Ts... args) { return (n + ... + args); }
template<typename... Ts>
auto AddFoldRightUn(Ts... args) { return (args + ...); }
template<typename... Ts>
auto AddFoldRightBin(int n, Ts... args) { return (args + ... + n); }
template<typename T, typename... Ts>
auto AddFoldRightBinPoly(T n, Ts... args) { return (args + ... + n); }
template<typename T, typename... Ts>
auto AddFoldLeftBinPoly(T n, Ts... args) { return (n + ... + args); }

int main() {
	auto a = AddFoldLeftUn(1,2,3,4);
	cout << a << endl;
	cout << AddFoldRightBin(a, 4,5,6) << endl;

	// свертка справа налево 
	auto b = AddFoldRightBinPoly("C++ "s, "Hello "s, "World	"s);
	cout << b << endl;

	auto c = AddFoldLeftBinPoly("Hello "s, "World "s, "C++ "s);
	cout << c << endl;
	return 0;
}

