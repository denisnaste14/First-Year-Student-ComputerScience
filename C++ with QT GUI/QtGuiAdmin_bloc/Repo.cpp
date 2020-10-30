#include "Repo.h"
#include <cassert>
#include <algorithm>
#include <fstream>
#include "Validator.h"

string RepoException::get_mesaj() const {
	return msg;
}

Repo::Repo(double lim) {
	lim_eroare = lim;
}
void Repo::add_locatar(const Locatar& locatar) {
	//if(locatari.find(locatar.get_apart())!=locatari.end())
		//throw RepoException("Locatar deja existent in repo!\n");
	double marja_eroare = ((rand() % 10) * 1.0) / 10;
	if (marja_eroare < lim_eroare)
		throw RepoException("Limita superioara de eroare atinsa!\n");
	else if (locatari.count(locatar.get_apart()) > 0)
		throw RepoException("Locatar deja existent in repo!\n");

	locatari.insert({ locatar.get_apart(),locatar });
}

vector<Locatar> Repo::get_all_locatari() {
	vector<Locatar> result;
	std::transform(locatari.begin(),
		locatari.end(),
		std::back_inserter(result),
		[](auto& key_value) {return key_value.second; });//functie labda- key_value este o referinta la un element din dictionar;iau doar valoarea care se afla la second
	return result;
}

void Repo::sterge_locatar(const int& apart) {
	double marja_eroare = ((rand() % 10) * 1.0) / 10;
	if (marja_eroare < lim_eroare)
		throw RepoException("Limita superioara de eroare atinsa!\n");
	if (locatari.find(apart) == locatari.end())
		throw RepoException("Locatar cautat pentru a fi sters, inexistent!\n");
	//stergerea din dictionar
	locatari.erase(apart);
}

void Repo::modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) {
	double marja_eroare = ((rand() % 10) * 1.0) / 10;
	if (marja_eroare < lim_eroare)
		throw RepoException("Limita superioara de eroare atinsa!\n");
	//caut sa vada daca exista locatarul care se vrea a fi modificat
	if (locatari.find(apart_cautat) == locatari.end())
		throw RepoException("Locatar cautat pentru a fi modificat, inexistent!\n");

	//daca am ajuns aici inseamna ca am gasit un locatar cu acel numar de apartament
	//modific locatarul
	locatari.at(apart_cautat).set_nume(nume_nou);
	locatari.at(apart_cautat).set_suprafata(suprafata_noua);
	locatari.at(apart_cautat).set_tip(tip_nou);
}

const Locatar& Repo::cauta_locatar(const int& apart_cautat) {
	/*if (locatari.find(apart_cautat) == locatari.end())
		throw RepoException("Locatar cautat inexistent!\n");
	return locatari.at(apart_cautat);*/
	double marja_eroare = ((rand() % 10) * 1.0) / 10;
	if (marja_eroare < lim_eroare)
		throw RepoException("Limita superioara de eroare atinsa!\n");
	auto it = std::find_if(locatari.begin(),
		locatari.end(),
		[&apart_cautat](auto key_value) {return key_value.first == apart_cautat; }
	);
	if (it == locatari.end())
		throw RepoException("Locatar cautat inexistent!\n");
	return it->second;		//al doilea parametru din key_value, adica Locatarul
}


//
//FileRepo
//
void FileRepo::citesc_tot_din_fisier() {
	std::ifstream fin(filename);

	if (!fin.is_open())
		throw RepoException("\nFisierul nu s-a putut deschide!\n");
	
	while (!fin.eof()) {
		int apart = 0;
		double suprafata;
		string nume, tip;
		fin >> apart >> nume >> suprafata >> tip;
		if (nume.empty())
			break;
		Locatar loc{ apart,nume,suprafata,tip };
		Validator valid{ loc };
		valid.valid();
		//daca trece de validare fara sa arunce exceptie, locatarul este bun 
		Repo::add_locatar(loc);
	}
	fin.close();
}

void FileRepo::tiparesc_tot_in_fisier() {
	std::ofstream fout(filename);
	if (!fout.is_open())
		throw RepoException("\nFisierul nu s-a putut deschide!\n");
	for (const Locatar& loc : Repo::get_all_locatari())
		fout << loc.get_apart() << " " << loc.get_nume() << " " << loc.get_suprafata() << " " << loc.get_tip() << "\n";
	fout.close();
}

void FileRepo::add_locatar(const Locatar& loc) {
	//citesc_tot_din_fisier();
	Repo::add_locatar(loc);
	tiparesc_tot_in_fisier();
}

vector<Locatar> FileRepo::get_all_locatari() {
	//citesc_tot_din_fisier();
	return Repo::get_all_locatari();
}

void FileRepo::sterge_locatar(const int& apart) {
	//citesc_tot_din_fisier();
	Repo::sterge_locatar(apart);
	tiparesc_tot_in_fisier();
}

void FileRepo::modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) {
	//citesc_tot_din_fisier();
	Repo::modifica_locatar(apart_cautat, nume_nou, suprafata_noua, tip_nou);
	tiparesc_tot_in_fisier();
}

const Locatar& FileRepo::cauta_locatar(const int& apart_cautat) {
	//citesc_tot_din_fisier();
	return Repo::cauta_locatar(apart_cautat);
}
//
//teste
//
void test_add_repo() {
	Repo r;
	Locatar loc{ 12,"D",18,"decomandat" };
	r.add_locatar(loc);
	assert(r.get_all_locatari().size() == 1);//verific ca am ceva in repo

	try {
		r.add_locatar(loc);
		assert(false);
	}
	catch (RepoException& re) {
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

void test_lim_eroare() {
	Repo r{ 1.0 };
	Locatar loc{ 1,"D",18,"decomandat" };
	try {
		r.add_locatar(loc);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Limita superioara de eroare atinsa!\n");
	}

}

void test_repo_fis() {
	FileRepo frepo{ "loc.txt", 0 };
	Locatar loc1{ 1,"D",18,"decomandat" };
	Locatar loc2{ 2,"a",19,"decomandat" };
	frepo.add_locatar(loc1);
	frepo.add_locatar(loc2);
	assert(frepo.get_all_locatari().size() == 2);
	frepo.modifica_locatar(1, "s", 20, "open-space");
	assert(frepo.get_all_locatari().at(0).get_nume() == "s" && frepo.get_all_locatari().at(0).get_suprafata() == 20);
	assert(frepo.cauta_locatar(2).get_suprafata() == 19);
	frepo.sterge_locatar(1);
	frepo.sterge_locatar(2);
	assert(frepo.get_all_locatari().size() == 0);
}
