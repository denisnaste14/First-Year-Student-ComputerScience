#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include "Observer.h"
#include "Cos.h"
#include "CosRDOnlyGUI.h"

class CosGUI : public QWidget, public Observer {
private:
	QListWidget* lista_notif = new QListWidget;
	QPushButton* add = new QPushButton{ "Adauga din lista principala" };
	QPushButton* goleste = new QPushButton{ "&Goleste lista" };
	QPushButton* undo_cos = new QPushButton{ "&Undo" };
	QPushButton* add_random = new QPushButton{ "&Adauga random din lista principala" };
	QPushButton* desenare_obiecte = new QPushButton{ "&Desenarea obiectelor" };
	QLineEdit* apart = new QLineEdit;
	QLineEdit* rand_nr = new QLineEdit;

	Cos& cos;
	void initGui();
	void load_information(QListWidget* list_aux, vector<Locatar> aux);
	void connections();
	//ajutatoare
	bool este_int(string aux);
	bool este_double(string aux);
public:
	CosGUI(Cos& cos) : cos{ cos } {
		initGui();
		cos.addObserver(this);
		connections();
		load_information(lista_notif, cos.toti_din_cos());
	}

	void update() override {
		load_information(lista_notif, cos.toti_din_cos());
	}
	
	~CosGUI() {
		cos.removeObserver(this);
	}

};