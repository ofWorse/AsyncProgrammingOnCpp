#include <iostream>
using namespace std;

// ОПТИМАЛЬНЫЙ ВАРИАНТ КОНСТРУИРОВАНИЯ КЛАССА КАК ОБЪЕКТ, НАД КОТОРЫМ БУДЕТ ВОЗМОЖНОСТЬ ПРОВОДИТЬ БАЗОВЫЕ АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ

class Foo {
private:
	int *arr, size;

public:
	Foo(int s) {
		size = s;
		arr = new int[size]{0};
	}

	// Коприрующий конструктор
	Foo(const Foo& rhs) {
		cout << "Copy constructor.\n";
		size = rhs.size;
		arr = new int[size];

		for(int i{}; i < size; i++) arr[i] = rhs.arr[i];
	}

	// Чтобы не было копирования мы воспользуемся двойным амперсантом
	Foo(Foo&& rhs) noexcept { // не вызывает экспешенов
		cout << "move constructor.\n";
		size = rhs.size;
		arr = rhs.arr;
		rhs.arr = nullptr; // Уничтожаем ненужный объект
	}

	~Foo() {
		if(arr) delete[] arr;
	}

	// f + g; создает правое значение.
	Foo operator+(const Foo& rhs) {
		Foo temp(size + rhs.size);

		auto i = 0;
		for(; i < size; i++)
			temp[i] = arr[i];
		for(auto j = 0; j < rhs.size; i++, j++)
			temp[i] = rhs.arr[j];

		return temp;
	}

	// f = g; Оператор присваивания
	Foo& operator=(const Foo& rhs) {
		cout << "Copy assigment operator.\n";
		if(this == &rhs)
			return *this;
		if(arr) 
			delete[] arr;

		size = rhs.size;
		arr = new int[size];

		for(int i{}; i < size; i++) arr[i] = rhs.arr[i];

		return *this;
	}

	// оператор move
	Foo& operator=(Foo&& rhs) noexcept {
		cout << "move assigment.\n";
		size = rhs.size;
		arr = rhs.arr;
		rhs.arr = nullptr; // Уничтожаем ненужный объект
		return *this;	
	}

	int& operator[](int i) 
	{ return arr[i]; }

	int length() const
	{ return size; }

	// Поток консольного вывода в который записываются элементы массива объекта.
	friend ostream& operator<<(ostream& o, const Foo& rhs) {
		for(int i{}; i < rhs.size; i++) 
			o << rhs.arr[i] << " ";
		return o;
	}
};

int main() {
	Foo f(5);
	for(int i{}; i < f.length(); i++)
		f[i] = 3 * i;

	cout << f << endl;

	Foo g(f);
	cout << g << endl;

	Foo h(3);
	cout << h << endl;

	h = f + g; // f + g - временное выделение памяти для выполнения данной операции.
			   // Сэкономим время выполнения операций с помощью конструкции move!
	cout << h << endl;
}
