#include <iostream>
#include <vector>
using namespace std;

class FloatBuffer {
	double *bfr;
	int count;
public:
	FloatBuffer() : bfr(nullptr), count(0) {}
	FloatBuffer(int pcount) : bfr(new double[pcount]), count(pcount) {}
	FloatBuffer(const FloatBuffer& other) : 
		count(other.count), bfr(new double[other.count]) 
		{ std::copy(other.bfr, other.bfr + count, bfr); }
	
	// Копирующая операция присваивания
	FloatBuffer& operator=(const FloatBuffer& other) {
		if(this != &other) {
			delete[] bfr; // освободить имеющийся буфер
			count = other.count;
			bfr = new double[count]; // создать новый буфер
			std::copy(other.bfr, other.bfr + count, bfr);
		}
		return *this;
	}

	// Перемещающий конструктор
	FloatBuffer(FloatBuffer&& other) : bfr(nullptr), count(0) {
		cout << "Перемещающий конструктор." << endl;
		// при перемещении не нужно копировать данные из объекта
		// можно просто забрать себе указатель на буфер
		bfr = other.bfr;
		count = other.count;
		// объект - источник более не владеет этими данными
		other.bfr = nullptr;
		other.count = 0;
	}

	// Переменная операция присваивания
	FloatBuffer& operator=(FloatBuffer&& other) {
		if(this != &other) {
			// освободить существующий буфер
			delete[] bfr;
			// забрать данные из объекта источника
			bfr = other.bfr;
			count = other.count;
			// объект-источник более не владеет этими данными
			other.bfr = nullptr;
			other.count = 0;
		}
		return *this;
	}
};

int main() {
	vector<FloatBuffer> v;
	v.push_back(FloatBuffer(25));
	v.push_back(FloatBuffer(75));
	return 0;
}

