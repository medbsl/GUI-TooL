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
#include <vector>
#include <QCheckBox>
#include "dist\json\json.h"

 extern QString filename;
 extern std::vector <QCheckBox*> staticTest ;
 extern std::vector <QCheckBox*> DynamicTest ;
 extern std::vector <QCheckBox*> Requirement ;


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

     std::vector <QCheckBox*> staticTest ;
     std::vector <QCheckBox*> DynamicTest ;
     std::vector <QCheckBox*> Requirement ;



     Json::Value JSON;
     Json::Value::Members member;
     QLineEdit *lineEdit;
     void Test(QGridLayout *laYout, int x);


     int s;
    ~Read();

private slots:
     void onBrowseButton();
     void onSaveChanegeButton();
     void onCheckAllTestReq();
     void onCheckAllTestDynamic();
     void onCheckAllTestStatic();
     void requirement();




private:
    Ui::Read *ui;
    QPushButton *browseButton,*m_button;
};

#endif // READ_H
