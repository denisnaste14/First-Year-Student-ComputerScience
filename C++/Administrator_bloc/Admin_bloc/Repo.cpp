#include "Repo.h"
#include <cassert>

string RepoException::get_mesaj() const{
	return msg;
}

void Repo::add_locatar(const Locatar& locatar) {
	for (const Locatar& loc : locatari)
		if (loc.get_apart() == locatar.get_apart())
			throw RepoException("Locatar deja existent in repo!\n");
	locatari.push_back(locatar);
}

vector_dinamic<Locatar>& Repo::get_all_locatari() {
	return locatari;
}

void Repo::sterge_locatar(const int &apart) {
	int index_gasit = -1;
	for (int i = 0; i < (int)locatari.size(); i++)
		if (locatari.at(i).get_apart() == apart)
			index_gasit = i;
	if (index_gasit == -1)
		throw RepoException("Locatar cautat pentru a fi sters, inexistent!\n");
		
	//mut elementele din vector in stanga cu o pozitie incepand "acoperindu-l pe cel cu indexul gasit"
	for (int i = index_gasit; i < (int)locatari.size() - 1; i++)
		locatari.at(i) = locatari.at(i + 1);
	//acum scot ultimul element  care oricum este "dublat" in penultimul element
	//void avea acum o contradicite in ceea ce priveste repo deoarece ultimul element apare de 2 ori
	//dar urmeaza sa il elimin acum

	locatari.pop_back();
}

void Repo::modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) {
	//caut sa vada daca exista locatarul care se vrea a fi modificat
	int index_gasit = -1;
	for (int i = 0; i < (int)locatari.size(); i++)
		if (locatari.at(i).get_apart() == apart_cautat)
			index_gasit = i;
	if (index_gasit == -1)
		throw RepoException("Locatar cautat pentru a fi modificat, inexistent!\n");

	//daca am ajuns aici inseamna ca am gasit un locatar cu acel numar de apartament
	//modific locatarul
	locatari.at(index_gasit).set_nume(nume_nou);
	locatari.at(index_gasit).set_suprafata(suprafata_noua);
	locatari.at(index_gasit).set_tip(tip_nou);
}

const Locatar& Repo::cauta_locatar(const int& apart_cautat)const {
	int index_gasit = -1;
	for (int i = 0; i < locatari.size(); i++)
		if (locatari.at(i).get_apart() == apart_cautat)
			index_gasit = i;
	if (index_gasit == -1)
		throw RepoException("Locatar cautat inexistent!\n");

	return locatari.at(index_gasit);
}

//teste
void test_add_repo() {
	Repo r;
	Locatar loc{ 1,"D",18,"garsoniera" };
	r.add_locatar(loc);
	assert(r.get_all_locatari().size() == 1);//verific ca am ceva in repo

	try {
		r.add_locatar(loc);
		assert(false);
	}
	catch (RepoException& re) {
		assert(true);
		assert(re.get_mesaj() == "Locatar deja existent in repo!\n");
	}
	
}	

void test_sterge_repo() {
	Repo r;
	Locatar loc{ 1,"D",18,"decomandat" };
	r.add_locatar(loc);
	Locatar loc1{ 2,"A",49,"circular" };
	r.add_locatar(loc1);
	assert(r.get_all_locatari().size() == 2);

	r.sterge_locatar(1);
	assert(r.get_all_locatari().size() == 1);
	try {
		r.sterge_locatar(1);
		assert(false);
	}
	catch (RepoException& re) {
		assert(true);
		assert(re.get_mesaj() == "Locatar cautat pentru a fi sters, inexistent!\n");
	}
}

void test_modificare_repo() {
	Repo r;
	Locatar loc{ 1,"D",18,"decomandat" };
	r.add_locatar(loc);
	assert(r.get_all_locatari().size() == 1);
	//modific locatarul adaugat
	r.modifica_locatar(1, "puya", 50, "semidecomandat");
	assert(r.get_all_locatari().back().get_nume() == "puya");
	assert(r.get_all_locatari().back().get_suprafata() == 50);
	assert(r.get_all_locatari().back().get_tip() == "semidecomandat");
}

void test_caut_locatar() {
	Repo r;
	Locatar loc{ 1,"D",18,"decomandat" };
	r.add_locatar(loc);
	assert(r.get_all_locatari().size() == 1);
	try {
		r.cauta_locatar(2);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar cautat inexistent!\n");
	}
	assert(r.cauta_locatar(1).get_apart() == 1);
	assert(r.cauta_locatar(1).get_nume() == "D");
	assert(r.cauta_locatar(1).get_suprafata() == 18);
	assert(r.cauta_locatar(1).get_tip() == "decomandat");
}