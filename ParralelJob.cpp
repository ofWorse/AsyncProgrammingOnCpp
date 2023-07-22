#include <iostream>
#include <thread>

class parralel_job {
private:
	int& _iterations;
public:
	parralel_job(int& iterations) : _iterations(iterations) {} 
	void operator() () {
		for(int i = 0; i < _iterations; ++i) {
			// какая-то реализация
		}
	}
};

void func() {
	int local_var = 10000;
	parralel_job job(local_var);
	std::thread t(job);
	// если к потоку можно подключиться,
	// то подключаемся и ожидаем завершения.
	if(t.joinable()) t.join();
}



