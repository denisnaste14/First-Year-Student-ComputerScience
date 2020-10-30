#include "GUI.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

using std::vector;
using std::string;
using std::to_string;

void GUI::initializare_iterfata() {
	
	setLayout(lymain);
	QFont* font = new QFont;
	font->setWeight(46);
	font->setBold(true);
	font->setWordSpacing(13);
	list->setFont(*font);
	lymain->addWidget(list);
	lymain->addSpacing(6);

	QVBoxLayout* ly_mijloc = new QVBoxLayout;

	QFormLayout* fly = new QFormLayout;
	fly->addRow("Numar apart:", line_apart);
	fly->addRow("Nume:", line_nume);
	fly->addRow("Suprafata:", line_suprafata);
	fly->addRow("Tip:", line_tip);
	ly_mijloc->addLayout(fly);

	QHBoxLayout* ly_as = new QHBoxLayout;
	ly_as->addWidget(adauga);
	ly_as->addWidget(sterge);
	ly_mijloc->addLayout(ly_as);

	QHBoxLayout* ly_mc = new QHBoxLayout;
	ly_mc->addWidget(modifica);
	ly_mc->addWidget(cauta);
	ly_mijloc->addLayout(ly_mc);

	QVBoxLayout* ly_final = new QVBoxLayout;
	ly_final->addWidget(filtrare);
	ly_final->addWidget(sortare);
	ly_final->addWidget(lista_notificare);
	ly_final->addWidget(statistica);
	ly_final->addWidget(undo);
	ly_final->addWidget(help_add);
	ly_final->addWidget(help_sterge);

	lymain->addSpacing(5);
	lymain->addLayout(ly_mijloc);
	lymain->addSpacing(5);
	lymain->addLayout(ly_final);
}

void GUI::load_information(QListWidget* list_aux,vector<Locatar> aux) {
	list_aux->clear();
	for (auto const& elem : aux) {
		string aux=""; 
		aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
		list_aux->addItem(QString::fromStdString(aux));
	}
}

