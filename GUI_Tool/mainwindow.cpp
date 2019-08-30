#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <iostream>
#include <fstream>



QString filename = "C://" ;
bool newFile =false;
bool ok=false;


Json::Value root;

/*Constructor that set up the mainWindow */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/img/ST.JPEG"));
}

/*Destructor of the MainWindow*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*Browse Button Clicked*/
void MainWindow::on_Next1_clicked()
{


	
    newFile =false;
    USARTSTATE=false;
    I2CSTATE=false;
    SPISTATE=false;
    CANSTATE=false;
    FDCANSTATE=false;
    USBSTATE=false;
	
	/*Get the file name path to the variable "filename"*/
    filename = QFileDialog::getOpenFileName(this,tr("browse"), QCoreApplication::applicationDirPath()+"//Templates", "json File(*.json)");
    ParseJson(filename);
	
    if(!filename.isEmpty()&& !filename.isNull() && ParseJson(filename))
    {
		/*"newFile" is a bool variable if the chcekbox is checked then it will be true*/
		/*else it will be false*/		
        if (ui->checkBox->checkState() == Qt::Checked)
            newFile = true;
        else
            newFile = false;
        if (ui->checkBox_2->checkState() == Qt::Checked)
            USARTSTATE= true ;
        else
            USARTSTATE = false;
        if (ui->checkBox_3->checkState() == Qt::Checked)
            I2CSTATE= true ;
        else
            I2CSTATE = false;

        if (ui->checkBox_4->checkState() == Qt::Checked)
            SPISTATE= true ;
        else
            SPISTATE = false;

        if (ui->checkBox_5->checkState() == Qt::Checked)
            CANSTATE= true ;
        else
            CANSTATE = false;


        if (ui->checkBox_6->checkState() == Qt::Checked)
            FDCANSTATE= true ;
        else
            FDCANSTATE = false;


        if (ui->checkBox_7->checkState() == Qt::Checked)
            USBSTATE= true ;
        else
            USBSTATE = false;


        this->setWindowState(Qt::WindowActive);
        //hide();
		/*create the "Read" class */
        uiread = new Read(this,filename,newFile,USARTSTATE,I2CSTATE,SPISTATE,CANSTATE,FDCANSTATE,USBSTATE);
		/*show the "Read" class */
        uiread->show();
    }
}

/*Get the file Path*/
QString MainWindow::getFilepath(){
    return filename;
}

void MainWindow::on_checkBox_clicked(){
    if(ui->checkBox->checkState() == Qt::Unchecked){
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        ui->checkBox_5->setCheckState(Qt::Unchecked);
        ui->checkBox_6->setCheckState(Qt::Unchecked);
        ui->checkBox_7->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_2->setCheckState(Qt::Unchecked);
}

void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_3->setCheckState(Qt::Unchecked);
}

void MainWindow::on_checkBox_4_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_4->setCheckState(Qt::Unchecked);
}

void MainWindow::on_checkBox_5_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_5->setCheckState(Qt::Unchecked);
}

void MainWindow::on_checkBox_6_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_6->setCheckState(Qt::Unchecked);
}

void MainWindow::on_checkBox_7_clicked()
{
    if(ui->checkBox->checkState() == Qt::Unchecked)
        ui->checkBox_7->setCheckState(Qt::Unchecked);
}

void MainWindow::on_actionabout_triggered()
{
    uiabout = new About(this);
    /*show the "Read" class */
    uiabout->show();

}

bool MainWindow::ParseJson(QString filepath){
    while(!ok){
        try{
            std::ifstream file(std::string(filepath.toLocal8Bit().constData()), std::ifstream::binary );
            file >> root;
            ok= true;

        }catch(std::exception &e){
            ok= false;
            filepath.clear();
            QMessageBox::warning(this,"Warning", QString::fromStdString(e.what()));
            break;
        }
    }
    return ok;
}
