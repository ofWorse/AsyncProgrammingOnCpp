#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

// Глобальные семафоры
std::mutex evenMutex;
std::mutex oddMutex;

// Функция для печати четных чисел
void printEven(int max) {
	for(unsigned i = 0; i <= max; i += 2) {
		evenMutex.lock();
		std::cout << i << ", ";
		oddMutex.lock();
		evenMutex.unlock();
		oddMutex.unlock();
	}
	std::cout << "\n";
}

// Функция для печати нечетных чисел
void printOdd(int max) {
	for(unsigned i = 1; i <= max; i += 2) {
		evenMutex.lock();
		std::cout << i << ", ";
		oddMutex.lock();
		evenMutex.unlock();
		oddMutex.unlock();
	}
	std::cout << "\n";
}

int main() {
	auto max = 100;

	std::thread t1(printEven, max);
	std::thread t2(printOdd, max);

	if(t1.joinable()) t1.join();
	if(t2.joinable()) t2.join();

	return 0;
}


