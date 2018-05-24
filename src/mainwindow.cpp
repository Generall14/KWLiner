#include "mainwindow.h"
#include <QLayout>
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QDebug>
#include <QListWidgetItem>
#include <QFileDialog>
#include <exception>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    Restorable("KWLiner")
{
    InitWidgets();
    LoadConfigs();
}

MainWindow::~MainWindow()
{
    Store("cbSet", cbSet->currentText());
    Store("leAdr", leAdr->text());
    QStringList temp;
    for(int i=0;i<lwIgnorowane->count();i++)
        temp.append(lwIgnorowane->item(i)->text());
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
    connect(lwIgnorowane, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ModifyIgnored()));
    ignoreLayout->addWidget(lwIgnorowane);
    QHBoxLayout* ignModLayout = new QHBoxLayout();
    ignModLayout->setMargin(2);
    ignoreLayout->addLayout(ignModLayout);
    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(AddIgnored()));
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(RemoveIgnored()));
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Edytuj");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ModifyIgnored()));
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
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(GetAdr()));
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
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Run()));
    typLayout->addWidget(btn);
}

void MainWindow::AddIgnored()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Get", "Ignorowane wyrażenie", QLineEdit::Normal, "", &ok);
    if(ok && !text.isEmpty())
        lwIgnorowane->addItem(text);
}

void MainWindow::ModifyIgnored()
{
    QListWidgetItem* it = lwIgnorowane->currentItem();
    if(it==nullptr)
        return;
    bool ok;
    QString text = QInputDialog::getText(this, "Get", "Ignorowane wyrażenie", QLineEdit::Normal, it->text(), &ok);
    if(ok && !text.isEmpty())
        it->setText(text);
}

void MainWindow::RemoveIgnored()
{
    lwIgnorowane->takeItem(lwIgnorowane->currentRow());
}

void MainWindow::Clear()
{
    //<TODO>
}

void MainWindow::Display(Core &core)
{
    //<TODO>
}

void MainWindow::Run()
{
    Clear();

    try
    {
        QStringList temp;
        for(int i=0;i<lwIgnorowane->count();i++)
            temp.append(lwIgnorowane->item(i)->text());
        Core a(cbSet->currentText(), leAdr->text()+"/", temp);
        a.GetSum();
    }
    catch(std::runtime_error exc)
    {
        QMessageBox::information(this, "runtime_error", QString(exc.what()));
    }


}

void MainWindow::GetAdr()
{
    QString init;
    if(leAdr->text().isEmpty())
        init = "./";
    else
        init = leAdr->text();
    QString directory = QFileDialog::getExistingDirectory(this, "Podaj katalog z projektem", init);
    if(!directory.isEmpty())
        leAdr->setText(directory);
}
