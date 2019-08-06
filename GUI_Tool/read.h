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
 extern QString filename;
 extern int index;

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
     QGridLayout *layoutSpi    = new QGridLayout(this);
     QGridLayout *layoutI2C    = new QGridLayout(this);
     QGridLayout *layoutUSB    = new QGridLayout(this);
     QGridLayout *layoutCAN   = new QGridLayout(this);
     QGridLayout *layoutFDCAN    = new QGridLayout(this);
     std::vector <QCheckBox *> interfaces;

     QVector <QLineEdit *> value;
     QVector <QComboBox *> valueCombo;

     QVector <QLineEdit *> valueUsart;
     QVector <QComboBox *> valueUsartCombo;

     QVector <QLineEdit *> valueSpi;
     QVector <QComboBox *> valueSpiCombo;

     QVector <QLineEdit *> valueI2C;
     QVector <QComboBox *> valueI2CCombo;

     QVector <QLineEdit *> valueCAN;
     QVector <QComboBox *> valueCANCombo;

     QVector <QLineEdit *> valueFDCAN;
     QVector <QComboBox *> valueFDCANCombo;

     QVector <QLineEdit *> valueUSB;
     QVector <QComboBox *> valueUSBCombo;


        bool newFile ,newfile;
        std::vector <int> index;
     std::vector <QCheckBox*> staticTest ,  staticTestSpi ,staticTestCAN , staticTestFDCAN , staticTestI2C , staticTestUSB;
     std::vector <QCheckBox*> DynamicTest, DynamicTestSpi, DynamicTestCAN , DynamicTestFDCAN , DynamicTestI2C , DynamicTestUSB;
     std::vector <QCheckBox*> Requirement, RequirementSpi, RequirementTestCAN , RequirementTestFDCAN , RequirementTestI2C , RequirementTestUSB;



     void setPath(QString);
     bool getNewFile();
     Json::Value JSON;
     Json::Value::Members member;
     QLineEdit *lineEdit;

     QLabel *label,*Label;
     void onBrowseButton(QString );
     QLabel* newLabel(QString);
     QLabel* newSubLabel(QString);
     void Affiche();
     bool Mandatory();

     std::vector<unsigned int> getIndex( QString );


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
