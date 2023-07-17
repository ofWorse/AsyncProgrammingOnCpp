// --- ВАРИАДИЧЕСКИЕ ШАБЛОНЫ ---
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

// база для рекурсивной компиляции 
int add() { return 0; } // условие завершения рекурсии

// Вариадический шаблон функции:
// компилятор сгенерирует конкретную функцию,
// исходя из количества и типов аргументов,
// с которыми она вызвана.
template<class T0, class ... Ts>
decltype(auto) add(T0 first, Ts ... rest) {
	return first + add(rest...);
}

int main() {
	int n = add(0,2,3,4);
	cout << n << endl;
	return 0;
}
