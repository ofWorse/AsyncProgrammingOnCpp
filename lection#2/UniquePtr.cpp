#include <iostream>
#include <deque>
#include <memory>
using namespace std;

int main(int argc, char **argv) {
	// умный указатель на двустороннюю очередь
	unique_ptr<deque<int>> dq(new deque<int>);
	// наполнить значениями через перегруженную операцию ->
	dq->push_front(10);
	dq->push_front(20);
	dq->push_back(23);
	dq->push_front(16);
	dq->push_back(41);
	
	auto dqiter = dq->begin();
	while(dqiter != dq->end()) {
		cout << *dqiter << " ";
		dqiter++;
	}
	cout << endl;

	// вывод из области видимости умного указателя влечет
	// вызов его деструктора, который уничтожает объект
	return 0;
}
