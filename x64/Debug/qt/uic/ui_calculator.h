/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calculatorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *calculatorClass)
    {
        if (calculatorClass->objectName().isEmpty())
            calculatorClass->setObjectName(QStringLiteral("calculatorClass"));
        calculatorClass->resize(600, 400);
        menuBar = new QMenuBar(calculatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        calculatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(calculatorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        calculatorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(calculatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        calculatorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(calculatorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        calculatorClass->setStatusBar(statusBar);

        retranslateUi(calculatorClass);

        QMetaObject::connectSlotsByName(calculatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *calculatorClass)
    {
        calculatorClass->setWindowTitle(QApplication::translate("calculatorClass", "calculator", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class calculatorClass: public Ui_calculatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
