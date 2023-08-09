// --- СОЗДАНИЕ АСИНХРОННОЙ ЗАДАЧИ --- //
// данный метод выделения потока под задачу позволяет скрыть 
// подробности реализации ее выполнения.
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <future>

int calc_sum(std::vector<int> v) {
	return std::accumulate(v.begin(), v.end(), 0);
}

int main() {
	std::vector<int> nums{ 1,2,3,4,5,6,7,8,9,10 };

	// запустить фсинхронную задачу и получить ее фьючерс.
	std::future<int> result(std::async(
	// сразу и в отдельном потоке
				std::launch::async, calc_sum, std::move(nums)));

	// получить результат выполнения асинхронной задачи
	int sum = result.get();

	std::cout << "Сумма: " << sum << std::endl;

	// проще с лямбдой:
	std::future<int> result1(std::async(
			[](std::vector<int> v) { return std::accumulate(v.begin(), v.end(), 0); },
			std::move(nums)));
	return 0;
}
