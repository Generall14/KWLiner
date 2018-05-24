#include "mainwindow.h"
#include "src/core.hpp"
#include <QLayout>
#include <QFrame>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    Restorable("KWLiner")
{
    InitWidgets();
    LoadConfigs();

    Core a("MSP430 asm", "./test_cpp/");
    a.GetSum();
}

MainWindow::~MainWindow()
{
    Store("fd", "ff");
}

void MainWindow::LoadConfigs()
{

}

void MainWindow::InitWidgets()
{
    QWidget* wd = new QWidget();
    this->setCentralWidget(wd);

    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->setMargin(2);
    wd->setLayout(centralLayout);

    QGroupBox* upperFrame = new QGroupBox("Dane wejściowe");
    centralLayout->addWidget(upperFrame);
    QGroupBox* lowerFrame = new QGroupBox("Wyniki");
    centralLayout->addWidget(lowerFrame);

    QHBoxLayout* upperLayout = new QHBoxLayout();
    upperLayout->setMargin(2);
    upperFrame->setLayout(upperLayout);

    //Dane wejściowe:
    QGroupBox* ignoreFrame = new QGroupBox("Ignorowane");
    upperLayout->addWidget(ignoreFrame);
}
