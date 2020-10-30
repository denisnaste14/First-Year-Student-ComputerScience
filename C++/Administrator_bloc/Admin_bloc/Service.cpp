#include "Service.h"
#include <cassert>
#include <algorithm>
#include <cstring>
#include <vector>
using std::vector;

void Service::add(int apart, string nume, double suprafata, string tip) {
	Locatar loc{ apart, nume, suprafata, tip };
	Validator valid{ loc };
	valid.valid();
	repo.add_locatar(loc);
}

vector_dinamic<Locatar>& Service::get_all()  {
	return repo.get_all_locatari();
}

void Service::sterge(const int& apart) {
	//creez un locatar cu date valide in afara de nr apartamentului pentru a testa daca acesta este valid 
	//fara a mai avea nevoie de o alta functie separata de validare 
	Locatar loc{ apart , "Denis", 43.5, "decomandat" };
	Validator valid{ loc };
	valid.valid();
	//aici se va ajunge doar daca apart este validat
	repo.sterge_locatar(apart);
}

void Service::modifica(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) {
	//creez un locatar pentru a folosi functia de validare 
	Locatar loc{ apart_cautat,nume_nou,suprafata_noua,tip_nou };
	Validator valid{ loc };
	valid.valid();
	//
	repo.modifica_locatar(apart_cautat, nume_nou, suprafata_noua, tip_nou);
}

const Locatar& Service::caut(const int& apart_cautat)const {
	//creez un locatar cu date valide in afara de nr apartamentului pentru a testa daca acesta este valid 
	//fara a mai avea nevoie de o alta functie separata de validare 
	Locatar loc{ apart_cautat , "Denis", 43.5, "decomandat" };
	Validator valid{ loc };
	valid.valid();

	return repo.cauta_locatar(apart_cautat);
}

void Service::filtrare_dupa_suprafata(const double& suprafata, vector_dinamic<Locatar>& filtrate) const {
	Locatar loc{ 10,"a",suprafata,"decomandat" };
	Validator valid(loc);
	valid.valid();
	
	for (const Locatar& locatar : repo.get_all_locatari())
		if (locatar.get_suprafata() == suprafata)
			filtrate.push_back(locatar);

}

void Service::filtrare_dupa_tip(const string& tip, vector_dinamic<Locatar>& filtrate)const {
	Locatar loc{ 10,"a",10,tip };
	Validator valid(loc);
	valid.valid();
	for (const Locatar& locatar : repo.get_all_locatari())
		if (locatar.get_tip()==tip)
			filtrate.push_back(locatar);
}

void Service::sortare_dupa_nume(vector_dinamic<Locatar>& sortate) {
	vector<Locatar> pentru_sortat;
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		pentru_sortat.push_back(repo.get_all_locatari().at(i));
	//sortare cu sort din algorithm
	sort(pentru_sortat.begin(), pentru_sortat.end(), [](const Locatar& loc1, const Locatar& loc2) {
		return loc1.get_nume()<loc2.get_nume();
		});
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		sortate.push_back(pentru_sortat.at(i));
}

void Service::sortare_dupa_suprafata(vector_dinamic<Locatar>& sortate) {
	vector<Locatar> pentru_sortat;
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		pentru_sortat.push_back(repo.get_all_locatari().at(i));
	//sortare cu sort din algorithm
	sort(pentru_sortat.begin(), pentru_sortat.end(), [](const Locatar& loc1, const Locatar& loc2) {
		return loc1.get_suprafata() < loc2.get_suprafata();
		});
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		sortate.push_back(pentru_sortat.at(i));
}

void Service::sortare_dupa_tip_si_suprafata(vector_dinamic<Locatar>& sortate) {
	vector<Locatar> pentru_sortat;
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		pentru_sortat.push_back(repo.get_all_locatari().at(i));
	//sortare cu sort din algorithm
	sort(pentru_sortat.begin(), pentru_sortat.end(), [](const Locatar& loc1, const Locatar& loc2) {
		if (loc1.get_tip() == loc2.get_tip())
			return loc1.get_suprafata() < loc2.get_suprafata();
		return loc1.get_tip() < loc2.get_tip();
		});
	
	for (int i = 0; i < repo.get_all_locatari().size(); i++)
		sortate.push_back(pentru_sortat.at(i));

}

//teste
void test_add_srv() {
	Repo r;
	Service srv{ r };
	//adaugare buna
	try {
		srv.add(10, "Denis", 60.5, "decomandat");
		assert(true);
	}
	catch (ValidError&) {
		assert(false);
	}
	//verific daca chiar s-a adaugat
	assert(srv.get_all().size() == 1);
	//exceptii duplicat in repo
	try {
		srv.add(10, "Andrei", 61, "semidecomandat");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	//exceptii vlidare
	try {
		srv.add(11, "Andrei", 61, "jjj");
		assert(false);
	}
	catch (ValidError& vle) {
		assert(true);
		assert(vle.get_mesaj() == "Campul tip trebuie sa fie unul dintre: decomandat, semidecomandat, nedecomandat, circular sau open-space!!!\n");
	}
}

void test_sterge_srv() {
	Repo r;
	Service srv{ r };
	srv.add(10, "Denis", 50, "circular");
	assert(srv.get_all().size() == 1);
	srv.sterge(10);
	assert(srv.get_all().size()==0);
	try {
		srv.sterge(10);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar cautat pentru a fi sters, inexistent!\n");
	}
}

void test_modifica_srv() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 20, "decomandat");
	assert(srv.get_all().size() == 1);
	srv.modifica(1, "b", 50, "circular");
	assert(srv.get_all().size() == 1);
	//verific daca s-au facut modificarile
	assert(srv.get_all().back().get_nume() == "b");
	assert(srv.get_all().back().get_suprafata() == 50);
	assert(srv.get_all().back().get_tip() == "circular");
	try {
		srv.modifica(2, "b", 50, "circular");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar cautat pentru a fi modificat, inexistent!\n");
	}
}

void test_cauta_srv() {
	Repo r;
	Service srv{ r };
	srv.add(10, "Denis", 50, "circular");
	assert(srv.get_all().size() == 1);

	assert(srv.caut(10).get_apart() == 10);
	assert(srv.caut(10).get_nume() == "Denis");
	assert(srv.caut(10).get_suprafata() == 50);
	assert(srv.caut(10).get_tip() == "circular");
}

void test_filtrare_dupa_suprafata() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	vector_dinamic<Locatar> lista;
	srv.filtrare_dupa_suprafata(10,lista);
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 2);
}

void test_filtrare_dupa_tip() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	vector_dinamic<Locatar> lista;
	srv.filtrare_dupa_tip("decomandat", lista);
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 2);
}

void test_sortare_dupa_nume() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	srv.add(3, "a", 10, "circular");
	vector_dinamic<Locatar> lista;
	srv.sortare_dupa_nume(lista);
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 2);
}

void test_sortare_dupa_suprafata() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 20, "decomandat");
	srv.add(3, "a", 15, "circular");
	vector_dinamic<Locatar> lista;
	srv.sortare_dupa_suprafata(lista);
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 2);
}

void test_sortare_dupa_tip_si_suprafata() {
	Repo r;
	Service srv{ r };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 20, "semidecomandat");
	srv.add(3, "a", 15, "circular");
	srv.add(4, "a", 11, "circular");
	vector_dinamic<Locatar> lista;
	srv.sortare_dupa_tip_si_suprafata(lista);
	assert(lista.at(0).get_apart() == 4);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 1);
	assert(lista.at(3).get_apart() == 2);
}