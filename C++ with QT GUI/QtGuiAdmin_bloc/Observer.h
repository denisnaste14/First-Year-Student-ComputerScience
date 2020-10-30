#pragma once
#include <vector>

class Observer{
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> observers;
protected:
	void notify() {
		for (auto obs : observers)
			obs->update();
	}
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs),
			observers.end());
	}
};