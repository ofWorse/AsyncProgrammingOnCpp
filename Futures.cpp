// --- ФЬЮЧЕРСЫ И ОБЕЩАНИЯ --- 
#include <exception>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>

// обещание pr связано с запущеной задачей
template<typename T>
void func1(std::promise<T>& pr) {
	try {
		T val;
		process_data(val); // вычислить значение 
		// значение будет получено через future<T>::get()
		pr.set_value(val);
	} catch(...) {
		// исключение будет получено в future<T>::get()
		pr.set_exception(std::current_exception());
	}
}

// фьючерс ft связан с уже запущеной задачей
template<typename T>
void func2(std::future<T>& ft) {
	try {
		// если соответствующему обещанию установлено состояние
		// ошибки, следующий вызов выбросит исключение, иначе - 
		// вернет установленное в обещании значение.
		T result = ft.get();
		handle_value(result); // обрабоать полученные данные 
	} catch(...) {
		// обработать исключение
	}	
}
