#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

std::atomic<int> count = {0};

void func() {
	count.fetch_add(1, std::memory_order_relaxed);
}

int main() {
	
	std::vector<std::thread> v;
	for(int n = 0; n < 10; ++n) v.emplace_back(func);
	
	for(auto& t : v) t.join();

	std::cout << "Число потоков: " << count << std::endl;

	return 0;
}
