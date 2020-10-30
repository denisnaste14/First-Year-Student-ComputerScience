#include "UI.h"
#include <iostream>
#include <iomanip>
#include "Lista.h"

using std::cin;
using std::cout;
using std::setw;
void UI::run() {
	cout << "0. Exit\n1. Adauga locatar\n2. Afisarea tuturor locatarilor\n3. Sterge locatar\n4. Modifica locatar\n5. Cauta locatar\n6. Filtrare\n7. Sortare\n\n";
	while (true) {
		int comanda;
		cout << "Adaugati o comanda: ";
		cin >> comanda;
		if (comanda == 0)
			break;
		if (comanda == 1) {
			int apart;
			string nume;
			double suprafata;
			string tip;
			string aux;
			cout << "  Numarul apartamentului: ";
			cin >> aux;
			//verific ca am citit un nr pentru apartament
			if (este_int(aux))
				apart = std::atoi(aux.c_str());	//functia c_str transforma stringul intr-un char pentru a putea folosi atoi
			else {
				cout << "Numarul apartamentului trebuie sa fie de tip intreg!\n";
				continue;
			}
			cout << "  Numele locatarului: ";
			cin >> nume;
			cout << "  Suprafata apartamentului: ";
			cin >> aux;
			if (este_double(aux))
				suprafata = std::atof(aux.c_str());
			else {
				cout << "Suprafata apartamentului trebuie sa fie un numar rational!\n";
				continue;
			}
			cout << "  Tipul apartamentului: ";
			cin >> tip;
			try {
				srv.add(apart, nume, suprafata, tip);
				cout << "\n			Locatar adaugat cu succes!\n";
			}
			catch (ValidError& vle) {
				cout << vle.get_mesaj();
			}
			catch (RepoException& re) {
				cout << re.get_mesaj();
			}
		}
		else if (comanda == 2) {
			for (const Locatar& loc : srv.get_all())
				cout << setw(3)<<loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() <<setw(19) << loc.get_tip() << "\n";
		}
		else if (comanda == 3) {
			int apart;
			string aux;
			cout << "  Numarul apartamentului: ";
			cin >> aux;
			if (este_int(aux))
				apart = std::atoi(aux.c_str());
			else {
				cout << "Numarul apartamentului trebuie sa fie de tip intreg!\n";
				continue;
			}
			try {
				srv.sterge(apart);
				cout << " \n			Locatar sters cu succes!\n";
			}
			catch (ValidError& vle) {
				cout << vle.get_mesaj();
			}
			catch (RepoException& re) {
				cout << re.get_mesaj();
			}
		}
		else if (comanda == 4) {
			int apart_cautat;
			string nume_nou;
			double suprafata_noua;
			string tip_nou;
			string aux;
			cout << "  Numarul apartamentului de modificat: ";
			cin >> aux;
			if (este_int(aux))
				apart_cautat = std::atoi(aux.c_str());	
			else {
				cout << "Numarul apartamentului trebuie sa fie de tip intreg!\n";
				continue;
			}
			cout << "  Numele locatarului cu care se va modifica: ";
			cin >> nume_nou;
			cout << "  Suprafata apartamentului cu care se va modifica: ";
			cin >> aux;
			if (este_double(aux))
				suprafata_noua = std::atof(aux.c_str());
			else {
				cout << "Suprafata apartamentului trebuie sa fie un numar rational!\n";
				continue;
			}
			cout << "  Tipul apartamentului cu care se va modifica: ";
			cin >> tip_nou;
			try {
				srv.modifica(apart_cautat, nume_nou, suprafata_noua, tip_nou);
				cout << " \n			Locatar modificat cu succes!\n";
			}
			catch (ValidError& vle) {
				cout << vle.get_mesaj();
			}
			catch (RepoException& re) {
				cout << re.get_mesaj();
			}
		}
		else if (comanda == 5) {
			int apart_cautat;
			string aux;
			cout << "  Numarul apartamentului cautat: ";
			cin >> aux;
			if (este_int(aux))
				apart_cautat = std::atoi(aux.c_str());
			else {
				cout << "Numarul apartamentului trebuie sa fie de tip intreg!\n";
				continue;
			}
			cout << "Locatarul cautat:\n";
			cout << setw(3) << srv.caut(apart_cautat).get_apart() << setw(8) << srv.caut(apart_cautat).get_nume() << setw(8) << srv.caut(apart_cautat).get_suprafata() << setw(19) << srv.caut(apart_cautat).get_tip() << "\n";
		}
		else if (comanda == 6) {
			cout << "\n\t\t\t~~Meniul de filtrare~~\n";
			while (true) {
				cout << "\t0. Exit meniu filtrare\n";
				cout << "\t1. Filtrare dupa suprafata\n";
				cout << "\t2. Filtrare dupa tipul apartamentului\n";
				string aux;
				int cmd;
				cout << "Indroduceti tipul de filtrare: ";
				cin >> aux;
				if (este_int(aux))
					cmd = std::atoi(aux.c_str());
				else {
					cout << "Comanda trebuie sa fie nr intreg!\n";
					continue;
				}
				if (cmd == 0)
					break;
				else if (cmd == 1) {
					string aux1;
					double suprafata;
					cout << "Suprafata dupa care se va face filtrarea apartamentelor: ";
					cin >> aux1;
					if (este_double(aux1))
						suprafata = std::atof(aux1.c_str());
					else {
						cout << "Suprafata apartamentului trebuie sa fie un numar rational!\n";
						continue;
					}
					vector_dinamic<Locatar> filtrate;
					srv.filtrare_dupa_suprafata(suprafata, filtrate);
					for (const Locatar& loc : filtrate)
						cout << setw(3) << loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() << setw(19) << loc.get_tip() << "\n";
				}
				else if (cmd == 2) {
					string tip;
					cout << "  Tipul apartamentului dupa care se va filtara: ";
					cin >> tip;

					vector_dinamic<Locatar> filtrate;
					srv.filtrare_dupa_tip(tip, filtrate);
					for (const Locatar& loc : filtrate)
						cout << setw(3) << loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() << setw(19) << loc.get_tip() << "\n";
				}
				else
					continue;
			}
		}
		else if (comanda == 7) {
			cout << "\n\t\t\t~~Meniul de sortare~~\n";
			while (true) {
			cout << "\t0. Exit meniu sortare\n";
			cout << "\t1. Sortare dupa nume\n";
			cout << "\t2. Sortare dupa suprafata\n";
			cout << "\t3. Sortare dupa tipul apartamentului + suprafata\n";
			string aux1;
			int cmd;
			cout << "Indroduceti tipul de sortare: ";
			cin >> aux1;
			if (este_int(aux1))
				cmd = std::atoi(aux1.c_str());
			else {
				cout << "Comanda trebuie sa fie nr intreg!\n";
				continue;
			}

			if (cmd == 0)
				break;
			else if (cmd == 1) {
				vector_dinamic<Locatar> sortate;
				srv.sortare_dupa_nume(sortate);
				for (const Locatar& loc : sortate)
					cout << setw(3) << loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() << setw(19) << loc.get_tip() << "\n";
			}
			else if (cmd == 2) {
				vector_dinamic<Locatar> sortate;
				srv.sortare_dupa_suprafata(sortate);
				for (const Locatar& loc : sortate)
					cout << setw(3) << loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() << setw(19) << loc.get_tip() << "\n";
			}
			else if (cmd == 3) {
				vector_dinamic<Locatar> sortate;
				srv.sortare_dupa_tip_si_suprafata(sortate);
				for (const Locatar& loc : sortate)
					cout << setw(3) << loc.get_apart() << setw(8) << loc.get_nume() << setw(8) << loc.get_suprafata() << setw(19) << loc.get_tip() << "\n";
			}
			else
				continue;
			}
		}
	}
}

bool UI :: este_int(string aux) {
	//parcurg stringul caracter cu caracter si verific daca fiecare caracter este cifra
	for (int i = 0; i <(int) aux.length(); i++) 
		if (aux.at(i) < '0' || aux.at(i) > '9')
			return false;
	return true;
}

bool UI::este_double(string aux) {
	//parcurg stringul caracter cu caracter si verific daca poate fi un numar rational
	bool un_punct=false;
	for (int i = 0; i < (int)aux.length(); i++) {	//sirul poate contine numai un punct maxim, asa fiind reprezentate numerele rationale
		if (aux.at(i) == '.' && un_punct == true)	//daca a mai gasit un punct
			return false;
		if (aux.at(i) == '.')
			un_punct = true;
		else if (aux.at(i) < '0' || aux.at(i) > '9')
			return false;
	}
	return true;
}