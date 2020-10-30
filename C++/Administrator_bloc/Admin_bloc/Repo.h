#pragma once
#include "Locatar.h"
#include "Lista.h"

class RepoException {
	string msg;
public:
	RepoException(string mesaj) :msg{ mesaj } {
	};
	string get_mesaj() const;
};

class Repo {
private:
	vector_dinamic<Locatar> locatari;
public:
	Repo(const Repo& other) = delete; //pentru a sterge copiile ce se fac la transmiterea repo-ului prin valoare
	Repo() = default;	//am nevoie totusi de un constructor astfel il numesc pe cel default
	void add_locatar(const Locatar& locatar);
	vector_dinamic<Locatar>& get_all_locatari();
	void sterge_locatar(const int& apart);
	void modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou);
	const Locatar& cauta_locatar(const int& apart_cautat)const;
};

void test_add_repo();
void test_sterge_repo();
void test_modificare_repo();
void test_caut_locatar();