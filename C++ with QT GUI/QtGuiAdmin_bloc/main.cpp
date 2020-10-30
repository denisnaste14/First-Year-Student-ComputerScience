#include "QtGuiAdmin_bloc.h"
#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileRepo repo{ "loc.txt",0 };
	Repo cos;
	Service srv{ repo,cos };
	GUI gui{srv};
	gui.show();
	return a.exec();
}
