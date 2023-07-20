// --- ЦИКЛЫ ПО ДИАПОЗОНАМ ИН НАБЛЮДАТЕЛИ ---
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
using namespace std;

template<long Start, long End>
class EnumerableRange {
public:
	class iterable : public std::iterator<
					 std::input_iterator_tag, // category (категория)
					 long,					  // value_type (тип значения)
					 long,                    // difference_type (тип разности)
					 const long*,			  // pointer type (тип указателя)
					 long>					  // reference type (тип ссылки)
	{
	private:
		long currentNum = Start;
	public:
		reference operator*() const { return currentNum; }
		explicit iterable(long val = 0) : currentNum(val) {}
		iterable& operator++() {
			currentNum = (End >= Start) ? currentNum+1 : currentNum-1;
			return *this;
		}
		iterable operator++(int) {
			iterable retval = *this;
			++(*this);
			return retval;
		}
		bool operator==(iterable other) const { return currentNum == other.currentNum; }
		bool operator!=(iterable other) const { return !(*this == other); }
	};
	iterable begin() { return iterable(Start); }
	iterable end() { return iterable(End >= Start ? End + 1 : End - 1); }
};

struct Observer {
	std::function<void(const long&)> ondata;
	std::function<void()> oncompleted;
	std::function<void(const std::exception &)> onexception;
};

template<long Start, long End>
class ObservableRange {
private:
	// контейнер наблюдателей
	vector<std::pair<const Observer&, int>> _observers;
	int _id = 0;
	class iterable : public std::iterator<
					 std::input_iterator_tag, // category (категория)
					 long,					  // value_type (тип значения)
					 long,                    // difference_type (тип разности)
					 const long*,			  // pointer type (тип указателя)
					 long>					  // reference type (тип ссылки)
	{
	private: int currentNum = Start;
	public: 
		reference operator*() const { return currentNum; }
		explicit iterable(long val = 0) : currentNum(val) {}
		iterable& operator++() {
			currentNum = (End >= Start) ? currentNum+1 : currentNum-1;
			return *this;
		}
		iterable operator++(int) {
			iterable retval = *this;
			++(*this);
			return retval;
		}
		bool operator==(iterable other) const { return currentNum == other.currentNum; }
		bool operator!=(iterable other) const { return !*(this == other); }
	};
	iterable begin() { return iterable(Start); }
	iterable end() { return iterable(End >= Start ? End + 1 : End - 1); }
	
	// генерировать значения из диапозона;
	// этот метод следовало бызывать с помощью std::async
	void generateAsync() {
		auto& subscribers = _observers;
		for(auto l : *this)
			for(const auto& obs : subscribers) {
				const Observer& ob = obs.first;
				ob.ondata(l);
			}
	}

public:
	// генерация последовательности
	void generate() { generateAsync(); }
	// подписка наблюдателей
	virtual int subscribe(const Observer& call) {
		_observers.emplace_back(call, ++_id);
		return _id;
	}
	// отписка наблюдателя не реализована для краткости примера
	virtual void unsub(const int subscribtion) {}
};

int main() {
	// воспользоваться циклом по диапозону
	for(long l : EnumerableRange<5, 25>()) { cout << l << endl; }
	cout << endl;

	// создать источник - экземпляр класса ObservableRange
	auto j = ObservableRange<10, 20>();
	// создать наблюдателя
	Observer testHandler;
	testHandler.ondata = [=](const long& r) { cout << r << endl; };
	// подписать пользователя на события от источника
	int cnt = j.subscribe(testHandler);
	j.generate(); // записать генератор
	
	return 0;
}

