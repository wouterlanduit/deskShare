#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

// TODO
// 1. protocol om opeenvolgende pakketten te herkennen

// 2. elke connection aan netwerk hangen en allemaal sluiten als applicatie sluit
