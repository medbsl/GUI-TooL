#ifndef READ_H
#define READ_H

#include <QDialog>
#include <QGridLayout>
#include <QWidget>
#include <QScrollArea>
#include <QTabWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include <QCheckBox>
#include "dist\json\json.h"

 extern QString filename;
 extern QVector <QCheckBox*> staticTest ;
 extern QVector <QCheckBox*> DynamicTest ;
 extern QVector <QCheckBox*> Requirement ;
namespace Ui {
class Read;
}

class Read : public QDialog
{
    Q_OBJECT

public:
    explicit Read(QWidget *parent = 0);
     QGridLayout *layout    = new QGridLayout(this);
     QGridLayout *layoutUsart    = new QGridLayout(this);
     QString filename;
     QVector <std::string> name;
     QVector <QLineEdit *> value;
     QVector <QLineEdit *> valueUsart;
     QVector <QCheckBox*> staticTest ;
     QVector <QCheckBox*> DynamicTest ;
     QVector <QCheckBox*> Requirement ;

     Json::Value JSON;
     Json::Value::Members member;
     QLineEdit *lineEdit;
          void Test(QGridLayout *laYout, int x);

     int s;
    ~Read();

private slots:
     void onBrowseButton();
     void onSaveChanegeButton();


private:
    Ui::Read *ui;
    QPushButton *browseButton,*m_button;
};

#endif // READ_H
