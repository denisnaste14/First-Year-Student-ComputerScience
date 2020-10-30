#pragma once
#include "Service.h"
#include "Observer.h"
#include <unordered_map>


class Tipuri : public Observable {
private:
	Service& srv;
	unordered_map<string, int> tip_nr;

public:
	Tipuri(Service& srv) : srv{ srv } {
	}
	void cate_dinFiecare();
	vector<int> get_valori();
};