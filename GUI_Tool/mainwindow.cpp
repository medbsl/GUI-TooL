#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


bool newFile =false;

QString filename = "C:\ " ;
//filename = "C:\ " ;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filename = "C:\ " ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Next1_clicked()
{

    //filename = QFileDialog::getOpenFileName(this,tr("browse"), "C:/", "json File(*.json)");
    if (ui->checkBox->checkState() == Qt::Checked)
        newFile = true;
    else if (ui->checkBox->checkState() == Qt::Unchecked)
        newFile = false;
    
       hide();
       uiread = new Read(this);
       uiread->show();
       uiread->onBrowseButton();


}



void MainWindow::on_checkBox_clicked()
{


}
QString MainWindow::getFilepath(){
    return filename;
}
