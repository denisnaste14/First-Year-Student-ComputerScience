/********************************************************************************
** Form generated from reading UI file 'QtGuiAdmin_bloc.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIADMIN_BLOC_H
#define UI_QTGUIADMIN_BLOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiAdmin_blocClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiAdmin_blocClass)
    {
        if (QtGuiAdmin_blocClass->objectName().isEmpty())
            QtGuiAdmin_blocClass->setObjectName(QString::fromUtf8("QtGuiAdmin_blocClass"));
        QtGuiAdmin_blocClass->resize(600, 400);
        menuBar = new QMenuBar(QtGuiAdmin_blocClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtGuiAdmin_blocClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiAdmin_blocClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtGuiAdmin_blocClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtGuiAdmin_blocClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtGuiAdmin_blocClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGuiAdmin_blocClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGuiAdmin_blocClass->setStatusBar(statusBar);

        retranslateUi(QtGuiAdmin_blocClass);

        QMetaObject::connectSlotsByName(QtGuiAdmin_blocClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiAdmin_blocClass)
    {
        QtGuiAdmin_blocClass->setWindowTitle(QCoreApplication::translate("QtGuiAdmin_blocClass", "QtGuiAdmin_bloc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiAdmin_blocClass: public Ui_QtGuiAdmin_blocClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIADMIN_BLOC_H
