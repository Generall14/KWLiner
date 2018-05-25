#include "mainwindow.h"
#include <QLayout>
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QFileDialog>
#include <exception>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    Restorable("KWLiner")
{
    InitWidgets();
    LoadConfigs();

    statusBar()->show();
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
    pbar = new QProgressBar();
    pbar->setEnabled(false);
    statusBar()->addWidget(pbar);
    sblab = new QLabel("");
    sblab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    statusBar()->addWidget(sblab);

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

    QVBoxLayout* lowerLayout = new QVBoxLayout();
    lowerLayout->setMargin(2);
    lowerFrame->setLayout(lowerLayout);

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

    // Dane wyjściowe: ======================================================
    lwFiles = new QListWidget();
    connect(lwFiles, SIGNAL(currentRowChanged(int)), this, SLOT(Display(int)));
    lowerLayout->addWidget(lwFiles);
    QGroupBox* wynikFrame = new QGroupBox();
    lowerLayout->addWidget(wynikFrame);
    QVBoxLayout* wynikLayout = new QVBoxLayout();
    wynikLayout->setMargin(2);
    wynikFrame->setLayout(wynikLayout);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    wynikLayout->addLayout(fileLayout);
    lab = new QLabel("Plik:");
    fileLayout->addWidget(lab);
    fileLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leFile = new QLabel("-");
    fileLayout->addWidget(leFile);

    QHBoxLayout* totalLayout = new QHBoxLayout();
    wynikLayout->addLayout(totalLayout);
    lab = new QLabel("Linii razem:");
    totalLayout->addWidget(lab);
    totalLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leTotal = new QLabel("-");
    totalLayout->addWidget(leTotal);

    QHBoxLayout* codeLayout = new QHBoxLayout();
    wynikLayout->addLayout(codeLayout);
    lab = new QLabel("Linii kodu:");
    codeLayout->addWidget(lab);
    codeLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leCode = new QLabel("-");
    codeLayout->addWidget(leCode);

    QHBoxLayout* commLayout = new QHBoxLayout();
    wynikLayout->addLayout(commLayout);
    lab = new QLabel("Linii komentarzy:");
    commLayout->addWidget(lab);
    commLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leComm = new QLabel("-");
    commLayout->addWidget(leComm);

    QHBoxLayout* lightLayout = new QHBoxLayout();
    wynikLayout->addLayout(lightLayout);
    lab = new QLabel("Linii światła:");
    lightLayout->addWidget(lab);
    lightLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leLight = new QLabel("-");
    lightLayout->addWidget(leLight);
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
    leFile->setText("-");
    leTotal->setText("-");
    leCode->setText("-");
    leComm->setText("-");
    leLight->setText("-");
}

void MainWindow::Display(int c)
{
    Clear();
    if(c<0)
        return;
    if(c==0)
        Display(result);
    else
        Display(results[c-1]);
}

void MainWindow::Display(ResFile &fil)
{
    Clear();
    leFile->setText(fil.Name());
    leTotal->setText(QString::number(fil.Total()));
    leCode->setText(QString::number(fil.Code()));
    leComm->setText(QString::number(fil.Comment()));
    leLight->setText(QString::number(fil.Light()));
}

void MainWindow::Run()
{
    Clear();
    lwFiles->clear();

    try
    {
        QStringList temp;
        for(int i=0;i<lwIgnorowane->count();i++)
            temp.append(lwIgnorowane->item(i)->text());
        Core a(cbSet->currentText(), leAdr->text()+"/", temp);
        result = a.GetSum();
        results = a.GetFiles();
        lwFiles->addItem(result.Name());

        temp.clear();
        for(ResFile res: results)
            temp.append(res.Name());
        lwFiles->addItems(temp);
        lwFiles->setCurrentRow(0);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F1)
    {
        QMessageBox::information(this, "About", "Autor: mgr inż. Wojciech Kogut\nBuild on "+QString(__DATE__));
    }
    else
        QMainWindow::keyPressEvent(event);
}

void MainWindow::StatusBarInit()
{
    pbar->setEnabled(true);
    pbar->setValue(0);
    sblab->setText("Szukanie plików...");
}

void MainWindow::StatusBarEnd()
{
    pbar->setEnabled(false);
    sblab->setText("");
}

void MainWindow::StatusBarUpdate(int current, int total)
{
    pbar->setMaximum(total);
    pbar->setValue(current);
    sblab->setText("Przetwarzanie... "+QString::number(current)+" / "+QString::number(total));
}
