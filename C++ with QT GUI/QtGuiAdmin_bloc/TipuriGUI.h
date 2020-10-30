#pragma once
#include "Observer.h"
#include "Tipuri.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>

class TipuriGUI: public Observer, public QWidget {
private:
	QLabel* circular = new QLabel{ "Circular: " };
	QLabel* decomandat = new QLabel{"Decomandat: "};
	QLabel* semidecomandat = new QLabel{ "Semidecomandat: " };
	QLabel* nedecomandat = new QLabel{ "nedecomandat" };
	QLabel* open_space = new QLabel{ "open-space" };
	Tipuri& tipuri;
public:
	void incercare();
};