#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiAdmin_bloc.h"

class QtGuiAdmin_bloc : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiAdmin_bloc(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiAdmin_blocClass ui;
};
