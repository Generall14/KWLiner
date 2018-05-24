#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <src/import/Restorable.hpp>
#include <QLabel>
#include "src/core.hpp"
#include "src/resFile.hpp"

class MainWindow : public QMainWindow, public Restorable
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void AddIgnored();
    void ModifyIgnored();
    void RemoveIgnored();
    void Run();
    void GetAdr();
    void Display(int c);

private:
    void InitWidgets();
    void LoadConfigs();

    void Clear();
    void Display(ResFile &fil);

    QComboBox* cbSet = nullptr;
    QLineEdit* leAdr = nullptr;
    QListWidget* lwIgnorowane = nullptr;

    QListWidget* lwFiles = nullptr;

    QLabel* leFile = nullptr;
    QLabel* leTotal = nullptr;
    QLabel* leCode = nullptr;
    QLabel* leComm = nullptr;
    QLabel* leLight = nullptr;

    ResFile result;
    QVector<ResFile> results;
};

#endif // MAINWINDOW_H
