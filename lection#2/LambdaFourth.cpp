#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// обобщенные функции для сравнения и обмена
template<typename T>
bool Cmp(T const& a, T const& b) { return (a > b); }
template<typename T>
void Swap(T& a, T& b) { T c = a; a = b; b = c; } 
// данные шаблоны понадобятся для сравнения двух элементов массива и их обмена
template<class T>
void selectionSort(T *arr, int length) {
	for(int i = 0; i < length - 1; ++i) 
		for(int j = i+1; j < length; ++j) 
			if(Cmp(arr[i], arr[j]))
				Swap(arr[i], arr[j]);
}

template<typename T>
void selectionSortLambda(T *arr, int length) {
	auto CmpLambda = [](const auto& a, const auto& b)
		{ return (a > b); };
	auto SwapLambda = [](auto& a, auto& b)
		{ auto c = a; a = b; b = c; };
	for(int i = 0; i < length - 1; ++i)
		for(int j = i+1; j < length; ++j)
			if(CmpLambda(arr[i], arr[j]))
				SwapLambda(arr[i], arr[j]);
}


int main() {
	double ar1[4] = { 20, 10, 15, -41 };	
	selectionSort(ar1, 4);
	for(int i = 0; i != 4; ++i) 
		cout << ar1[i] << " ";
	cout << endl;
	double ar2[4] = { 20, 10, 15, -41 };
	selectionSortLambda(ar2, 4);
	for(int i = 0; i != 4; ++i) 
		cout << ar2[i] << " ";
	cout << endl;
	
	return 0;
}
