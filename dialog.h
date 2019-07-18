#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <string>
#include <QScrollArea>
#include <QGridLayout>
#include <QTreeWidget>
#include <QVector>
#include <QCheckBox>

class QLineEdit;
class QPushButton;


namespace Ui {
class Dialog;
}
extern QString STlink;
extern QString UsartDt;
extern QString UsartSt;
extern QGridLayout *gridLayout;
extern QTreeWidget *treeWidget;

class Dialog : public QDialog
{
    Q_OBJECT

public:

    QString  STlink,UsartDt,UsartSt, DeviceId,i2cblVersion,spiBlVersion,usartBlversion,fdCanBlversion,usbBlVersion,fWBlVersion,blRamSize,canBlversion;

    QLineEdit *lineSTLINK, *blDataDeviceId, *blDataI2cBlVersion, *blDataSpiBlVersion, *blDataUsartBlVersion, *blDataFdCanBlVersion,
    *blDataUsbBlVersion, *blDataFwBlVersion, *blDataBlRamSize, *blDataCanBlVersion, *lineUsartSt,*lineUsartDt,*lineUsartName ,*lineUsartCom
    ,*lineUsartDriver,*lineUsartStatic,*lineUsartDynamic;

    explicit Dialog(QWidget *parent = 0);

     QGridLayout *gridLayout   = new QGridLayout(this);
     QGridLayout *usartLayout  = new QGridLayout(this);
     QGridLayout *i2cLayout    = new QGridLayout(this);
     QGridLayout *spiLayout    = new QGridLayout(this);
     QGridLayout *canLayout    = new QGridLayout(this);
     QGridLayout *fdCanLayout    = new QGridLayout(this);
    int i=0;
    QVector<QLineEdit*>linememory;

    QVector<QCheckBox*>checkBoxUsartStaticTest;
    QVector<QCheckBox*>checkBoxUsartStaticTestReq;

    QVector<QCheckBox*>checkBoxUsartDynamicTest;
    QVector<QCheckBox*>checkBoxUsartDynamicTestReq;

    QWidget *widgetUsart ;
    QScrollArea *scrollAreaUsart ;
    QScrollArea *scrollAreaI2c   ;
    QScrollArea *scrollAreaSpi   ;
    QScrollArea *scrollAreaCan   ;
    QScrollArea *scrollAreaFdCan ;

    QComboBox *BaudrateUsart,*FTDIUsart;



     void clicked();
    ~Dialog();

private slots:
     void handleButton();

     void ADDMemory();

private:
    Ui::Dialog *ui;
    QLineEdit* m_line;
    QPushButton *m_button, *buttonMemory;
    QComboBox *QPlatform, *comboBoxBlSpecificConnect, *comboBoxBlSpecificSupportMe, *comboBoxBlSpecificSupportBe;
    QScrollArea *scrollArea;



};

#endif // DIALOG_H
