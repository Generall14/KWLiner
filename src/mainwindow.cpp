#include "mainwindow.h"
#include "src/core.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Core a("c/c++", "./test_cpp/");
    a.GetSum();
}

MainWindow::~MainWindow()
{

}
