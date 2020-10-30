#include "Lista.h"


void test_vector_dinamic_iterator() {
	vector_dinamic<Locatar> vd;
	vector_dinamic<Locatar> vd1;
	assert(vd.size() == 0);
	Locatar loc{ 10,"dd",10,"decomandat" };
	Locatar loc1{ 11,"ff",20,"semidecomandat" };
	vd.push_back(loc);
	vd.push_back(loc1);
	assert(vd.size() == 2);
	assert(vd.begin().operator*().get_apart() == 10);
	assert(vd.begin().operator++().operator*().get_apart() == 11);
	vd1 = vd;
	assert(vd1.begin().operator*().get_apart() == 10);
	assert(vd.begin().operator*().get_apart() == 10);
}

void range_for_test() {
	vector_dinamic<Locatar> vd;
	Locatar loc{ 10,"dd",10,"decomandat" };
	Locatar loc1{ 11,"ff",20,"semidecomandat" };
	vd.push_back(loc);
	vd.push_back(loc1);
	for (const auto& locatar : vd)
		assert(locatar.get_apart() == 10 || locatar.get_apart() == 11);
	//voi verifica si daca se face extinderea vectorului dinamic cand adaug 10 elemente
	Locatar loc2{ 12,"ff",20,"semidecomandat" };
	Locatar loc3{ 13,"ff",20,"semidecomandat" };
	Locatar loc4{ 14,"ff",20,"semidecomandat" };
	Locatar loc5{ 15,"ff",20,"semidecomandat" };
	Locatar loc6{ 16,"ff",20,"semidecomandat" };
	Locatar loc7{ 17,"ff",20,"semidecomandat" };
	Locatar loc8{ 18,"ff",20,"semidecomandat" };
	Locatar loc9{ 19,"ff",20,"semidecomandat" };
	Locatar loc10{ 20,"ff",20,"semidecomandat" };
	vd.push_back(loc2);
	vd.push_back(loc3);
	vd.push_back(loc4);
	vd.push_back(loc5);
	vd.push_back(loc6);
	vd.push_back(loc7);
	vd.push_back(loc8);
	vd.push_back(loc9);
	vd.push_back(loc10);
	assert(vd.size() == 11);
	assert(vd.begin().operator*().get_apart() == 10);
	assert(vd.back().get_apart() == 20);
	assert(vd.at(10).get_apart() == 20);
	vd.pop_back();
	assert(vd.back().get_apart() == 19);
}