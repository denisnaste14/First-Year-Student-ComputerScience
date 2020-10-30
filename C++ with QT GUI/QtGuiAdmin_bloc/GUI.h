#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlayout>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include <qpalette.h>
#include <qbrush.h>
#include "Service.h"
#include "CosGUI.h"


class GUI : public QWidget {
public:
	GUI(Service& srv) : srv{srv} {
		initializare_iterfata();
		load_information(list,srv.get_all());
		conectivitate();
		list_of_buttons(srv.get_all());
	};
private:
	Service& srv;
	Cos cos{ srv };
	QListWidget* list = new QListWidget;
	//
	QHBoxLayout* lymain = new QHBoxLayout;
	QLineEdit* line_apart = new QLineEdit;
	QLineEdit* line_nume = new QLineEdit;
	QLineEdit* line_suprafata = new QLineEdit;
	QLineEdit* line_tip = new QLineEdit;
	//
	QPushButton* adauga = new QPushButton{"&Adauga"};
	QPushButton* sterge = new QPushButton{"&Sterge"};
	QPushButton* modifica = new QPushButton{ "&Modifica" };
	QPushButton* cauta = new QPushButton{ "&Cauta" };
	QPushButton* filtrare = new QPushButton{ "&Meniu filtrare" };
	QPushButton* sortare = new QPushButton{ "&Meniu sortare" };
	QPushButton* lista_notificare = new QPushButton{"&Lista de notificare"};
	QPushButton* statistica = new QPushButton{"&Statistica"};
	QPushButton* undo = new QPushButton{ "&Undo" };
	//
	QRadioButton* help_add = new QRadioButton{ "&Info adauga!" };
	QRadioButton* help_sterge = new QRadioButton{ "&Info sterge!" };
	//filtrare
	QPushButton* filtr_supraf = new QPushButton{ "&Filtrare dupa suprafata" };
	QPushButton* filtr_tip = new QPushButton{ "&Filtrare dupa tip" };
	QLineEdit* l1 = new QLineEdit;
	QLineEdit* l2 = new QLineEdit;
	QListWidget* lst = new QListWidget;
	QWidget* menu_filtr = new QWidget;
	//sortare
	QWidget* menu_sort = new QWidget;
	QPushButton* soratare_nume = new QPushButton{ "&Sortare dupa nume" };
	QPushButton* sortare_suprafata = new QPushButton{ "&Sortare dupa suprafata" };
	QPushButton* sortare_tip_supraf = new QPushButton{ "&Sortare dupa tip si supraf" };
	//
	QGridLayout* grid_ly = new QGridLayout;
	//lista butoane
	QVBoxLayout* btn_dyn_ly = new QVBoxLayout;
	QWidget* btn_dyn = new QWidget;

	vector<QPushButton*> btn_dreapta;

	void initializare_iterfata();
	void load_information(QListWidget* list_aux,vector<Locatar> aux);
	void conectivitate();
	void conectivitate_adauga();
	void conectivitate_sterge();
	void conectivitate_modifica();
	void conectivitate_cauta();
	void conectivitate_filtrare();
	void conectivitate_sortare();
	void conectivitate_statistica();
	void conectivitate_undo();
	void conectivitate_selectedListItem();
	void conectivitate_cos();
	void conectivitate_help();

	bool este_int(string aux);
	bool este_double(string aux);

	void list_of_buttons(vector<Locatar> aux);
	void sterge_lista_butoane();
};