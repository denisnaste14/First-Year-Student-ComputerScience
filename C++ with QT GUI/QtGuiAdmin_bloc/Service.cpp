#include "Service.h"
#include <cassert>
#include <algorithm>
#include <cstring>
#include <map>
#include <random>
#include <fstream>
#include <numeric>
#include <iostream>

using std::map;

void Service::add(int apart, string nume, double suprafata, string tip) {
	Locatar loc{ apart, nume, suprafata, tip };
	Validator valid{ loc };
	valid.valid();
	repo.add_locatar(loc);
	actiuniUndo.push_back(std::make_unique<UndoAdauga>(loc, repo));
}

vector<Locatar> Service::get_all()const {
	return repo.get_all_locatari();
}

void Service::sterge(const int& apart) {
	//creez un locatar cu date valide in afara de nr apartamentului pentru a testa daca acesta este valid 
	//fara a mai avea nevoie de o alta functie separata de validare 
	Locatar loc{ apart , "Denis", 43.5, "decomandat" };
	Validator valid{ loc };
	valid.valid();
	//aici se va ajunge doar daca apart este validat
	actiuniUndo.push_back(std::make_unique<UndoSterge>(repo.cauta_locatar(apart), repo));
	repo.sterge_locatar(apart);

}

void Service::modifica(const int& apart_cautat, const string& nume_nou, const double& suprafata_noua, const string& tip_nou) {
	//creez un locatar pentru a folosi functia de validare 
	Locatar loc{ apart_cautat,nume_nou,suprafata_noua,tip_nou };
	Validator valid{ loc };
	valid.valid();
	Locatar nemodificat = repo.cauta_locatar(apart_cautat);
	//
	repo.modifica_locatar(apart_cautat, nume_nou, suprafata_noua, tip_nou);
	actiuniUndo.push_back(std::make_unique<UndoModifica>(repo.get_all_locatari().back(), nemodificat, repo));
}

const Locatar& Service::caut(const int& apart_cautat)const {
	//creez un locatar cu date valide in afara de nr apartamentului pentru a testa daca acesta este valid 
	//fara a mai avea nevoie de o alta functie separata de validare 
	Locatar loc{ apart_cautat , "Denis", 43.5, "decomandat" };
	Validator valid{ loc };
	valid.valid();

	return repo.cauta_locatar(apart_cautat);
}

vector<Locatar> Service::filtrare_dupa_suprafata(const double& supraf)const {
	Locatar loc{ 10,"a",supraf,"decomandat" };
	Validator valid(loc);
	valid.valid();
	vector<Locatar> Filtrate;
	vector<Locatar> aux;
	aux = repo.get_all_locatari();
	std::copy_if(aux.begin(),
		aux.end(),
		std::back_inserter(Filtrate),
		[&supraf](auto& elem) {return elem.get_suprafata() == supraf; }
	);
	return Filtrate;
}

 vector<Locatar> Service::filtrare_dupa_tip(const string& tip)const {
	Locatar loc{ 10,"a",10,tip };
	Validator valid(loc);
	valid.valid();
	vector<Locatar> Filtrate;
	vector<Locatar> aux;
	aux = repo.get_all_locatari();
	std::copy_if(aux.begin(),
		aux.end(),
		std::back_inserter(Filtrate),
		[&tip](auto& elem) {return elem.get_tip() == tip; }
	);
	return Filtrate;
}

vector<Locatar> Service::sortare_dupa_nume() {
	auto locatari = repo.get_all_locatari();
	//sortare cu sort din algorithm
	sort(locatari.begin(), locatari.end(), [](const Locatar& loc1, const Locatar& loc2) {
		return loc1.get_nume() < loc2.get_nume();
		});
	return locatari;
}
vector<Locatar> Service::sortare_dupa_suprafata() {
	auto locatari = repo.get_all_locatari();
	//sortare cu sort din algorithm
	sort(locatari.begin(), locatari.end(), [](const Locatar& loc1, const Locatar& loc2) {
		return loc1.get_suprafata() < loc2.get_suprafata();
		});
	return locatari;
}

