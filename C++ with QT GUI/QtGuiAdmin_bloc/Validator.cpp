#include "Validator.h"
#include <cstring>
#include <vector>
#include <cassert>

using std::vector;
string  ValidError::get_mesaj() const {
	return mesaj;
}

void Validator::valid() {
	string erori;
	erori.clear();

	if (loc.get_apart() <= 0 || loc.get_apart() > 100)
		erori.append("Numarul apartamentului trebuie sa fie un numar intreg cuprins intre 0 si 100!!!\n");
	//verific daca stringul dat ca nume este un sir vid
	if (loc.get_nume().empty())
		erori.append("Campul nume trebuie sa contina un sir de caractere nevid!!!\n");
	if (loc.get_suprafata() < 0.9)
		erori.append("Suprafata nu poate fi mai mica decat 1 metru patrat!!!\n");
	//verific daca stringul dat ca nume este un sir vid
	if (loc.get_tip().empty())
		erori.append("Campul tip trebuie sa contina un sir de caractere nevid!!!\n");
	//verific si daca tipul este unul dintre cele posibile 
	vector<string> tipuri_posibile;
	tipuri_posibile.push_back("circular");
	tipuri_posibile.push_back("decomandat");
	tipuri_posibile.push_back("semidecomandat");
	tipuri_posibile.push_back("nedecomandat");
	tipuri_posibile.push_back("open-space");
	bool sem = false;
	for (const string& tip : tipuri_posibile)
		if (tip == loc.get_tip())
			sem = true;
	if (!sem)
		erori.append("Campul tip trebuie sa fie unul dintre: decomandat, semidecomandat, nedecomandat, circular sau open-space!!!\n");
	if (!erori.empty())
		throw ValidError(erori);
}

void test_validare() {
	//locatar bun
	Locatar loc{ 10 ,"d",99,"decomandat" };
	Validator val{ loc };
	try {
		val.valid();
		assert(true);
	}
	catch (ValidError&) {
		assert(false);
	}
	//locatar cu nr_apart gresit
	Locatar loc1{ 101 ,"d",99,"decomandat" };
	Validator val1{ loc1 };
	try {
		val1.valid();
		assert(false);
	}
	catch (ValidError&) {
		assert(true);
	}
	//Locatar cu nume vid
	Locatar loc2{ 10 ,"",99,"decomandat" };
	Validator val2{ loc2 };
	try {
		val2.valid();
		assert(false);
	}
	catch (ValidError&) {
		assert(true);
	}
	//Locatar cu supreafata apartamentului invalida
	Locatar loc3{ 10 ,"ff",0.4,"decomandat" };
	Validator val3{ loc3 };
	try {
		val3.valid();
		assert(false);
	}
	catch (ValidError&) {
		assert(true);
	}
	//Locatar cu tip vid si inexistent
	Locatar loc4{ 10 ,"ff",99,"" };
	Validator val4{ loc4 };
	try {
		val4.valid();
		assert(false);
	}
	catch (ValidError&) {
		assert(true);
	}
	//Locatar cu tip inexistent
	Locatar loc5{ 10 ,"",99,"garsoniera" };
	Validator val5{ loc5 };
	try {
		val5.valid();
		assert(false);
	}
	catch (ValidError&) {
		assert(true);
	}
}