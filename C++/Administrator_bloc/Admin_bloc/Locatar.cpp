#include "Locatar.h"
#include <cassert>

int Locatar::get_apart() const{
	return apart;
}

string Locatar::get_nume() const{
	return nume;
}

double Locatar::get_suprafata() const{
	return suprafata;
}

string Locatar::get_tip() const{
	return tip;
}

void Locatar::set_nume(const string& nume_nou) {
	//folosesc string operator=
	nume = nume_nou;
}

void Locatar::set_suprafata(const double& suprafata_noua) {
	suprafata = suprafata_noua;
}

void Locatar::set_tip(const string& tip_nou) {
	tip = tip_nou;
}

void test_domeniu() {
	Locatar loc{ 20,"a",50,"circular" };
	assert(loc.get_apart() == 20);
	assert(loc.get_nume() == "a");
	assert(loc.get_suprafata() == 50);
	assert(loc.get_tip() == "circular");
	//
	loc.set_nume("b");
	loc.set_suprafata(45.5);
	loc.set_tip("decomandat");
	//
	assert(loc.get_nume() == "b");
	assert(loc.get_suprafata() == 45.5);
	assert(loc.get_tip() == "decomandat");
}