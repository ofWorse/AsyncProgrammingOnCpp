#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
std::mutex m;

int main() {
	std::vector<std::thread> threads;
	for(int i = 0; i < 5; ++i) {
		threads.push_back(std::thread( [i]() {
					std::lock_guard<std::mutex> guard(m);
					std::cout << "Поток " << i << std::endl;
					} ));
	}

	std::for_each(
			threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
	return 0;
}
