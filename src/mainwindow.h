#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <src/import/Restorable.hpp>
#include "src/core.hpp"

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

private:
    void InitWidgets();
    void LoadConfigs();

    void Clear();
    void Display(Core &core);

    QComboBox* cbSet = nullptr;
    QLineEdit* leAdr = nullptr;
    QListWidget* lwIgnorowane = nullptr;
};

#endif // MAINWINDOW_H
