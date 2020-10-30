#pragma once
#include <QtWidgets/qwidget.h>
#include <qpainter.h>
#include "Observer.h"
#include "Cos.h"
class CosRDOnlyGUI: public QWidget, public Observer{
private:
	Cos& cos;
	void paintEvent(QPaintEvent* ev) override;
	void update() override;
public:
	CosRDOnlyGUI(Cos& cos) : cos{ cos } {
		cos.addObserver(this);
	};
	~CosRDOnlyGUI() {
		cos.removeObserver(this);
	}
};