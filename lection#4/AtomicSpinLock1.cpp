#include <iostream>
#include <atomic>

class SpinLock {
std::atomic_flag flg;
public:
	SpinLock() : flg(ATOMIC_FLAG_INIT) {}
	void lock() {
		// захватить и войти в цикл ожидания
		while(flg.test_and_set(std::memory_order_acquire));
	}
	void unlock() {
		// освободить
		flg.clear(std::memory_order_release);
	}
};
