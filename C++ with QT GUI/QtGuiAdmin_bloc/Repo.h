#pragma once
#include "Locatar.h"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class RepoException {
	string msg;
public:
	RepoException(string mesaj) :msg{ mesaj } {
	};
	string get_mesaj() const;
};

//clasa abstracta 
class Repository {
protected:
	double lim_eroare;
public:
	~Repository() = default;
	virtual void add_locatar(const Locatar& locatar) = 0;
	virtual vector<Locatar> get_all_locatari() = 0;
	virtual void sterge_locatar(const int& apart) = 0;
	virtual void modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) = 0;
	virtual const Locatar& cauta_locatar(const int& apart_cautat) = 0;

};

class Repo : public Repository {
protected:
	unordered_map<int, Locatar> locatari;
public:
	Repo(double lim);
	Repo(const Repo& other) = delete; //pentru a sterge copiile ce se fac la transmiterea repo-ului prin valoare
	Repo() = default;	//am nevoie totusi de un constructor astfel il numesc pe cel default
	virtual void add_locatar(const Locatar& locatar);
	virtual vector<Locatar> get_all_locatari();
	virtual void sterge_locatar(const int& apart);
	virtual void modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou);
	virtual const Locatar& cauta_locatar(const int& apart_cautat);
};

class FileRepo : public Repo {
private:
	string filename;
	void citesc_tot_din_fisier();
	void tiparesc_tot_in_fisier();
public:
	FileRepo(string filename, double lim) : Repo(lim), filename{ filename } {
		citesc_tot_din_fisier();
	};

	void add_locatar(const Locatar& locatar) override;
	vector<Locatar> get_all_locatari() override;
	void sterge_locatar(const int& apart) override;
	void modifica_locatar(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) override;
	const Locatar& cauta_locatar(const int& apart_cautat) override;
};



void test_add_repo();
void test_sterge_repo();
void test_modificare_repo();
void test_caut_locatar();
void test_lim_eroare();
void test_repo_fis();