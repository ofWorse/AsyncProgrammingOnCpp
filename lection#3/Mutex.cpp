// Двоичный семафор - это механизм, ииспользуемый в паралельном программировании для 
// броьбы с гонками потоков. Основное назначение двоичного семафора состоит в том,
// чтобы не дать потоку войти в критическую секцию, пока другой поток находится в 
// своей критической секции.
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

std::mutex m;

int main() {
	std::vector<std::thread> threads;
	for(int i = 0; i < 5; ++i) {
		threads.push_back(std::thread( [i]() {
					m.lock();
					std::cout << "Поток " << i << std::endl;
					m.unlock();} ));
	}		

	std::for_each(
			threads.begin(),
			threads.end(),
			[](std::thread& t) { t.join(); });
	return 0;
}

