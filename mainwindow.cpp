#include "mainwindow.h"
#include <QUiLoader>
#include <QFile>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(nullptr)
{
    QUiLoader loader;
    QFile file("/home/alexvolin/runtimeXML/mainwindow.ui");
    file.open(QFile::ReadOnly);

    QWidget *myWidget = loader.load(&file, this);

    if (!myWidget) {
        qCritical() << "Cannot load UI file";
        return;
    }

    file.close();

    // get pointers to the buttons
    QPushButton *combatButton = myWidget->findChild<QPushButton*>("combatButton");
    QPushButton *dataButton = myWidget->findChild<QPushButton*>("dataButton");

    // connect buttons to slots or lambda functions
    connect(combatButton, &QPushButton::clicked, this, [](){
        qDebug() << "Combat System Inventory button clicked";
    });

    connect(dataButton, &QPushButton::clicked, this, [](){
        qDebug() << "Parametric Data Entry button clicked";
    });

    this->setCentralWidget(myWidget);
    qDebug() << "MainWindow constructed";
    qDebug() << "MainWindow visible: " << this->isVisible();
    qDebug() << "Central widget visible: " << this->centralWidget()->isVisible();
}

MainWindow::~MainWindow()
{
    delete ui;
}
