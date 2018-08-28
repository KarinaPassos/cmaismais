#include "mainwindow.h"
#include <QTabWidget>
#include <QLabel>
#include <projeto1.h>
#include <projeto2.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setGeometry(300, 300, 500, 500);
    tab = new QTabWidget();
    setCentralWidget(tab);
    tab->addTab(new projeto1(),"Primeiro trabalho");
    tab->addTab(new projeto2(),"Segundo trabalho");
    tab->addTab(new QLabel("terceiro widget"),"terceiro titulo");
}

MainWindow::~MainWindow()
{
}
