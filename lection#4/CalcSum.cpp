#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <numeric>

int calc_sum(std::vector<int> v) {
	return std::accumulate(v.begin(), v.end(), 0);
}

int main() {
	// создать задачу на основе функции.
	// packaged_task принимает в качестве параметра тип функции
	// на основе которой предполагается создавать задачу.
	std::packaged_task<int(std::vector<int>)> task(calc_sum);

	// получить фьючерс этой задачи
	std::future<int> result = task.get_future();

	std::vector<int> nums{ 1,2,3,4,5,6,7,8,9,10 };

	// задачу запустить в потоке, передав исходне данные 
	std::thread t(std::move(task), std::move(nums));

	t.join();

	// получить результат выполнения асинхронной задачи
	int sum = result.get();

	std::cout << "Сумма: " << sum << std::endl;

	// можно было обойтись лямбда функцией при инициализации packaged_task:
	std::packaged_task<int(std::vector<int>)> task1(
			[](std::vector<int> v) { return std::accumulate(v.begin(), v.end(), 0); });
	return 0;
}
