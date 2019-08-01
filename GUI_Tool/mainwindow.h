#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include "read.h"

extern QString filename;
extern bool newFile;

//QString filename;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString filename;
    QString getFilepath();
    bool newFile;
    Read *uiread;
    ~MainWindow();

private slots:
    void on_Next1_clicked();
    void on_checkBox_clicked();


private:
    Ui::MainWindow *ui;






};



#endif // MAINWINDOW_H
