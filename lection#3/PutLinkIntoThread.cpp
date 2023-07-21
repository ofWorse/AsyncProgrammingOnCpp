#include <iostream>
#include <thread>

void update_data(shared_data& data);

void another_func() {
	shared_data data; // обеспечивает передачу именно ссылки на объект.
	std::thread t(update_data, std::ref(data));
	t.join();
	do_something_else(data);
}
