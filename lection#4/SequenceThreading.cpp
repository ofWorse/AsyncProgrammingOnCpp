#include <iostream>
#include <thread>
#include <atomic>

std::string result;
std::atomic<bool> ready(false);

void thread1() {
	while(!ready.load(std::memory_order_seq_cst));
	result += "согласованность";
}

void thread2() {
	result = "последовательная ";
	ready = true;
}

int main() {
	std::thread t1(thread1);
	std::thread t2(thread2);
	t1.join();
	t2.join();
	
	std::cout << "Результат: " << result << std::endl;

	return 0;
}