vector<Locatar> Service::sortare_dupa_tip_si_suprafata() {
	auto locatari = repo.get_all_locatari();
	//sortare cu sort din algorithm
	sort(locatari.begin(), locatari.end(), [](const Locatar& loc1, const Locatar& loc2) {
		if (loc1.get_tip() == loc2.get_tip())
			return loc1.get_suprafata() < loc2.get_suprafata();
		return loc1.get_tip() < loc2.get_tip();
		});
	return locatari;
}


vector<DTO> Service::statistica() {
	int nr_locatari = repo.get_all_locatari().size();
	auto locatari = repo.get_all_locatari();
	map<string, DTO> procentaje;

	for (auto& loc : locatari) {
		if (procentaje.find(loc.get_tip()) == procentaje.end()) {
			DTO aux{ loc.get_tip() };
			procentaje.insert({ loc.get_tip(), aux });
		}
		else {
			DTO aux = procentaje[loc.get_tip()];
			aux.contorizare();
			procentaje[loc.get_tip()] = aux;
		}
	}

	vector<DTO> stat;
	map<string, DTO>::iterator iter;
	iter = procentaje.begin();
	while (iter != procentaje.end()) {
		iter->second.set_procent(nr_locatari);
		stat.push_back(iter->second);
		iter++;
	}
	return stat;
}

void Service::add_in_cos(int apart) {
	Locatar aux{ apart, "ff", 100, "circular" };
	Validator valid{ aux };
	valid.valid();
	Locatar aux1 = repo.cauta_locatar(apart);
	cos.add_locatar(aux1);
	actiuniUndo.push_back(std::make_unique<UndoAdauga>(aux1, cos));
}

vector<Locatar> Service::toti_din_cos() {
	return cos.get_all_locatari();
}

void Service::goleste_lista() {
	for (auto& loc : cos.get_all_locatari())
		cos.sterge_locatar(loc.get_apart());
}

void Service::adauga_random_din_repo(int nr_locatari) {
	//nu am cum sa adaug in lista de notificare mai multi locatari decat am deja
	if (nr_locatari > (int)repo.get_all_locatari().size() - (int)cos.get_all_locatari().size())
		throw RepoException("Nu exista asa multi locatari in repository!\n");
	while (nr_locatari) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repo.get_all_locatari().size());
		int rndNr = dist(mt);
		try {
			cos.add_locatar(repo.cauta_locatar(rndNr));
			nr_locatari--;
		}
		catch (RepoException&) {
			continue;
		}
	}
}

vector<Locatar> Service::scrie_in_fisier(string numele_fisierului) {
	std::ofstream fout(numele_fisierului);
	if (!fout.is_open())
		throw RepoException("fisierul nu s-a putut deschide!");
	return cos.get_all_locatari();
}

void Service::undo() {
	if (actiuniUndo.empty())
		throw UndoException("NU se mai poate face nici o operatie de undo!\n");
	//daca ajung aici inseamna ca exista actiuni de undo posibile 
	actiuniUndo.back()->doUndo(); //apel polimorfic 
	actiuniUndo.pop_back();
}


//teste
void test_add_srv() {
	Repo r, cos;
	Service srv{ r, cos };
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
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(10, "Denis", 50, "circular");
	assert(srv.get_all().size() == 1);
	srv.sterge(10);
	assert(srv.get_all().size() == 0);
	try {
		srv.sterge(10);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar cautat inexistent!\n");
	}
}

void test_modifica_srv() {
	Repo r, cos;
	Service srv{ r,cos };
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
		assert(re.get_mesaj() == "Locatar cautat inexistent!\n");
	}
}

void test_cauta_srv() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(10, "Denis", 50, "circular");
	assert(srv.get_all().size() == 1);

	assert(srv.caut(10).get_apart() == 10);
	assert(srv.caut(10).get_nume() == "Denis");
	assert(srv.caut(10).get_suprafata() == 50);
	assert(srv.caut(10).get_tip() == "circular");
}

