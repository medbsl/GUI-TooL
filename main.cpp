#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Read R;
    R.show();


    //w.show();

    return a.exec();
}



