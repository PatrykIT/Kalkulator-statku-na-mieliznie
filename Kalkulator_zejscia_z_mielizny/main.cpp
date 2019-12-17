#include "mainwindow.h"
#include <QApplication>

#include "statek.h"
#include "Tests.h"
#include "Interpolacja.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow window;
    window.show();

    return a.exec();
}
