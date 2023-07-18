#include <iostream>
#include <memory>
#include <stdio.h>
using namespace std;

// объекты типа shared_ptr<T> можно передавать по значению:
// копия этого умного указателя указывает на тот же объект,
// а конструктор копирования увелививает счетчик ссылок
void foo_by_value(std::shared_ptr<int> i) { (*i)++; }

// передача объекта shared_ptr<T> по ссылке не создает копию 
void foo_by_reference(std::shared_ptr<int>& i) { (*i)++; }

int main() {
	auto sp = std::make_shared<int>(10);
	foo_by_value(sp);
	foo_by_reference(sp);
	// должно быть значение 12
	cout << *sp << endl;
	return 0;
}
