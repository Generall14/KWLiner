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
#include <algorithm>

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
    lwIgnorowane->setToolTip("Pliki i katalogi zawierające dowolny z podanych tu tekstów \n"
                             "zostaną zignorowane. Porównywanie tekstów odbywa się z \n"
                             "ignorowaniem wielkości znaku.");
    connect(lwIgnorowane, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ModifyIgnored()));
    ignoreLayout->addWidget(lwIgnorowane);
    QHBoxLayout* ignModLayout = new QHBoxLayout();
    ignModLayout->setMargin(2);
    ignoreLayout->addLayout(ignModLayout);
    QPushButton* btn = new QPushButton("Dodaj");
    btn->setToolTip("Dodaj element do listy ignorowanych.");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(AddIgnored()));
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Usuń");
    btn->setToolTip("Usuń element z listy ignorowanych.");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(RemoveIgnored()));
    ignModLayout->addWidget(btn);
    btn = new QPushButton("Edytuj");
    btn->setToolTip("Zmień zaznaczony element na liście ignorowawnych.");
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
    leAdr->setToolTip("Adres katalogu ze źródłami, pliki będą wyszukiwane \n"
                      "w podanym katalogu oraz wszystkich jego podkatalogach.");
    leAdr->setReadOnly(true);
    adrLayout->addWidget(leAdr);
    btn = new QPushButton("Zmień");
    btn->setToolTip("Zmień adres katalogu ze śródłami.");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(GetAdr()));
    adrLayout->addWidget(btn);

    // typ
    QGroupBox* othFrame = new QGroupBox();
    rLayout->addWidget(othFrame);
    QHBoxLayout* typLayout = new QHBoxLayout();
    typLayout->setMargin(2);
    othFrame->setLayout(typLayout);
    QString typToolTip = "Typ źródeł, określa rozszerzenie plików jakie zostaną \n"
                         "zbadane oraz zasady rozdzielania komentarzy od kodu właściwego.";
    QLabel* lab = new QLabel("Typ projektu:");
    lab->setToolTip(typToolTip);
    typLayout->addWidget(lab);
    cbSet = new QComboBox();
    cbSet->setToolTip(typToolTip);
    cbSet->addItems(Set::GetSetsList());
    typLayout->addWidget(cbSet);
    btn = new QPushButton("ODPAL!");
    btn->setToolTip("Rozpocznik przetwarzania z podanymi parametrami.");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Run()));
    typLayout->addWidget(btn);

    // Dane wyjściowe: ======================================================
    QHBoxLayout* totalFilesLayout = new QHBoxLayout();
    lowerLayout->addLayout(totalFilesLayout);
    QString pasujaceToolTip = "Liczba znalezionych plików w podanym katalogu z\n"
                              "odpowiednim rozszerzeniem.";
    lab = new QLabel("Pasujące pliki:");
    lab->setToolTip(pasujaceToolTip);
    totalFilesLayout->addWidget(lab);
    totalFilesLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leTotalFiles = new QLabel("-");
    leTotalFiles->setToolTip(pasujaceToolTip);
    totalFilesLayout->addWidget(leTotalFiles);

    lwFiles = new QListWidget();
    lwFiles->setToolTip("Lista odczytanych plików. Posegregowana według ilości\n"
                        "lini kodu (zaczynając od największych wartości). Pierwszy\n"
                        "element zawiera sumę wszystkich plików.");
    connect(lwFiles, SIGNAL(currentRowChanged(int)), this, SLOT(Display(int)));
    lowerLayout->addWidget(lwFiles);
    QGroupBox* wynikFrame = new QGroupBox();
    lowerLayout->addWidget(wynikFrame);
    QVBoxLayout* wynikLayout = new QVBoxLayout();
    wynikLayout->setMargin(2);
    wynikFrame->setLayout(wynikLayout);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    wynikLayout->addLayout(fileLayout);
    QString plikToolTiop = "Nazwa pliku.";
    lab = new QLabel("Plik:");
    lab->setToolTip(plikToolTiop);
    fileLayout->addWidget(lab);
    fileLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leFile = new QLabel("-");
    leFile->setToolTip(plikToolTiop);
    fileLayout->addWidget(leFile);

    QHBoxLayout* totalLayout = new QHBoxLayout();
    wynikLayout->addLayout(totalLayout);
    QString razemToolTip = "Całkowita liczba lini tekstu w pliku.";
    lab = new QLabel("Linii razem:");
    lab->setToolTip(razemToolTip);
    totalLayout->addWidget(lab);
    totalLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leTotal = new QLabel("-");
    leTotal->setToolTip(razemToolTip);
    totalLayout->addWidget(leTotal);

    QHBoxLayout* codeLayout = new QHBoxLayout();
    wynikLayout->addLayout(codeLayout);
    QString kodToolTip = "Liczba lini kodu które zawierały jakiś tekst \n"
                         "(pomijając spacje i tabulatory) niebędący\n"
                         "komentarzem";
    lab = new QLabel("Linii kodu:");
    lab->setToolTip(kodToolTip);
    codeLayout->addWidget(lab);
    codeLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leCode = new QLabel("-");
    leCode->setToolTip(kodToolTip);
    codeLayout->addWidget(leCode);

    QHBoxLayout* commLayout = new QHBoxLayout();
    wynikLayout->addLayout(commLayout);
    QString commToolTip = "Liczba lini które zawierały sam komentarz\n"
                          "(pomijając spacje i tabulatory).";
    lab = new QLabel("Linii komentarzy:");
    lab->setToolTip(commToolTip);
    commLayout->addWidget(lab);
    commLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leComm = new QLabel("-");
    leComm->setToolTip(commToolTip);
    commLayout->addWidget(leComm);

    QHBoxLayout* lightLayout = new QHBoxLayout();
    wynikLayout->addLayout(lightLayout);
    QString lightToolTip = "Liczba lini które były puste lub zawierały\n"
                           "same znki białe.";
    lab = new QLabel("Linii światła:");
    lab->setToolTip(lightToolTip);
    lightLayout->addWidget(lab);
    lightLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leLight = new QLabel("-");
    leLight->setToolTip(lightToolTip);
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

    Core* core = nullptr;
    try
    {
        QStringList temp;
        for(int i=0;i<lwIgnorowane->count();i++)
            temp.append(lwIgnorowane->item(i)->text());

        StatusBarInit();

        core = new Core(cbSet->currentText(), leAdr->text()+"/", temp);
        connect(core, SIGNAL(progress(int,int)), this, SLOT(StatusBarUpdate(int,int)));

        core->Calc();

        result = core->GetSum();
        results = core->GetFiles();
        std::sort(results.begin(), results.end());
        lwFiles->addItem(result.Name());

        temp.clear();
        for(ResFile res: results)
            temp.append(res.Name());
        lwFiles->addItems(temp);
        lwFiles->setCurrentRow(0);
        leTotalFiles->setText(QString::number(results.size()));
    }
    catch(std::runtime_error exc)
    {
        QMessageBox::information(this, "runtime_error", QString(exc.what()));
    }
    core->disconnect();
    delete core;
    StatusBarEnd();
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
    centralWidget()->setEnabled(false);
}

void MainWindow::StatusBarEnd()
{
    pbar->setEnabled(false);
    sblab->setText("");
    centralWidget()->setEnabled(true);
}

void MainWindow::StatusBarUpdate(int current, int total)
{
    pbar->setMaximum(total);
    pbar->setValue(current);
    sblab->setText("Przetwarzanie... "+QString::number(current)+" / "+QString::number(total));
}
