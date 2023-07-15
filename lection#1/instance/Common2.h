#pragma once

// стандартная заглушка для полноты интерфейса
struct CustomException {
	const char *what() const throw() {
		return "C++ exception";
	}
};

template<class T> class IEnumerator {
public:
	virtual bool hasMore() = 0;
	virtual T next() = 0;
};

template<class T> class IEnumerable {
public:
	virtual IEnumerator<T> *getEnumerator() = 0;
};

// Интерфейс для приема данных
template<class T> class IObserver {
public:
	virtual void onCompleted() = 0;
	virtual void onError(CustomException *exception) = 0;
	virtual void onNext(T value) = 0;
};

template<class T> class IObservable {
public:
	virtual bool subscribe(IObserver<T> &observer) = 0;
};



