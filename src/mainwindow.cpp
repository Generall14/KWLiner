#include "mainwindow.h"
#include "src/core.hpp"
#include <QLayout>
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>

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
    Store("cbSet", cbSet->currentText());
    Store("leAdr", leAdr->text());
    QStringList temp;
    for(int i=0;i<lwIgnorowane->count();i++)
        temp.append(lwIgnorowane->itemAt(i, 0)->text());
    Store("lwIgnorowane", temp);
}

void MainWindow::LoadConfigs()
{
    cbSet->setCurrentText(RestoreAsString("cbSet", Set::GetSetsList().at(0)));
    leAdr->setText(RestoreAsString("leAdr", "./"));
    lwIgnorowane->clear();
    lwIgnorowane->addItems(RestoreAsQStringList("lwIgnorowane", QStringList()));
}

void MainWindow::InitWidgets()
{
    QWidget* wd = new QWidget();
    this->setCentralWidget(wd);

    QHBoxLayout* centralLayout = new QHBoxLayout();
    centralLayout->setMargin(2);
    wd->setLayout(centralLayout);

    QGroupBox* upperFrame = new QGroupBox("Dane wejściowe");
    centralLayout->addWidget(upperFrame);
    QGroupBox* lowerFrame = new QGroupBox("Wyniki");
    centralLayout->addWidget(lowerFrame);

    QVBoxLayout* upperLayout = new QVBoxLayout();
    upperLayout->setMargin(2);
    upperFrame->setLayout(upperLayout);

    // Dane wejściowe: ======================================================
    // ignorowane
    QGroupBox* ignoreFrame = new QGroupBox("Ignorowane");
    upperLayout->addWidget(ignoreFrame);
    QVBoxLayout* ignoreLayout = new QVBoxLayout();
    ignoreLayout->setMargin(2);
    ignoreFrame->setLayout(ignoreLayout);
    lwIgnorowane = new QListWidget();
    ignoreLayout->addWidget(lwIgnorowane);
    QHBoxLayout* ignModLayout = new QHBoxLayout();
    ignModLayout->setMargin(2);
    ignoreLayout->addLayout(ignModLayout);
    QPushButton* btn = new QPushButton("Dodaj");
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Usuń");
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Edytuj");
    ignModLayout->addWidget(btn);

    // prawa
    QVBoxLayout* rLayout = new QVBoxLayout();
    rLayout->setMargin(2);
    upperLayout->addLayout(rLayout);

    // adr
    QGroupBox* adrFrame = new QGroupBox("Adres katalogu");
    rLayout->addWidget(adrFrame);
    QHBoxLayout* adrLayout = new QHBoxLayout();
    adrLayout->setMargin(2);
    adrFrame->setLayout(adrLayout);
    leAdr = new QLineEdit();
    leAdr->setReadOnly(true);
    adrLayout->addWidget(leAdr);
    btn = new QPushButton("Zmień");
    adrLayout->addWidget(btn);

    // typ
    QGroupBox* othFrame = new QGroupBox();
    rLayout->addWidget(othFrame);
    QHBoxLayout* typLayout = new QHBoxLayout();
    typLayout->setMargin(2);
    othFrame->setLayout(typLayout);
    QLabel* lab = new QLabel("Typ projektu:");
    typLayout->addWidget(lab);
    cbSet = new QComboBox();
    cbSet->addItems(Set::GetSetsList());
    typLayout->addWidget(cbSet);
    btn = new QPushButton("ODPAL!");
    typLayout->addWidget(btn);
}
