#include <iostream>
#include <string>
#include <thread>

void thread_proc(std::string msg) {
	std::cout << "thread_proc days: " << msg << std::endl;
}

int main() {
	// создать поток и выполнить в нем функцию thread_proc
	std::thread t(thread_proc, "Hello, World!");
	t.join(); // дождаться завершения потока и завершить программу
	return 0;
}
