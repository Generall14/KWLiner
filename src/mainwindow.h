#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <src/import/Restorable.hpp>

class MainWindow : public QMainWindow, public Restorable
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void InitWidgets();
    void LoadConfigs();

    QComboBox* cbSet = nullptr;
    QLineEdit* leAdr = nullptr;
    QListWidget* lwIgnorowane = nullptr;
};

#endif // MAINWINDOW_H
