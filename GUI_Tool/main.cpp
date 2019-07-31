#include "mainwindow.h"
#include "read.h"
#include <QApplication>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QString path;

    path=w.getFilepath();


    w.show();


    return a.exec();
}



