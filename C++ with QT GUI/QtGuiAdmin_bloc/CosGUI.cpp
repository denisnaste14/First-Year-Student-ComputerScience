#include "CosGUI.h"


void CosGUI::initGui() {
		QHBoxLayout* cos_main_ly = new QHBoxLayout;
		load_information(lista_notif, cos.toti_din_cos());
		cos_main_ly->addWidget(lista_notif);
		QVBoxLayout* butoane = new QVBoxLayout;
		butoane->addWidget(add);
		butoane->addWidget(goleste);
		butoane->addWidget(add_random);
		butoane->addWidget(undo_cos);
		butoane->addWidget(desenare_obiecte);
		cos_main_ly->addLayout(butoane);
		QFormLayout* campuri = new QFormLayout;
		campuri->setSpacing(50);

		campuri->addRow("Numarul apart. de adaugat: ", apart);
		campuri->addRow("Numarul de apart. de adaugat random: ", rand_nr);
		cos_main_ly->addLayout(campuri);
		//campuri->setSpacing(30);
		setLayout(cos_main_ly);
		show();
}

void CosGUI::connections() {
	QObject::connect(add, &QPushButton::clicked, [&]() {
		auto txt = apart->text();
		string aux = txt.toStdString();
		int apartament;
		if (!este_int(aux))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			apartament = atoi(aux.c_str());
		try {
			cos.adauga_in_cos(apartament);
			apart->clear();
		}
		catch (ValidError& ve) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ve.get_mesaj()));
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		load_information(lista_notif, cos.toti_din_cos());
	});

	QObject::connect(goleste, &QPushButton::clicked, [&]() {
		cos.goleste_cos();
		load_information(lista_notif, cos.toti_din_cos());
	});

	QObject::connect(add_random, &QPushButton::clicked, [&]() {
		auto txt = rand_nr->text();
		string aux = txt.toStdString();
		int ran;
		if (!este_int(aux))
			QMessageBox::information(nullptr, "Eror", "Numarul apartamentului trebuie sa fie de tip intreg!");
		else
			ran = atoi(aux.c_str());

		try {
			cos.add_random(ran);
			rand_nr->clear();
		}
		catch (RepoException& re) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(re.get_mesaj()));
		}
		load_information(lista_notif, cos.toti_din_cos());
	});
	QObject::connect(undo_cos, &QPushButton::clicked, [&]() {
		try {
			cos.undo();
		}
		catch (UndoException& ue) {
			QMessageBox::information(nullptr, "Exception", QString::fromStdString(ue.get_mesaj()));
		}
		load_information(lista_notif, cos.toti_din_cos());
	});

	QObject::connect(desenare_obiecte, &QPushButton::clicked, [&]() {
		CosRDOnlyGUI* cos_desenare;
		cos_desenare = new CosRDOnlyGUI{ cos };
		cos_desenare->show();
	});
}

bool CosGUI::este_int(string aux) {
	//parcurg stringul caracter cu caracter si verific daca fiecare caracter este cifra
	for (int i = 0; i < (int)aux.length(); i++)
		if (aux.at(i) < '0' || aux.at(i) > '9')
			return false;
	return true;
}

bool CosGUI::este_double(string aux) {
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

void CosGUI::load_information(QListWidget* list_aux, vector<Locatar> aux) {
	list_aux->clear();
	if (aux.empty())
		list_aux->setStyleSheet("QListWidget{background: pink;}");
	for (auto const& elem : aux) {
		string aux = "";
		aux = std::to_string(elem.get_apart()) + " " + elem.get_nume() + " " + std::to_string(elem.get_suprafata()) + " " + elem.get_tip();
		list_aux->addItem(QString::fromStdString(aux));
	}
}