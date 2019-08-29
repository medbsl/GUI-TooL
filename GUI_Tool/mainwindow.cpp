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
	
	/*Get the file name path to the variable "filename"*/
    filename = QFileDialog::getOpenFileName(this,tr("browse"), "./", "json File(*.json)");
	
	
    if(!filename.isEmpty()&& !filename.isNull())
    {
		/*"newFile" is a bool variable if the chcekbox is checked then it will be true*/
		/*else it will be false*/		
        if (ui->checkBox->checkState() == Qt::Checked)
            newFile = true;
        else if (ui->checkBox->checkState() == Qt::Unchecked)
            newFile = false;
				
        hide();
		/*create the "Read" class */
        uiread = new Read(this,filename,newFile);
		/*show the "Read" class */
        uiread->show();
    }
}

/*Get the file Path*/
QString MainWindow::getFilepath(){
    return filename;
}

void MainWindow::on_checkBox_clicked(){}

