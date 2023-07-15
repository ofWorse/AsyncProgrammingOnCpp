#include <iostream>
#include <vector>
#include <iterator>
#include <memory>
#include "Common2.h"
using namespace std;

class ConcreteEnumerable : public IEnumerable<int> {
private:
	int *_numberList;
	int _count;
	friend class Enumerator;
public:
	ConcreteEnumerable(int numbers[], int count):
		_numberList(numbers), _count(count) {}
	~ConcreteEnumerable() {}

	class Enumerator : public IEnumerator<int> {
	private:
		int *_inumbers, _icount, _index;
	public:
		Enumerator(int *numbers, int count):
			_inumbers(numbers), _icount(count), _index(0) {}
		bool hasMore() { return _index < _icount; }
		// строго говоря, следующий метод должен выбрасывать 
		// исключение при выходе индекса за допустимые границы;
		// пускай пока возвращает -1.
		int next() { return (_index < _icount) ? 
							_inumbers[_index++] : -1; }
		~Enumerator() {}
	};

	IEnumerator<int> *getEnumerator() {
		return new Enumerator(_numberList, _count);
	}
};

int main() {
	int x[] { 1,2,3,4,5 };
	ConcreteEnumerable *t = new ConcreteEnumerable(x, 5);
	IEnumerator<int> *numbers = t->getEnumerator();
	while(numbers->hasMore()) 
		cout << numbers->next() << endl;
	delete numbers;
	delete t;
	return 0;
}
