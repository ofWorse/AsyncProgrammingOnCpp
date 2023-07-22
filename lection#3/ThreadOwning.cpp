#include <iostream>
#include <thread>

void func1() { std::cout << "Функция 1\n"; }
void func2() { std::cout << "Функция 2\n"; }

int main() {
	std::thread t1(func1);
	// передача владения потоком от объекта t1 к t2.
	std::thread t2 = std::move(t1);
	t1 = std::thread(func2); // запускаем новый поток.
	
	std::thread t3;
	t3 = std::move(t2);

	// ожидать поток t2 не нужно. Он уже отвязан от потока.
	if(t1.joinable()) t1.join();
	if(t3.joinable()) t3.join();
	return 0;
}
