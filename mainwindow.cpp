#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
 #include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Next1_clicked()
{

    if (( !(ui->radioButton->isChecked()) && (!(ui->radioButton_2->isChecked())) && (!(ui->radioButton_3->isChecked()))  && (!(ui->radioButton_4->isChecked())))  )
    {
       QMessageBox::warning(this,"","Radio_Button is not Selected" );

    }

    else if (ui->radioButton->isChecked())
    {
        hide();
        secDialog =new SecDialog(this);
        secDialog->show();

    }
    else if (ui->radioButton_2->isChecked())
    {
       // QMessageBox::warning(this,"","Radio_BUtton is not created" );
        hide();
        APPDialog = new appDialog(this);
        APPDialog->show();
    }
    else if (ui->radioButton_3->isChecked())
    {

        hide();
        dialog = new Dialog(this);
        dialog->show();
    }
    else if (ui->radioButton_4->isChecked())
    {

        hide();
        read = new Read(this);
        read->exec();
    }


}


