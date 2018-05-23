#include "mainwindow.h"
#include "src/core.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Core a("MSP430 asm", "./test_msp/");
    a.GetSum();
}

MainWindow::~MainWindow()
{

}
