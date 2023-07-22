#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

int main() {
	std::vector<std::thread> threads;
	for(int i = 0; i < 5; ++i) {
		threads.push_back(std::thread(
					[i]() { std::cout << "Поток " << i << std::endl; }));
	}
	std::cout << "\nГлавная функция.\n";
	std::for_each(threads.begin(),
				  threads.end(),
				  [](std::thread &t) { t.join(); });
	return 0;
}
