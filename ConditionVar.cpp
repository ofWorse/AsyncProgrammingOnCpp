#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>

std::mutex numMutex;
std::condition_variable syncCond;
auto bEvenReady = false;
auto bOddReady = false;

void printEven(int max) {
	for(unsigned i = 0; i <= max; i += 2) {
		std::unique_lock<std::mutex> lk(numMutex);
		syncCond.wait(lk, [] { return bEvenReady; }); // ждем наступления события bEvenReady == true
		std::cout << i << ", ";
		bEvenReady = false;
		bOddReady = true;
		syncCond.notify_one();
	}
	std::cout << "\n";
}

void printOdd(int max) {
	for(unsigned i = 1; i <= max; i += 2) {
		std::unique_lock<std::mutex> lk(numMutex);
		syncCond.wait(lk, [] { return bOddReady; }); 
		std::cout << i << ", ";
		bEvenReady = true;
		bOddReady = false;
		syncCond.notify_one();
	}
	std::cout << "\n";
}

int main() {
	auto max = 100;
	bEvenReady = true;

	std::thread t1(printEven, max);
	std::thread t2(printOdd, max);

	if(t1.joinable()) t1.join();
	if(t2.joinable()) t2.join();
	return 0;
}

