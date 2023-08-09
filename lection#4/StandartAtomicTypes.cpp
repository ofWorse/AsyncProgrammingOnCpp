#include <iostream>
#include <atomic>

int main() {
	std::atomic<int> value;
	
	std::cout << "Возвращаемое значение: " << value.fetch_add(5) << std::endl;
	std::cout << "Значение после операции: " << value << std::endl;

	std::cout << "Возвращаемое значение: " << value.fetch_sub(3) << std::endl;
	std::cout << "Значение после операции: " << value << std::endl;

	std::cout << "Возвращаемое значение: " << value++ << std::endl;
	std::cout << "Значение после операции: " << value << std::endl;

	std::cout << "Возвращаемое значение: " << ++value << std::endl;
	std::cout << "Значение после операции: " << value << std::endl;

	value += 1;
	std::cout << "Значение после операции: " << value << std::endl;

	value -= 1;
	std::cout << "Значение после операции: " << value << std::endl;
}
