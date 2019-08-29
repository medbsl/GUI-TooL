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
 extern unsigned int page;
 extern int addmemory3;



extern bool newfile, UsartState,I2cState,SpiState,CanState,FDCanState,UsbState;

namespace Ui {
class Read;
}

class Read : public QDialog
{
    Q_OBJECT

public:



     explicit Read(QWidget *parent = 0);
     Read(QWidget *parent,QString filename, bool newFile, bool UsartState, bool I2cState, bool SpiState,
          bool CanState, bool FDCanState,bool UsbState);
     QGridLayout *layout    = new QGridLayout(this);
     QGridLayout *layoutUsart    = new QGridLayout(this);
     QGridLayout *layoutSpi    = new QGridLayout(this);
     QGridLayout *layoutI2C    = new QGridLayout(this);
     QGridLayout *layoutUSB    = new QGridLayout(this);
     QGridLayout *layoutCAN   = new QGridLayout(this);
     QGridLayout *layoutFDCAN    = new QGridLayout(this);
     std::vector <QCheckBox *> interfaces;


     std::vector <QLineEdit *> value;
     std::vector <QComboBox *> valueCombo;

     std::vector <QLineEdit *> valueUsart;
     std::vector <QComboBox *> valueUsartCombo;

     std::vector <QLineEdit *> valueSpi;
     std::vector <QComboBox *> valueSpiCombo;

     std::vector <QLineEdit *> valueI2C;
     std::vector <QComboBox *> valueI2CCombo;

     std::vector <QLineEdit *> valueCAN;
     std::vector <QComboBox *> valueCANCombo;

     std::vector <QLineEdit *> valueFDCAN;
     std::vector <QComboBox *> valueFDCANCombo;

     std::vector <QLineEdit *> valueUSB;
     std::vector <QComboBox *> valueUSBCombo;



     std::vector <QLineEdit *> additionalMemory;


        bool newFile ,newfile,UsartState,I2cState,SpiState,CanState,FDCanState,UsbState;
        std::vector <int> index;
     std::vector <QCheckBox*> staticTest , staticTestSpi ,staticTestCAN , staticTestFDCAN , staticTestI2C , staticTestUSB;
     std::vector <QCheckBox*> DynamicTest, DynamicTestSpi, DynamicTestCAN , DynamicTestFDCAN , DynamicTestI2C , DynamicTestUSB;
     std::vector <QCheckBox*> Requirement, RequirementSpi, RequirementTestCAN , RequirementTestFDCAN , RequirementTestI2C , RequirementTestUSB;



     void setPath(QString);
     void Plateform();
     bool getNewFile();
     Json::Value JSON;
     Json::Value::Members member;
     QLineEdit *lineEdit;

     QLabel *label,*Label;
     void onBrowseButton(QString );
     void onBrowseNewFile();

     void Test();


     QLabel* newLabel(QString);
     QLabel* newSubLabel(QString);
     void Affiche();
     void Interfaces();
     bool Mandatory();

     std::vector<unsigned int> getIndex( QString ,bool);


     int s;
    ~Read();
public slots:
     void onSaveChanegeButton( );


private slots:

     void onAddMemory();
     void onCheckAllTestReq();
     void onCheckAllTestDynamic();
     void onCheckAllTestStatic();

     void onCheckAllTestReqUSB();
     void onCheckAllTestDynamicUSB();
     void onCheckAllTestStaticUSB();

     void onCheckAllTestReqCAN();
     void onCheckAllTestDynamicCAN();
     void onCheckAllTestStaticCAN();

     void onCheckAllTestReqFDCAN();
     void onCheckAllTestDynamicFDCAN();
     void onCheckAllTestStaticFDCAN();

     void onCheckAllTestReqI2C();
     void onCheckAllTestDynamicI2C();
     void onCheckAllTestStaticI2C();

     void onCheckAllTestReqSPI();
     void onCheckAllTestDynamicSPI();
     void onCheckAllTestStaticSPI();




     void requirement();






private:
    Ui::Read *ui;
    QPushButton *browseButton,*m_button, *addmemory;
};

#endif // READ_H
