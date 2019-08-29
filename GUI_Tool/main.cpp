#include "mainwindow.h"
#include "read.h"
#include <QApplication>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

int main(int argc, char *argv[])
{
	/*QApplication is a library of the QT that will create the application */
    QApplication a(argc, argv);
	
	/*create a main window named w*/
    MainWindow w;
	
	/*Save the file path */
    QString path;	
    path=w.getFilepath();

	/*show the main window*/
    w.show();
	/*execute the application*/
    return a.exec();
}