void GUI::conectivitate_adauga() {
	QObject::connect(adauga, &QPushButton::clicked, [&]() {
		auto nr_apart = line_apart->text();
		auto n = line_nume->text();
		auto supr = line_suprafata->text();
		auto tipp = line_tip->text();
		int apart;
		double suprafata;
		if (!este_int(nr_apart.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			apart = atoi(nr_apart.toStdString().c_str());
		string nume = n.toStdString();

		if (!este_double(supr.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Suprafata apartamentului trebuie sa fie de tip double!");
		else
			suprafata = atof(supr.toStdString().c_str());

		string tip = tipp.toStdString();

		try {
			srv.add(apart, nume, suprafata, tip);
			line_apart->clear();
			line_nume->clear();
			line_suprafata->clear();
			line_tip->clear();
		}
		catch (ValidError& ve) {
			QMessageBox::information(nullptr, "Exception",QString::fromStdString(ve.get_mesaj()));
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		sterge_lista_butoane();
		load_information(list,srv.get_all());
		list_of_buttons(srv.get_all());
	});
	
}

void GUI::conectivitate_sterge() {
	QObject::connect(sterge, &QPushButton::clicked, [&]() {
		auto nr_apart = line_apart->text();
		int apart;
		if (!este_int(nr_apart.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			apart = atoi(nr_apart.toStdString().c_str());
	
		try {
			srv.sterge(apart);
			line_apart->clear();
		}
		catch (ValidError& ve) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ve.get_mesaj()));
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		sterge_lista_butoane();
		load_information(list,srv.get_all());
		list_of_buttons(srv.get_all());
	});

}

void GUI::conectivitate_modifica() {
	QObject::connect(modifica, &QPushButton::clicked, [&]() {
		auto nr_apart = line_apart->text();
		auto n = line_nume->text();
		auto supr = line_suprafata->text();
		auto tipp = line_tip->text();
		int apart;
		double suprafata;
		if (!este_int(nr_apart.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			apart = atoi(nr_apart.toStdString().c_str());
		string nume = n.toStdString();

		if (!este_double(supr.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Suprafata apartamentului trebuie sa fie de tip double!");
		else
			suprafata = atof(supr.toStdString().c_str());

		string tip = tipp.toStdString();

		try {
			srv.modifica(apart, nume, suprafata, tip);
			line_apart->clear();
			line_nume->clear();
			line_suprafata->clear();
			line_tip->clear();
		}
		catch (ValidError& ve) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ve.get_mesaj()));
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		load_information(list,srv.get_all());
		});
}

void GUI::conectivitate_cauta() {
	QObject::connect(cauta, &QPushButton::clicked, [&]() {
		auto nr_apart = line_apart->text();
		int apart;
		if (!este_int(nr_apart.toStdString()))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			apart = atoi(nr_apart.toStdString().c_str());


		try {
			auto loc_gasit=srv.caut(apart);
			string solutie="";
			solutie= std::to_string(loc_gasit.get_apart()) + "  " + loc_gasit.get_nume() + "  " + std::to_string(loc_gasit.get_suprafata()) + "  " + loc_gasit.get_tip();
			QMessageBox::information(nullptr, "Locatarul Gasit", QString::fromStdString(solutie));
			line_apart->clear();
		}
		catch (ValidError& ve) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ve.get_mesaj()));
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		load_information(list,srv.get_all());
		});
}

void GUI::conectivitate_filtrare() {
	QObject::connect(filtrare, &QPushButton::clicked, [&]() {
		QVBoxLayout* filt_ly = new QVBoxLayout;
		filt_ly->addWidget(filtr_supraf);
		filt_ly->addWidget(filtr_tip);
		QFormLayout* supraf_tip = new QFormLayout;
		supraf_tip->addRow("Suprafata: ", l1);
		supraf_tip->addRow("Tip: ", l2);
		filt_ly->addLayout(supraf_tip);
		filt_ly->addWidget(lst);
		menu_filtr->setLayout(filt_ly);
		menu_filtr->show();

		QObject::connect(filtr_supraf, &QPushButton::clicked, [&]() { 
			auto supr = l1->text();
			double suprafata;
			if (!este_double(supr.toStdString()))
				QMessageBox::information(nullptr, "Eror", "Suprafata apartamentului trebuie sa fie de tip double!");
			else
				suprafata = atof(supr.toStdString().c_str());
			auto locatari = srv.filtrare_dupa_suprafata(suprafata);
			lst->clear();
			for (auto elem : locatari) {
				string aux = "";
				aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
				lst->addItem(QString::fromStdString(aux));
			}
			l1->clear();
		});
		QObject::connect(filtr_tip, &QPushButton::clicked, [&]() {
			auto tipp = l2->text();
			string tip = tipp.toStdString();
			auto locatari = srv.filtrare_dupa_tip(tip);
			lst->clear();
			for (auto elem : locatari) {
				string aux = "";
				aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
				lst->addItem(QString::fromStdString(aux));
			}
			l2->clear();
		});
	});
}

void GUI::conectivitate_sortare() {
	QObject::connect(sortare, &QPushButton::clicked, [&]() {
		QGridLayout* sort_ly = new QGridLayout;
		sort_ly->addWidget(soratare_nume);
		sort_ly->addWidget(sortare_suprafata);
		sort_ly->addWidget(sortare_tip_supraf);
		menu_sort->setWindowTitle("Meniu Sortare");
		menu_sort->setLayout(sort_ly);
		menu_sort->show();

		QObject::connect(soratare_nume, &QPushButton::clicked, [&]() {
			menu_sort->hide();
			list->clear();
			sterge_lista_butoane();
			vector<Locatar> de_incarcat = srv.sortare_dupa_nume();
			for (auto const& elem : de_incarcat) {
				string aux = "";
				aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
				list->addItem(QString::fromStdString(aux));
			}
			list_of_buttons(de_incarcat);
		});
		QObject::connect(sortare_suprafata, &QPushButton::clicked, [&]() {
			menu_sort->hide();
			list->clear();
			sterge_lista_butoane();
			vector<Locatar> de_incarcat = srv.sortare_dupa_suprafata();
			for (auto const& elem : de_incarcat) {
				string aux = "";
				aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
				list->addItem(QString::fromStdString(aux));
			}
			list_of_buttons(de_incarcat);
		});
		QObject::connect(sortare_tip_supraf, &QPushButton::clicked, [&]() {
			menu_sort->hide();
			list->clear();
			sterge_lista_butoane();
			vector<Locatar> de_incarcat = srv.sortare_dupa_tip_si_suprafata();
			for (auto const& elem : de_incarcat) {
				string aux = "";
				aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
				list->addItem(QString::fromStdString(aux));
			}
			list_of_buttons(de_incarcat);
		});
	});
}

void GUI::conectivitate_statistica() {
	QObject::connect(statistica, &QPushButton::clicked, [&]() {
		auto stat = srv.statistica();
		string aux="";
		for (auto st : stat) {
			aux += st.get_solutie() + "\n";
		}
		QMessageBox::information(nullptr, "Statistica", QString::fromStdString(aux));
	});
}

void GUI::conectivitate_undo() {
	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
		}
		catch (UndoException& ue) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ue.get_mesaj()));
		}
		sterge_lista_butoane();
		load_information(list,srv.get_all());
		list_of_buttons(srv.get_all());
	});
}

