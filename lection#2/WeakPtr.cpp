#include <iostream>
#include <deque>
#include <memory>
using namespace std;

int main(int argc, char **argv) {
	std::shared_ptr<int> ptr1(new int(500));
	std::weak_ptr<int> wptr1 = ptr1;
	{
		std::shared_ptr<int> ptr2 = wptr1.lock();
		if(ptr2) cout << *ptr2 << endl; // будет выполнено
		// выход из области видимоти ptr2
	}
	ptr1.reset(); // объект уничтожается 
	
	std::shared_ptr<int> ptr3 = wptr1.lock();
	if(ptr3) cout << *ptr3 << endl;
	else cout << "Указатель пуст!" << endl;
	return 0;
}
