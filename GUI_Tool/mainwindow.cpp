#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



QString filename = "C://" ;

bool newFile =false;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Next1_clicked()
{

    newFile =false;

    filename = QFileDialog::getOpenFileName(this,tr("browse"), "C:/", "json File(*.json)");


    if(!filename.isEmpty()&& !filename.isNull())
    {
        if (ui->checkBox->checkState() == Qt::Checked)
            newFile = true;
        else if (ui->checkBox->checkState() == Qt::Unchecked)
            newFile = false;

           hide();
           uiread = new Read(this,filename,newFile);
           uiread->show();

    }





}



void MainWindow::on_checkBox_clicked()
{


}
QString MainWindow::getFilepath(){
    return filename;
}
