#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<class T>
class EventSourceValueObserver;

template<class T>
class EventSourceValueSubject {
	vector<EventSourceValueObserver<T> *> sinks;
	T State;

public:
	EventSourceValueSubject() { State = 0; }
	~EventSourceValueSubject() {
		for(auto* n : sinks) delete n;
		sinks.clear();
	}
	
	bool Subscribe(EventSourceValueObserver<T>* sink) 	
	{ sinks.push_back(sink); }
	void NotifyAll() 
	{ for(auto sink : sinks) sink->Update(State); }
	T GetState() 
	{ return State; }
	void SetState(T pstate)
	{ State = pstate; NotifyAll(); }
};

// общий класс приемника событий
template<class T>
class EventSourceValueObserver {
	T OldState;
public:
	EventSourceValueObserver() : OldState(0) {}
	virtual ~EventSourceValueObserver() {}
	
	virtual void UpdateState(T state) {
		cout << "Старое состояние: " << OldState << endl;
		OldState = state;
		cout << "Новое состояние: " << state << endl;
	}
};

// специализированный наблюдатель
class AnotherObserver : public EventSourceValueObserver<double> {
public:
	AnotherObserver() : EventSourceValueObserver() {}
	virtual ~AnotherObserver() {}
	virtual void Update(double State) {
		cout << "Specialized observer" << endl;
	}
};

int main() {
	unique_ptr<EventSourceValueSubject<double>> evsrc(new EventSourceValueSubject<double>());
	// создать наблюдателей и подписать их на получение оповещений
	evsrc->Subscribe(new AnotherObserver());
	evsrc->Subscribe(new EventSourceValueObserver<double>());

	// изменим состояние источника событий, это должно
	// привести к вызову метода Update обоих наблюдателей.
	evsrc->SetState(100.1);
	return 0;
}
