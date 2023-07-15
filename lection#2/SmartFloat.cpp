// --- ВЫРАЗИТЕЛЬНОСТЬ --- //
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// пример самодельной оберкти встроенного типа данных double
class SmartFloat {
private:
	double _value;
public:
	SmartFloat(double value) : _value(value) {}
	SmartFloat() : _value(0) {}
	SmartFloat(const SmartFloat &other) { _value = other._value; }

	// здесь мы переопределяем семантику втроенных типов.
	SmartFloat &operator=(const SmartFloat &other) {
		if(this != &other) { _value = other._value; } 
		return *this;
	}
	SmartFloat &operator=(double value) {
		_value = value; return *this;
	}	

	SmartFloat &operator++() { _value++; return *this; }
	SmartFloat &operator++(int) { /* постфиксная операция */
		SmartFloat nu(*this); ++_value; return nu; 
	}
	SmartFloat &operator--() { _value--; return *this; }
	SmartFloat &operator--(int) { /* постфиксная операция */
		SmartFloat nu(*this); --_value; return nu; 
	}
	SmartFloat &operator+=(int x) { _value += x; return *this; } 
	SmartFloat &operator-=(int x) { _value -= x; return *this; } 
	SmartFloat &operator*=(int x) { _value *= x; return *this; } 
	SmartFloat &operator/=(int x) { _value /= x; return *this; } 

	// обработка исключений
	bool operator>(const SmartFloat &other)
		{ return _value > other._value; }
	bool operator<(const SmartFloat &other)
		{ return _value < other._value; }
	bool operator==(const SmartFloat &other)
		{ return _value == other._value; }
	bool operator!=(const SmartFloat &other)
		{ return _value != other._value; }
	bool operator>=(const SmartFloat &other)
		{ return _value >= other._value; }
	bool operator<=(const SmartFloat &other)
		{ return _value <= other._value; }

	operator int() { return _value; }
	operator double() { return _value; }
	
	~SmartFloat() {}
};

double accumulate(double a[], int count) {
	double value = 0;
	for(int i = 0; i < count; ++i) { value += a[i]; }
	return value;
}

double accumulate(SmartFloat a[], int count) {
	SmartFloat value = 0;
	for(int i = 0; i < count; ++i) { value += a[i]; }
	return value;
}

template<class T>
T accumulate(T a[], int count) {
	T value = 0;
	for(int i = 0; i < count; ++i) { value += a[i]; }
	return value;
}

int main() {
	double x[] = { 10.0, 20.0, 30, 40 };
	SmartFloat y[] = { 10.0, 20.0, 30, 40 };
	double res = accumulate(x, 4); // Вызов с типом double
	cout << res << endl;
	res = accumulate(y, 4); // вызов с типом SmarFloat
	cout << res << endl;
	// шаблонизированная версия SmartFloat	
	/*
	 * SmartValue<double> y[] = { 10.0, 20.0, 30, 40 };
	 * double res = accumulate(y, 4);
	 * cout << res << endl;
	 * */
	return 0;
}