void GUI::conectivitate_selectedListItem() {

	QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
		auto selection = list->selectedItems();
		if (selection.isEmpty()) {
			line_apart->setText("");
			line_nume->setText("");
			line_suprafata->setText("");
			line_tip->setText("");
		}
		else{
			auto doar_o_selectie = selection.at(0); // deoarece selected items returneaza o lista de items 
			QStringList separat = doar_o_selectie->text().split(" ");
			auto p1 = separat.at(0);
			line_apart->setText(p1);
			line_nume->setText(separat.at(1));
			line_suprafata->setText(separat.at(2));
			line_tip->setText(separat.at(3));
		}
	});
}

void GUI::conectivitate_cos() {
	QObject::connect(lista_notificare, &QPushButton::clicked, [&]() {
		CosGUI* cos_gui;
		cos_gui = new CosGUI{ cos };
		cos_gui->show();
	});

}

void GUI::conectivitate_help() {
	QObject::connect(help_add, &QRadioButton::clicked, [&]() {
		QMessageBox::information(nullptr, "INFO", "La adaugarea unui nou locatar, acesta trebuie sa aiba numarul apartamentului de tip intreg, numele nevid, suprafata mai mare sau egala cu 1 m^2 si tipul unul tinre urmatoarele: decomandat, semidecomandat, nedecomandat, circular sau open-space!");
	});
	QObject::connect(help_sterge, &QRadioButton::clicked, [&]() {
		QMessageBox::information(nullptr, "INFO", "La stergerea unui locatar numarul apartamentului trebuie sa fie de tip intreg si si locatarul identificat ulterior cu acel numar de apartament sa existe in lista cu locatari!");
	});
}

void GUI::conectivitate() {
	conectivitate_adauga();
	conectivitate_sterge();
	conectivitate_modifica();
	conectivitate_cauta();
	conectivitate_filtrare();
	conectivitate_sortare();
	conectivitate_statistica();
	conectivitate_undo();
	conectivitate_selectedListItem();
	conectivitate_cos();
	conectivitate_help();
}

void GUI::list_of_buttons(vector<Locatar> aux) {

	for (auto loc : aux){
		auto b = new QPushButton{ QString::fromStdString(to_string(loc.get_apart())) };
		b->setObjectName(QString::fromStdString(to_string(loc.get_apart())));
		btn_dreapta.push_back(b);
		btn_dyn_ly->addWidget(b);
		QObject::connect(b, &QPushButton::clicked, [this,b]() {
			auto n = b->objectName();
			auto nume = n.toStdString();
			//caut butonul care trebuie sters
			int index;
			for(int i=0;i<btn_dreapta.size();i++)
				if (btn_dreapta.at(i) == b) {
					index = i;
				}
			for (int i = index; i < btn_dreapta.size() - 1; i++) {
				btn_dreapta.at(i) = btn_dreapta.at(i - 1);
			}
			btn_dreapta.pop_back();
			srv.sterge(atoi(nume.c_str()));
			load_information(list, srv.get_all());
			delete b;
		});
	}
	btn_dyn->setLayout(btn_dyn_ly);
	lymain->addWidget(btn_dyn);
}

void GUI::sterge_lista_butoane() {
	for (auto b : btn_dreapta)
		delete b;
	btn_dreapta.clear();
}

bool GUI::este_int(string aux) {
	//parcurg stringul caracter cu caracter si verific daca fiecare caracter este cifra
	for (int i = 0; i < (int)aux.length(); i++)
		if (aux.at(i) < '0' || aux.at(i) > '9')
			return false;
	return true;
}

bool GUI::este_double(string aux) {
	//parcurg stringul caracter cu caracter si verific daca poate fi un numar rational
	bool un_punct = false;
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
