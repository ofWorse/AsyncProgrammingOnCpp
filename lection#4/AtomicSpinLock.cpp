#include <iostream>
#include <atomic>

class spin_lock {
private:
	std::atomic_flag flg;
public:
	spin_lock() : flg(ATOMIC_FLAG_INIT) {}
	
	void lock() {
		// вход в критическую секцию: выполнять цикл, пока флаг
		// "занято" не сброшен, и сразу снова установить его
		while (flg.test_and_set(std::memory_order_acquire));
	}

	void unlock() {
		// выход из критической секции 
		flg.clear(std::memory_order_release);
	}
};
