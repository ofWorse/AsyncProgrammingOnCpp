// --- ФНКЦИОНАЛЬНЫЕ ОБЪЕКТЫ - объекты классов, обладающие перегруженной операцией функционально применения --- 
#include <iostream>
#include <numeric>
using namespace std;

// функциональные объекты для сложения и умножения чисел
template<typename T> 
struct addition {
	T operator ()(T init, T a) { return init + a; }
};
template<typename T>
struct multiply {
	T operator ()(T init, T a) { return init * a; }
};

int main() {
	double v1[3] = { 1.0, 2.0, 4.0 };
	auto sum = accumulate(v1, v1 + 3, 0.0, addition<double>());
	cout << "Сумма: " << sum << endl;
	sum = accumulate(v1, v1 + 3, 0.0, 
			[](double a, double b) { return a + b; });
	cout << "Сумма: " << sum << endl;

	auto mul = accumulate(v1, v1 + 3, 1.0, multiply<double>());
	cout << "Произведение: " << mul << endl;
	mul = accumulate(v1, v1 + 3, 1.0,
			[](double a, double b) { return a * b; });
	cout << "Произведение: " << mul << endl;
	return 0;
}

