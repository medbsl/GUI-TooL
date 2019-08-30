#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



QString filename = "C://" ;
bool newFile =false;

/*Constructor that set up the mainWindow */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    filename = QFileDialog::getOpenFileName(this,tr("browse"), "./", "json File(*.json)");
	
	
    if(!filename.isEmpty()&& !filename.isNull())
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

void MainWindow::on_checkBox_clicked(){}


void MainWindow::on_checkBox_2_clicked()
{

}
