#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << "MainWindow shown";
    qDebug() << "MainWindow visible: " << w.isVisible();
    qDebug() << "Central widget visible: " << w.centralWidget()->isVisible();

    return a.exec();
}
