#include <iostream>
#include <memory>
#include <stack>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class Stack {
private:
	std::stack<T> myData;
	mutable std::mutex myMutex;
	std::condition_variable myCond;
public:
	Stack() = default; // реализация по умолчанию, генерируемая компилятором.
	~Stack() = default;
	Stack& operator=(const Stack&) = delete; // запрещена операция присваивания (будет вылезать ошибка при компиляции)

	Stack(const Stack& that) {
		std::lock_guard<std::mutex> lock(that.myMutex);
		myData = that.myData;
	}

	void push(T new_val) {
		std::lock_guard<std::mutex> local_lock(myMutex);
		myData.push(new_val);
		myCond.notify_one();
	}

	bool try_pop(T& return_value) {
		std::lock_guard<std::mutex> local_lock(myMutex);
		if(myData.empty()) return false;
		return_value = myData.top();
		myData.pop();
		return true;
	}

	std::shared_ptr<T> try_pop() {
		std::lock_guard<std::mutex> local_lock(myMutex);
		if(myData.empty()) return std::shared_ptr<T>();
		std::shared_ptr<T> return_value(std::make_shared<T>(myData.top()));
		myData.pop();
		return return_value;
	}

	void wait_n_pop(T& return_value) {
		std::unique_lock<std::mutex> local_lock(myMutex);
		myCond.wait(
				local_lock,
				[this] { return !myData.empty(); });
		return_value = myData.top();
		myData.pop();
	}
	
	std::shared_ptr<T> wait_n_pop() {
		std::unique_lock<std::mutex> local_lock(myMutex);
		myCond.wait(
				local_lock,
				[this] { return !myData.empty(); });
		std::shared_ptr<T> return_value(std::make_shared<T>(myData.top()));	
		myData.pop();
		return return_value;
	}
};
