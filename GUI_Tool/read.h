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
#include <QComboBox>
#include <QSignalMapper>
#include "dist\json\json.h"



 extern std::vector <QCheckBox*> staticTest ;
 extern std::vector <QCheckBox*> DynamicTest ;
 extern std::vector <QCheckBox*> Requirement ;

extern bool newfile;

namespace Ui {
class Read;
}

class Read : public QDialog
{
    Q_OBJECT

public:
     explicit Read(QWidget *parent = 0);
     Read(QWidget *parent,QString filename, bool newFile);
     QGridLayout *layout    = new QGridLayout(this);
     QGridLayout *layoutUsart    = new QGridLayout(this);
     //QString filename;

     QVector <QLineEdit *> value;
     QVector <QComboBox *> valueCombo;

     QVector <QLineEdit *> valueUsart;
     QVector <QComboBox *> valueUsartCombo;
        bool newFile ,newfile;
     std::vector <QCheckBox*> staticTest ;
     std::vector <QCheckBox*> DynamicTest ;
     std::vector <QCheckBox*> Requirement ;
     void setPath(QString);
     bool getNewFile();
     Json::Value JSON;
     Json::Value::Members member;
     QLineEdit *lineEdit;
     void Test(QGridLayout *laYout, int x);


     void onBrowseButton(QString ,bool);
     int s;
    ~Read();
public slots:
     void onSaveChanegeButton( );


private slots:


     void onCheckAllTestReq();
     void onCheckAllTestDynamic();
     void onCheckAllTestStatic();
     void requirement();






private:
    Ui::Read *ui;
    QPushButton *browseButton,*m_button;
};

#endif // READ_H
