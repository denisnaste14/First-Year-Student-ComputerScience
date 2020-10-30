#pragma once
#include "Locatar.h"
#include "Validator.h"
#include "Repo.h"
#include <string>

using std::string;

class Service {
private:
	Repo &repo;	//se transmite repo-ul prin referinta, evitand copiile
public:
	//Constuctor
	Service(Repo& r) :repo{ r } {
	}
	Service(Service& other) = delete;
	Service() = default;				//aceleasi explicatii ca la repo
	//Utils
	void add(int apart, string nume, double suprafata, string tip);
	vector_dinamic<Locatar>& get_all();
	void sterge(const int& apart);
	void modifica(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou);
	const Locatar& caut(const int& apart_cautat)const;
	void filtrare_dupa_suprafata(const double& suprafata, vector_dinamic<Locatar>& filtrate)const;
	void filtrare_dupa_tip(const string& tip, vector_dinamic<Locatar>& filtrate)const;
	void sortare_dupa_nume(vector_dinamic<Locatar>& sortate) ;
	void sortare_dupa_suprafata(vector_dinamic<Locatar>& sortate);
	void sortare_dupa_tip_si_suprafata(vector_dinamic<Locatar>& sortate);
};

void test_add_srv();
void test_sterge_srv();
void test_modifica_srv();
void test_cauta_srv();
void test_filtrare_dupa_suprafata();
void test_filtrare_dupa_tip();
void test_sortare_dupa_nume();
void test_sortare_dupa_suprafata();
void test_sortare_dupa_tip_si_suprafata();