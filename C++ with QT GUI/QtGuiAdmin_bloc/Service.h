#pragma once
#include "Locatar.h"
#include "Validator.h"
#include "Repo.h"
#include <string>
#include <memory>
#include "Undo.h"

using std::string;
using std::unique_ptr;

class Service {
private:
	Repo& repo;	//se transmite repo-ul prin referinta, evitand copiile
	Repo& cos;
	vector<unique_ptr<ActiuneUndo>> actiuniUndo;

public:
	//Constuctor
	Service(Repo& r, Repo& cos) :repo{ r }, cos{ cos }{
	}
	Service(Service& other) = delete;
	Service() = default;				//aceleasi explicatii ca la repo
	~Service() = default;
	//Utils
	void add(int apart, string nume, double suprafata, string tip);
	vector<Locatar> get_all()const;
	void sterge(const int& apart);
	void modifica(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou);
	const Locatar& caut(const int& apart_cautat)const;
	vector<Locatar> filtrare_dupa_suprafata(const double& suprafata)const;
	vector<Locatar> filtrare_dupa_tip(const string& tip)const;
	vector<Locatar> sortare_dupa_nume();
	vector<Locatar> sortare_dupa_suprafata();
	vector<Locatar> sortare_dupa_tip_si_suprafata();
	vector<DTO> statistica();
	//actiuni pe cos
	void add_in_cos(int apart);
	vector<Locatar> toti_din_cos();
	void goleste_lista();
	void adauga_random_din_repo(int nr_locatari);
	vector<Locatar> scrie_in_fisier(string numele_fisierului);

	//undo
	void undo();
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
void test_add_in_cos();
void test_toti_din_cos();
void test_goleste_lista();
void test_add_random();
void test_statistica();
void test_undo();