void test_filtrare_dupa_suprafata() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	auto lista = srv.filtrare_dupa_suprafata(10);
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 2);
}

void test_filtrare_dupa_tip() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	auto lista = srv.filtrare_dupa_tip("decomandat");
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 2);
}

void test_sortare_dupa_nume() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 10, "decomandat");
	srv.add(3, "a", 10, "circular");
	auto lista = srv.sortare_dupa_nume();
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 2);
}

void test_sortare_dupa_suprafata() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 20, "decomandat");
	srv.add(3, "a", 15, "circular");
	auto lista = srv.sortare_dupa_suprafata();
	assert(lista.at(0).get_apart() == 1);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 2);
}

void test_sortare_dupa_tip_si_suprafata() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "b", 20, "semidecomandat");
	srv.add(3, "a", 15, "circular");
	srv.add(4, "a", 11, "circular");
	auto lista = srv.sortare_dupa_tip_si_suprafata();
	assert(lista.at(0).get_apart() == 4);
	assert(lista.at(1).get_apart() == 3);
	assert(lista.at(2).get_apart() == 1);
	assert(lista.at(3).get_apart() == 2);
}

void test_add_in_cos() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	assert(srv.get_all().size() == 1);
	assert(r.cauta_locatar(1).get_suprafata() == 10);
	try {
		srv.add_in_cos(2);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar cautat inexistent!\n");
	}

	srv.add_in_cos(1);
	try {
		srv.add_in_cos(1);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Locatar deja existent in repo!\n");
	}
}

void test_toti_din_cos() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "a", 10, "decomandat");
	srv.add_in_cos(1);
	srv.add_in_cos(2);
	auto loc_cos = srv.toti_din_cos();
	assert(loc_cos.at(0).get_apart() == 1);
	assert(loc_cos.at(1).get_apart() == 2);
}

void test_goleste_lista() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "a", 10, "decomandat");
	srv.add_in_cos(1);
	srv.add_in_cos(2);
	assert(srv.toti_din_cos().size() == 2);
	srv.goleste_lista();
	assert(srv.toti_din_cos().size() == 0);
}

void test_add_random() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "a", 10, "decomandat");
	try {
		srv.adauga_random_din_repo(3);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_mesaj() == "Nu exista asa multi locatari in repository!\n");
	}
	srv.adauga_random_din_repo(2);
	assert(srv.toti_din_cos().size() == 2);
}

void test_statistica() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	srv.add(2, "a", 10, "decomandat");
	srv.add(3, "a", 10, "circular");
	srv.add(4, "a", 10, "circular");
	vector<DTO> stat_aux;
	stat_aux = srv.statistica();
	assert(stat_aux.at(0).get_solutie() == "circular 50.000000%\n");
	assert(stat_aux.at(1).get_solutie() == "decomandat 50.000000%\n");
}

void test_undo() {
	Repo r, cos;
	Service srv{ r,cos };
	srv.add(1, "a", 10, "decomandat");
	assert(r.get_all_locatari().size() == 1);
	srv.undo();
	assert(r.get_all_locatari().size() == 0);
	srv.add(1, "a", 10, "decomandat");
	srv.sterge(1);
	assert(r.get_all_locatari().size() == 0);
	srv.undo();
	assert(r.get_all_locatari().size() == 1);
	srv.modifica(1, "a", 11, "circular");
	assert(r.get_all_locatari().at(0).get_suprafata() == 11 && r.get_all_locatari().at(0).get_tip() == "circular");
	srv.undo();
	assert(r.get_all_locatari().at(0).get_suprafata() == 10 && r.get_all_locatari().at(0).get_tip() == "decomandat");
	srv.undo();
	try {
		srv.undo();
		assert(false);
	}
	catch (UndoException& ue) {
		assert(ue.get_mesaj() == "NU se mai poate face nici o operatie de undo!\n");
	}
}