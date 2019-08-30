#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include "read.h"

extern QString filename;
extern bool newFile,USARTSTATE,I2CSTATE,SPISTATE,CANSTATE,FDCANSTATE,USBSTATE;



namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //QString filename;
    QString getFilepath();
    bool newFile,USARTSTATE,I2CSTATE,SPISTATE,CANSTATE,FDCANSTATE,USBSTATE;
    Read *uiread;
    ~MainWindow();

private slots:
    void on_Next1_clicked();
    void on_checkBox_clicked();


    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

private:
    Ui::MainWindow *ui;






};



#endif // MAINWINDOW_H
