#include <iostream>
#include <vector>
#include <iterator>
#include <memory>
#include "Common2.h"
using namespace std;

class EvenNumberObservable : IObservable<int> {
private:
	int *_numbers;
	int _count;
public:
	EvenNumberObservable(int numbers[], int count):
		_numbers(numbers), _count(count) {}

	bool subscribe(IObserver<int> &observer) {
		for(int i = 0; i < _count; ++i) 
			if(_numbers[i] % 2 == 0)
				observer.onNext(_numbers[i]);
		observer.onCompleted();
		return true;
	}
};

class SimpleObserver : public IObserver<int> {
public:
	void onNext(int value) { cout << value << endl; }
	void onCompleted() { cout << "hello completed" << endl; }
	void onError(CustomException *ex) {}
};

int main() {
	int x[] { 1,2,3,4,5 };

	EvenNumberObservable *t = new EvenNumberObservable(x, 5);
	IObserver<int> *xy = new SimpleObserver();

	t->subscribe(*xy);

	delete xy;
	delete t;
	return 0;
}
