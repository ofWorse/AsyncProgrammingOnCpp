#include <iostream>
#include <atomic>

int main() {
	bool expected = false;
	std::atomic<bool> flg;
	
	flg.compare_exchange_weak(expected, true, std::memory_order_acq_rel, std::memory_order_acquire);
	flg.compare_exchange_weak(expected, true, std::memory_order_release);

	return 0;
}
