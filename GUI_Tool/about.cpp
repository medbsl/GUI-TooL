#include "about.h"
#include "ui_about.h"
#include <QLabel>
#include <QString>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);


}

About::~About()
{
    delete ui;
}
