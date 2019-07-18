#include "appdialog.h"
#include "ui_appdialog.h"


#include <QHBoxLayout>

appDialog::appDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::appDialog)
{
    ui->setupUi(this);



   /* m_line = new QLineEdit(this);
    QHBoxLayout* hlay = new QHBoxLayout;

    hlay->addWidget(m_line);
    hlay->setGeometry(QRect(QPoint(100, 10),QSize(120, 50)));

    hlay->setMargin(120); // 120 px
    setLayout(hlay);*/


}

appDialog::~appDialog()
{
    delete ui;
}

void appDialog::on_pushButton_clicked()
{

}



void appDialog::on_pushButton_5_clicked()
{

}
