#pragma once
#include "Observer.h"
#include "Service.h"
#include "Locatar.h"

class Cos :public Observable {
private:
	Service& srv;
public:
	Cos(Service& srv) : srv{ srv } {
	};
	void adauga_in_cos(int apart) {
		srv.add_in_cos(apart);
		notify();
	}
	void goleste_cos() {
		srv.goleste_lista();
		notify();
	}
	void undo() {
		srv.undo();
		notify();
	}
	void add_random(int nr) {
		srv.adauga_random_din_repo(nr);
		notify();
	}
	
	vector<Locatar> toti_din_cos() {
		return srv.toti_din_cos();
	}
};