#pragma once
#include "Service.h"

class UI {
private:
	Service &srv;
protected:
	//functii pe care le folosesc metodele publice din aceasta clasa
	bool este_int(string aux);
	bool este_double(string aux);
public:
	UI(Service &srv):srv{srv}{
	}
	void run();
};