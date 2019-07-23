#include "dialog.h"
#include "ui_dialog.h"
#include "dist\json\json.h"

#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QComboBox>
#include <fstream>
#include <QTextStream>
#include <Qlabel>
#include <QFont>
#include <QTextEdit>
#include <QString>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QTreeWidget>
#include <QVector>
#include <Qcheckbox>



int i=0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{


    ui->setupUi(this);
    //this->setGeometry( 100, 100, 570, 768);




//*****************************************************************************//
//****************************      Plateform      ****************************//
//*****************************************************************************//

    // Label Plateform
        QLabel *label = new QLabel(this);
        label->setGeometry(QRect(QPoint(30, 10),QSize(121, 21)));
        label->setText("Plateform :");


        QFont font;//( "MS Shell Dlg 2", 12, QFont::Bold);
        font.setFamily("MS Shell Dlg 2");
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);


    // Label Plateform Mode
        QLabel *labelMode = new QLabel(this);
        labelMode->setGeometry(QRect(QPoint(50, 48),QSize(176, 25)));
        labelMode->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        labelMode->setText("Plateform Mode");


        QFont fontMode;
        fontMode.setFamily("MS Shell Dlg 2");
        fontMode.setPointSize(10);
        fontMode.setBold(false);
        labelMode->setFont(fontMode);


    // ComboBox Plateform
        //QHBoxLayout *layoutComboBox = new QHBoxLayout( this );
        QPlatform = new QComboBox( this );
        QPlatform->setEditable( false );
        QPlatform->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        QPlatform->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
        QPlatform->addItem(tr("Automated"));
        QPlatform->addItem(tr("Cli"));








//*****************************************************************************//
//****************************        Target        ***************************//
//*****************************************************************************//

    // Label Target
        QLabel *labelTarget = new QLabel(this);
        labelTarget->setGeometry(QRect(QPoint(30, 100),QSize(121, 25)));
        labelTarget->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        labelTarget->setText("Target :");


        QFont fontTarget;
        fontTarget.setFamily("MS Shell Dlg 2");
        fontTarget.setPointSize(12);
        fontTarget.setBold(true);
        labelTarget->setFont(fontTarget);


    // Label Target Mode
        QLabel *targetLabel = new QLabel(this);
        targetLabel->setGeometry(QRect(QPoint(50, 138),QSize(176, 25)));
        targetLabel->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        targetLabel->setText("STLINK_SN");


        QFont fontSTLINK;
        fontSTLINK.setFamily("MS Shell Dlg 2");
        fontSTLINK.setPointSize(10);
        fontSTLINK.setBold(false);
        targetLabel->setFont(fontSTLINK);

    // Text Edit

        lineSTLINK = new QLineEdit(this);
        lineSTLINK->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));


//*****************************************************************************//
//****************************        BL_specific   ***************************//
//*****************************************************************************//

    // Label BlSpecific
        QLabel *labelBlSpecific = new QLabel(this);
        labelBlSpecific->setGeometry(QRect(QPoint(30, 500),QSize(176, 25)));
        labelBlSpecific->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        labelBlSpecific->setText("bl_specific");


        QFont fontBlSpecific;
        fontBlSpecific.setFamily("MS Shell Dlg 2");
        fontBlSpecific.setPointSize(12);
        fontBlSpecific.setBold(true);
        labelBlSpecific->setFont(fontBlSpecific);


   // Label Connect
        QLabel *labelBlSpecificconnect = new QLabel(this);
        labelBlSpecificconnect->setGeometry(QRect(QPoint(30, 530),QSize(176, 25)));
        labelBlSpecificconnect->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
        labelBlSpecificconnect->setText("Connect :");


        QFont fontBlSpecificconnect;
        fontBlSpecificconnect.setFamily("MS Shell Dlg 2");
        fontBlSpecificconnect.setPointSize(10);
        fontBlSpecificconnect.setBold(false);
        labelBlSpecificconnect->setFont(fontBlSpecificconnect);

                    comboBoxBlSpecificConnect = new QComboBox( this );
                    comboBoxBlSpecificConnect->setEditable( false );
                    comboBoxBlSpecificConnect->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                    comboBoxBlSpecificConnect->setGeometry(QRect(QPoint(230,530),QSize(176, 25)));
                    comboBoxBlSpecificConnect->addItem(tr("true"));
                    comboBoxBlSpecificConnect->addItem(tr("false"));




    // Label Support Me
         QLabel *labelBlSpecificSupportMe = new QLabel(this);
         labelBlSpecificSupportMe->setGeometry(QRect(QPoint(30, 590),QSize(176, 25)));
         labelBlSpecificSupportMe->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
         labelBlSpecificSupportMe->setText("Support ME :");


         QFont fontBlSpecificSupportMe;
         fontBlSpecificSupportMe.setFamily("MS Shell Dlg 2");
         fontBlSpecificSupportMe.setPointSize(10);
         fontBlSpecificSupportMe.setBold(false);
         labelBlSpecificSupportMe->setFont(fontBlSpecificSupportMe);


                     comboBoxBlSpecificSupportMe = new QComboBox( this );
                     comboBoxBlSpecificSupportMe->setEditable( false );
                     comboBoxBlSpecificSupportMe->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                     comboBoxBlSpecificSupportMe->setGeometry(QRect(QPoint(230,590),QSize(176, 25)));
                     comboBoxBlSpecificSupportMe->addItem(tr("true"));
                     comboBoxBlSpecificSupportMe->addItem(tr("false"));

     // Label support BE
          QLabel *labelBlSpecificSupportBE = new QLabel(this);
          labelBlSpecificSupportBE->setGeometry(QRect(QPoint(30, 650),QSize(176, 25)));
          labelBlSpecificSupportBE->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
          labelBlSpecificSupportBE->setText("Support Be :");


          QFont fontBlSpecificSupportBE;
          fontBlSpecificSupportBE.setFamily("MS Shell Dlg 2");
          fontBlSpecificSupportBE.setPointSize(10);
          fontBlSpecificSupportBE.setBold(false);
          labelBlSpecificSupportBE->setFont(fontBlSpecificSupportBE);


                      comboBoxBlSpecificSupportBe = new QComboBox( this );
                      comboBoxBlSpecificSupportBe->setEditable( false );
                      comboBoxBlSpecificSupportBe->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                      comboBoxBlSpecificSupportBe->setGeometry(QRect(QPoint(230,650),QSize(176, 25)));
                      comboBoxBlSpecificSupportBe->addItem(tr("true"));
                      comboBoxBlSpecificSupportBe->addItem(tr("false"));

//*****************************************************************************//
//****************************        BL_Data       ***************************//
//*****************************************************************************//
      // Label blData
          QLabel *labelBlData = new QLabel(this);
          labelBlData->setGeometry(QRect(QPoint(20, 136),QSize(121, 100)));
          labelBlData->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
          labelBlData->setText("bl_data :");


          QFont fontBlData;
          fontBlData.setFamily("MS Shell Dlg 2");
          fontBlData.setPointSize(12);
          fontBlData.setBold(true);
          labelBlData->setFont(fontBlData);

      // Label blData Device id
          QLabel *labelBlDataDeviceId = new QLabel(this);
          labelBlDataDeviceId->setGeometry(QRect(QPoint(33, 228),QSize(176, 25)));
          labelBlDataDeviceId->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
          labelBlDataDeviceId->setText("device_id");


          QFont fontBlDataDeviceId;
          fontBlDataDeviceId.setFamily("MS Shell Dlg 2");
          fontBlDataDeviceId.setPointSize(10);
          fontBlDataDeviceId.setBold(false);
          labelBlDataDeviceId->setFont(fontBlDataDeviceId);

          // Text Edit Bl data device id

              blDataDeviceId = new QLineEdit(this);
              blDataDeviceId->setGeometry(QRect(QPoint(230, 228),QSize(176, 23)));


          // Label blData i2c bl version
              QLabel *labeli2cBlVersion = new QLabel(this);
              labeli2cBlVersion->setGeometry(QRect(QPoint(33, 258),QSize(176, 25)));
              labeli2cBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labeli2cBlVersion->setText("i2c_bl_version");


              QFont fontI2cBlVersion;
              fontI2cBlVersion.setFamily("MS Shell Dlg 2");
              fontI2cBlVersion.setPointSize(10);
              fontI2cBlVersion.setBold(false);
              labeli2cBlVersion->setFont(fontI2cBlVersion);

              // Text Edit

                  blDataI2cBlVersion= new QLineEdit(this);
                  blDataI2cBlVersion->setGeometry(QRect(QPoint(230, 258),QSize(176, 23)));



          // Label blData spi bl version
              QLabel *labelspiBlVersion = new QLabel(this);
              labelspiBlVersion->setGeometry(QRect(QPoint(33, 288),QSize(176, 25)));
              labelspiBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelspiBlVersion->setText("spi_bl_version");


              QFont fontSpiBlVersion;
              fontSpiBlVersion.setFamily("MS Shell Dlg 2");
              fontSpiBlVersion.setPointSize(10);
              fontSpiBlVersion.setBold(false);
              labelspiBlVersion->setFont(fontSpiBlVersion);

              // Text Edit

                  blDataSpiBlVersion= new QLineEdit(this);
                  blDataSpiBlVersion->setGeometry(QRect(QPoint(230, 288),QSize(176, 23)));




          // Label blData usart bl version
              QLabel *labelUsartBlVersion = new QLabel(this);
              labelUsartBlVersion->setGeometry(QRect(QPoint(33, 318),QSize(176, 25)));
              labelUsartBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelUsartBlVersion->setText("usart_bl_version");


              QFont fontUsartBlVersion;
              fontUsartBlVersion.setFamily("MS Shell Dlg 2");
              fontUsartBlVersion.setPointSize(10);
              fontUsartBlVersion.setBold(false);
              labelUsartBlVersion->setFont(fontUsartBlVersion);

              // Text Edit

                  blDataUsartBlVersion= new QLineEdit(this);
                  blDataUsartBlVersion->setGeometry(QRect(QPoint(230, 318),QSize(176, 23)));



          // Label blData fd can bl version
              QLabel *labelFdCanBlVersion = new QLabel(this);
              labelFdCanBlVersion->setGeometry(QRect(QPoint(33, 348),QSize(176, 25)));
              labelFdCanBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelFdCanBlVersion->setText("fd_can_bl_version");


              QFont fontFdCanBlVersion;
              fontFdCanBlVersion.setFamily("MS Shell Dlg 2");
              fontFdCanBlVersion.setPointSize(10);
              fontFdCanBlVersion.setBold(false);
              labelFdCanBlVersion->setFont(fontFdCanBlVersion);

              // Text Edit

                  blDataFdCanBlVersion= new QLineEdit(this);
                  blDataFdCanBlVersion->setGeometry(QRect(QPoint(230, 348),QSize(176, 23)));



          // Label blData usb bl version
              QLabel *labelUsbBlVersion = new QLabel(this);
              labelUsbBlVersion->setGeometry(QRect(QPoint(33, 378),QSize(176, 25)));
              labelUsbBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelUsbBlVersion->setText("usb_bl_version");


              QFont fontUsbBlVersion;
              fontUsbBlVersion.setFamily("MS Shell Dlg 2");
              fontUsbBlVersion.setPointSize(10);
              fontUsbBlVersion.setBold(false);
              labelUsbBlVersion->setFont(fontUsbBlVersion);

              // Text Edit

                  blDataUsbBlVersion= new QLineEdit(this);
                  blDataUsbBlVersion->setGeometry(QRect(QPoint(230, 378),QSize(176, 23)));




          // Label blData fw bl version
              QLabel *labelFwBlVersion = new QLabel(this);
              labelFwBlVersion->setGeometry(QRect(QPoint(33, 408),QSize(176, 25)));
              labelFwBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelFwBlVersion->setText("fw_bl_version");


              QFont fontFwBlVersion;
              fontFwBlVersion.setFamily("MS Shell Dlg 2");
              fontFwBlVersion.setPointSize(10);
              fontFwBlVersion.setBold(false);
              labelFwBlVersion->setFont(fontFwBlVersion);

              // Text Edit

                  blDataFwBlVersion= new QLineEdit(this);
                  blDataFwBlVersion->setGeometry(QRect(QPoint(230, 408),QSize(176, 23)));


          // Label blData Bl ram size
              QLabel *labelBlRamSize = new QLabel(this);
              labelBlRamSize->setGeometry(QRect(QPoint(33, 438),QSize(176, 25)));
              labelBlRamSize->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelBlRamSize->setText("Bl Ram Size");


              QFont fontBlRamSize;
              fontBlRamSize.setFamily("MS Shell Dlg 2");
              fontBlRamSize.setPointSize(10);
              fontBlRamSize.setBold(false);
              labelBlRamSize->setFont(fontBlRamSize);

              // Text Edit

                  blDataBlRamSize= new QLineEdit(this);
                  blDataBlRamSize->setGeometry(QRect(QPoint(230, 438),QSize(176, 23)));



          // Label blData Can Bl version
              QLabel *labelCanBlVersion = new QLabel(this);
              labelCanBlVersion->setGeometry(QRect(QPoint(33, 468),QSize(176, 25)));
              labelCanBlVersion->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
              labelCanBlVersion->setText("Can Bl version");


              QFont fontCanBlVersion;
              fontCanBlVersion.setFamily("MS Shell Dlg 2");
              fontCanBlVersion.setPointSize(10);
              fontCanBlVersion.setBold(false);
              labelCanBlVersion->setFont(fontCanBlVersion);

              // Text Edit

                  blDataCanBlVersion= new QLineEdit(this);
                  blDataCanBlVersion->setGeometry(QRect(QPoint(230, 468),QSize(176, 23)));

//*****************************************************************************//
//****************************      Memory          ***************************//
//*****************************************************************************//

          // Label Memory
              QLabel *memory = new QLabel(this);
              memory->setGeometry(QRect(QPoint(30, 10),QSize(121, 21)));
              memory->setText("Memory :");


              QFont fontMemory;//( "MS Shell Dlg 2", 12, QFont::Bold);
              fontMemory.setFamily("MS Shell Dlg 2");
              fontMemory.setPointSize(12);
              fontMemory.setBold(true);
              memory->setFont(fontMemory);

          // Button ADD
              QHBoxLayout* addButton = new QHBoxLayout( this );
              addButton->setContentsMargins(0,0,0,0);
              buttonMemory = new QPushButton("ADD Memory", this);
              buttonMemory->setGeometry(QRect(QPoint(455, 700),QSize(100, 40)));
              connect(buttonMemory,SIGNAL (clicked()), this, SLOT(ADDMemory()));



//*****************************************************************************//
//****************************    Generate Button   ***************************//
//*****************************************************************************//


  // PushButton
      QHBoxLayout* layoutButton = new QHBoxLayout( this );
      layoutButton->setContentsMargins(0,0,0,0);
      m_button = new QPushButton("Generate", this);
      m_button->setGeometry(QRect(QPoint(895, 855),QSize(100, 20)));
      connect(m_button,SIGNAL (clicked()), this, SLOT(handleButton()));




//*****************************************************************************//
//****************************     scroll area      ***************************//
//*****************************************************************************//



                  QScrollArea *scrollAreaPlateform = new QScrollArea(this);
                  scrollAreaPlateform->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                  scrollAreaPlateform->setWidgetResizable( true );
                  scrollAreaPlateform->setGeometry( 5, 5, 995, 895 );


                  QWidget *widget = new QWidget();

                  scrollAreaPlateform->setWidget( widget );


                  widget->setLayout( gridLayout );




                // int i=0;

                  gridLayout->addWidget(label, i, 0);

                                gridLayout->addWidget(labelBlData,i, 3);
                  gridLayout->addWidget(labelMode, ++i, 0);
                  gridLayout->addWidget(QPlatform, i, 1);


                              gridLayout->addWidget(labelBlDataDeviceId, i, 3);
                              gridLayout->addWidget(blDataDeviceId,i, 4);



                  gridLayout->addWidget(labelTarget, ++i, 0);

                                    gridLayout->addWidget(blDataI2cBlVersion,i, 4);
                                    gridLayout->addWidget(labeli2cBlVersion, i, 3);
                  gridLayout->addWidget(targetLabel, ++i, 0);
                  gridLayout->addWidget(lineSTLINK, i, 1);
                                  gridLayout->addWidget(blDataSpiBlVersion,i, 4);
                                  gridLayout->addWidget(labelspiBlVersion, i, 3);

                  gridLayout->addWidget(labelBlSpecific, ++i, 0);
                                  gridLayout->addWidget(blDataUsartBlVersion,i, 4);
                                  gridLayout->addWidget(labelUsartBlVersion, i, 3);
                  gridLayout->addWidget(labelBlSpecificconnect, ++i, 0);
                  gridLayout->addWidget(comboBoxBlSpecificConnect, i, 1);

                                  gridLayout->addWidget( labelFdCanBlVersion,i, 3 );
                                  gridLayout->addWidget( blDataFdCanBlVersion,i, 4 );

                  gridLayout->addWidget(labelBlSpecificSupportMe, ++i, 0);
                  gridLayout->addWidget(comboBoxBlSpecificSupportMe, i, 1);


                                  gridLayout->addWidget( labelUsbBlVersion,i, 3 );
                                  gridLayout->addWidget( blDataUsbBlVersion,i, 4 );


                  gridLayout->addWidget(labelBlSpecificSupportBE, ++i, 0);
                  gridLayout->addWidget(comboBoxBlSpecificSupportBe, i, 1);

                                  gridLayout->addWidget( labelFwBlVersion,i, 3);
                                  gridLayout->addWidget( blDataFwBlVersion,i,4 );

                                  gridLayout->addWidget( labelBlRamSize ,++i, 3);
                                  gridLayout->addWidget( blDataBlRamSize,i, 4 );

                                  gridLayout->addWidget( labelCanBlVersion,  ++i, 3 );
                                  gridLayout->addWidget( blDataCanBlVersion ,i  , 4);
// ******************


// ********************
                  gridLayout->addWidget( memory,++i, 0 );
                  gridLayout->addWidget( buttonMemory ,++i, 0);


                                 /* ... */

                 // gridLayout->addWidget( m_button ,350, 5);

//*****************************************************************************//
//****************************  scroll area Uart    ***************************//
//*****************************************************************************//



                QScrollArea *scrollAreaUsart =new QScrollArea ;
                  scrollAreaUsart->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                  scrollAreaUsart->setWidgetResizable( true );
                  scrollAreaUsart->setGeometry( 5, 5, 695, 895 );


                  QWidget *widgetUsart = new QWidget;
                  scrollAreaUsart-> setWidget( widgetUsart );
                  widgetUsart->setLayout( usartLayout );





                                        /* ... */

                  // Label USART
                      QLabel *labelUsart = new QLabel(this);
                      labelUsart->setGeometry(QRect(QPoint(30, 100),QSize(121, 25)));

                      labelUsart->setText("Usart :");


                      QFont fontUsart;
                      fontUsart.setFamily("MS Shell Dlg 2");
                      fontUsart.setPointSize(12);
                      fontUsart.setBold(true);
                      labelUsart->setFont(fontUsart);




                  // Text Edit

                      lineUsartName = new QLineEdit(this);
                      lineUsartName->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));


                      // Label UsartBaudrate
                          QLabel *UsartBaudrateLabel = new QLabel(this);
                          UsartBaudrateLabel->setText("Baudrate");


                          QFont fontUsartBaudrate;
                          fontUsartBaudrate.setFamily("MS Shell Dlg 2");
                          fontUsartBaudrate.setPointSize(10);
                          fontUsartBaudrate.setBold(false);
                          UsartBaudrateLabel->setFont(fontUsartBaudrate);
                        //ComboBoX
                          BaudrateUsart = new QComboBox( this );
                          BaudrateUsart->setEditable( false );
                          BaudrateUsart->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                          BaudrateUsart->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                          BaudrateUsart->addItem(tr("9600"));
                          BaudrateUsart->addItem(tr("115200"));




                          QLabel *UsartComLabel = new QLabel(this);
                          UsartComLabel->setText("COM");


                          QFont fontUsartCom;
                          fontUsartCom.setFamily("MS Shell Dlg 2");
                          fontUsartCom.setPointSize(10);
                          fontUsartCom.setBold(false);
                          UsartComLabel->setFont(fontUsartCom);

                          lineUsartCom = new QLineEdit(this);
                          lineUsartCom->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));









                          QLabel *UsartDriverLabel = new QLabel(this);
                          UsartDriverLabel->setText("Driver");


                          QFont fontUsartDriver;
                          fontUsartDriver.setFamily("MS Shell Dlg 2");
                          fontUsartDriver.setPointSize(10);
                          fontUsartDriver.setBold(false);
                          UsartDriverLabel->setFont(fontUsartDriver);

                          lineUsartDriver = new QLineEdit(this);
                          lineUsartDriver->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));








                          QLabel *UsartFtdiLabel = new QLabel(this);
                          UsartFtdiLabel->setText("Static");


                          QFont fontUsartFtdi;
                          fontUsartFtdi.setFamily("MS Shell Dlg 2");
                          fontUsartFtdi.setPointSize(10);
                          fontUsartFtdi.setBold(false);
                          UsartFtdiLabel->setFont(fontUsartFtdi);
                          lineUsartStatic = new QLineEdit(this);
                          lineUsartStatic->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));







                          QLabel *UsartDynamicLabel = new QLabel(this);
                          UsartDynamicLabel->setText("Dynamic");


                          QFont fontUsartDynamic;
                          fontUsartDynamic.setFamily("MS Shell Dlg 2");
                          fontUsartDynamic.setPointSize(10);
                          fontUsartDynamic.setBold(false);
                          UsartDynamicLabel->setFont(fontUsartDynamic);
                          lineUsartDynamic = new QLineEdit(this);
                          lineUsartDynamic->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));


                          QLabel *UsartStaticTestLabel = new QLabel(this);
                          UsartStaticTestLabel->setText("Static Test:");


                          QFont fontUsartStaticTest;
                          fontUsartStaticTest.setFamily("MS Shell Dlg 2");
                          fontUsartStaticTest.setPointSize(12);
                          fontUsartStaticTest.setBold(true);
                          UsartStaticTestLabel->setFont(fontUsartStaticTest);


                          QLabel *UsartDynamicTestLabel = new QLabel(this);
                          UsartDynamicTestLabel->setText("Dynamic Test:");


                          QFont fontUsartDynamicTest;
                          fontUsartDynamicTest.setFamily("MS Shell Dlg 2");
                          fontUsartDynamicTest.setPointSize(12);
                          fontUsartDynamicTest.setBold(true);
                          UsartDynamicTestLabel->setFont(fontUsartStaticTest);

                          QLabel *UsartStaticTestReqLabel = new QLabel(this);
                          UsartStaticTestReqLabel->setText("Requirements :");


                          QFont fontUsartStaticTestReq;
                          fontUsartStaticTestReq.setFamily("MS Shell Dlg 2");
                          fontUsartStaticTestReq.setPointSize(12);
                          fontUsartStaticTestReq.setBold(true);
                          UsartStaticTestReqLabel->setFont(fontUsartStaticTestReq);





                         // QCheckBox *

                     /*     QLabel *UsartStatic001 = new QLabel("Req001",this);
                          QLabel *UsartStatic002 = new QLabel("Req001",this);
                          QLabel *UsartStatic003 = new QLabel("Req001",this);
                          QLabel *UsartStatic004 = new QLabel("Req000",this);
                          QLabel *UsartStatic005 = new QLabel("Req000",this);
                          QLabel *UsartStatic006 = new QLabel("Req003",this);
                          QLabel *UsartStatic007 = new QLabel("Req003",this);
                          QLabel *UsartStatic008 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic009 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);

                          QLabel *UsartStatic010 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic011 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic012 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic013 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic014 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic015 = new QLabel("Req010,Req011,Req012,Req013,Req014,Req015",this);
                          QLabel *UsartStatic016 = new QLabel("Req018,Req019",this);
                          QLabel *UsartStatic017 = new QLabel("Req018,Req019",this);
                          QLabel *UsartStatic018 = new QLabel("Req018,Req019",this);
                          QLabel *UsartStatic019 = new QLabel("Req018,Req019",this);

                          QLabel *UsartStatic020 = new QLabel("Req018,Req019",this);
                          QLabel *UsartStatic021 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic022 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic023 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic024 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic025 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic026 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic027 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic028 = new QLabel("Req004,Req005,Req006,Req007,Req008,Req009",this);
                          QLabel *UsartStatic029 = new QLabel("Req016,Req017",this);

                          QLabel *UsartStatic030 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic031 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic032 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic033 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic034 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic035 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic036 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic037 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic038 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic039 = new QLabel("Req016,Req017",this);

                          QLabel *UsartStatic040 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic041 = new QLabel("Req016,Req017",this);
                          QLabel *UsartStatic042 = new QLabel("Req020",this);
                          QLabel *UsartStatic043 = new QLabel("Req020",this);
                          QLabel *UsartStatic044 = new QLabel("Req020",this);
                          QLabel *UsartStatic045 = new QLabel("Req020",this);
                          QLabel *UsartStatic046 = new QLabel("Req020",this);
                          QLabel *UsartStatic047 = new QLabel("Req021",this);
                          QLabel *UsartStatic048 = new QLabel("Req021",this);
                          QLabel *UsartStatic049 = new QLabel("Req021",this);

                          QLabel *UsartStatic050 = new QLabel("Req023",this);
                          QLabel *UsartStatic051 = new QLabel("Req023",this);
                          QLabel *UsartStatic052 = new QLabel("Req023",this);
                          QLabel *UsartStatic053 = new QLabel("Req024",this);
                          QLabel *UsartStatic054 = new QLabel("Req024",this);
                          QLabel *UsartStatic055 = new QLabel("Req024",this);*/


                          //Add to widget












                            /* ... */



                  usartLayout->addWidget( labelUsart ,0, 0);





                  usartLayout->addWidget(UsartBaudrateLabel,2,0);
                  usartLayout->addWidget(BaudrateUsart,2,1,1,1);

                  usartLayout->addWidget(UsartComLabel,3,0);
                  usartLayout->addWidget(lineUsartCom,3,1);

                  usartLayout->addWidget(UsartDriverLabel,4,0);
                  usartLayout->addWidget(lineUsartDriver,4,1);


                  usartLayout->addWidget(UsartFtdiLabel,5,0);
                  usartLayout->addWidget(lineUsartStatic,5,1);


                  usartLayout->addWidget(UsartDynamicLabel,6,0);
                  usartLayout->addWidget(lineUsartDynamic,6,1);

                  usartLayout->addWidget(UsartStaticTestLabel,7,0);
                  usartLayout->addWidget(UsartDynamicTestLabel,7,1);
                  usartLayout->addWidget(UsartStaticTestReqLabel,7,2);








                 // usartLayout->addWidget( UsartStatic001 ,8, 1);




                  for(int i=1;i<56;i++)
                  {
                      QString add;
                      if (i<10)
                          add ="USART_S_00" + QString::number(i);
                      else if (i<100)
                          add ="USART_S_0" + QString::number(i);

                      QCheckBox *UsartStaticTest=new QCheckBox(add,this);
                      checkBoxUsartStaticTest.push_back(UsartStaticTest);
                      usartLayout->addWidget(UsartStaticTest,i+7,0);
                  }


                  for(int i=1;i<56;i++)
                  {
                      QString add;
                      if (i<10)
                          add ="USART_D_00" + QString::number(i);
                      else if (i<100)
                          add ="USART_D_0" + QString::number(i);

                      QCheckBox *UsartDynamicTest=new QCheckBox(add,this);
                      checkBoxUsartDynamicTest.push_back(UsartDynamicTest);
                      usartLayout->addWidget(UsartDynamicTest,i+7,1);
                  }

                  for(int i=0;i<25;i++)
                  {
                      QString addReq;
                      if (i<10)
                          addReq ="USART_Req00" + QString::number(i);
                      else if (i<100)
                          addReq ="USART_Req0" + QString::number(i);

                      QCheckBox *UsartStaticTestReq=new QCheckBox(addReq,this);
                      checkBoxUsartStaticTestReq.push_back(UsartStaticTestReq);
                      usartLayout->addWidget(UsartStaticTestReq,i+8,2);
                  }




             /*    usartLayout->addWidget( UsartStatic001 , 8,  3);
                  usartLayout->addWidget( UsartStatic002 , 9, 3);
                  usartLayout->addWidget( UsartStatic003 ,10, 3);
                  usartLayout->addWidget( UsartStatic004 ,11, 3);
                  usartLayout->addWidget( UsartStatic005 ,12, 3);
                  usartLayout->addWidget( UsartStatic006 ,13, 3);
                  usartLayout->addWidget( UsartStatic007 ,14, 3);
                  usartLayout->addWidget( UsartStatic008 ,15, 3);
                  usartLayout->addWidget( UsartStatic009 ,16, 3);

                  usartLayout->addWidget( UsartStatic010 ,17, 2);
                  usartLayout->addWidget( UsartStatic011 ,18, 2);
                  usartLayout->addWidget( UsartStatic012 ,19, 2);
                  usartLayout->addWidget( UsartStatic013 ,20, 2);
                  usartLayout->addWidget( UsartStatic014 ,21, 2);
                  usartLayout->addWidget( UsartStatic015 ,22, 2);
                  usartLayout->addWidget( UsartStatic016 ,23, 2);
                  usartLayout->addWidget( UsartStatic017 ,24, 2);
                  usartLayout->addWidget( UsartStatic018 ,25, 2);
                  usartLayout->addWidget( UsartStatic019 ,26, 2);

                  usartLayout->addWidget( UsartStatic020 ,27, 2);
                  usartLayout->addWidget( UsartStatic021 ,28, 2);
                  usartLayout->addWidget( UsartStatic022 ,29, 2);
                  usartLayout->addWidget( UsartStatic023 ,30, 2);
                  usartLayout->addWidget( UsartStatic024 ,31, 2);
                  usartLayout->addWidget( UsartStatic025 ,32, 2);
                  usartLayout->addWidget( UsartStatic026 ,33, 2);
                  usartLayout->addWidget( UsartStatic027 ,34, 2);
                  usartLayout->addWidget( UsartStatic028 ,35, 2);
                  usartLayout->addWidget( UsartStatic029 ,36, 2);

                  usartLayout->addWidget( UsartStatic030 ,37, 2);
                  usartLayout->addWidget( UsartStatic031 ,38, 2);
                  usartLayout->addWidget( UsartStatic032 ,39, 2);
                  usartLayout->addWidget( UsartStatic033 ,40, 2);
                  usartLayout->addWidget( UsartStatic034 ,41, 2);
                  usartLayout->addWidget( UsartStatic035 ,42, 2);
                  usartLayout->addWidget( UsartStatic036 ,43, 2);
                  usartLayout->addWidget( UsartStatic037 ,44, 2);
                  usartLayout->addWidget( UsartStatic038 ,45, 2);
                  usartLayout->addWidget( UsartStatic039 ,46, 2);

                  usartLayout->addWidget( UsartStatic040 ,47, 2);
                  usartLayout->addWidget( UsartStatic041 ,48, 2);
                  usartLayout->addWidget( UsartStatic042 ,49, 2);
                  usartLayout->addWidget( UsartStatic043 ,50, 2);
                  usartLayout->addWidget( UsartStatic044 ,51, 2);
                  usartLayout->addWidget( UsartStatic045 ,52, 2);
                  usartLayout->addWidget( UsartStatic046 ,53, 2);
                  usartLayout->addWidget( UsartStatic047 ,54, 2);
                  usartLayout->addWidget( UsartStatic048 ,55, 2);
                  usartLayout->addWidget( UsartStatic049 ,56, 2);

                  usartLayout->addWidget( UsartStatic050 ,57, 2);
                  usartLayout->addWidget( UsartStatic051 ,58, 2);
                  usartLayout->addWidget( UsartStatic052 ,59, 2);
                  usartLayout->addWidget( UsartStatic053 ,60, 2);
                  usartLayout->addWidget( UsartStatic054 ,61, 2);
                  usartLayout->addWidget( UsartStatic055 ,62, 2);*/



//*****************************************************************************//
//****************************  scroll area I2C     ***************************//
//*****************************************************************************//



                QScrollArea *scrollAreaI2c =new QScrollArea ;
                scrollAreaI2c->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                scrollAreaI2c->setWidgetResizable( true );
                scrollAreaI2c->setGeometry( 5, 5, 695, 895 );


                QWidget *widgetI2c = new QWidget;

                scrollAreaI2c->setWidget( widgetI2c );


                widgetI2c->setLayout( i2cLayout );

                                      /* ... */
//*****************************************************************************//
//****************************  scroll area Spi     ***************************//
//*****************************************************************************//



                QScrollArea *scrollAreaSpi =new QScrollArea ;
               scrollAreaSpi->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                scrollAreaSpi->setWidgetResizable( true );
                scrollAreaSpi->setGeometry( 5, 5, 695, 895 );


                QWidget *widgetSpi = new QWidget;

                scrollAreaSpi->setWidget( widgetSpi );


                widgetSpi->setLayout( spiLayout );

                                      /* ... */


//*****************************************************************************//
//****************************  scroll area Can     ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaCan =new QScrollArea ;
           scrollAreaCan->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaCan->setWidgetResizable( true );
            scrollAreaCan->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetCan = new QWidget;

            scrollAreaCan->setWidget( widgetCan );


            widgetCan->setLayout( canLayout );

                                  /* ... */

//*****************************************************************************//
//****************************  scroll area FdCan     ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaFdCan =new QScrollArea ;
           scrollAreaFdCan->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaFdCan->setWidgetResizable( true );
            scrollAreaFdCan->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetFdCan = new QWidget;

            scrollAreaFdCan->setWidget( widgetCan );


            widgetFdCan->setLayout( fdCanLayout );

                                  /* ... */

//*****************************************************************************//
//****************************      TAB            ****************************//
//*****************************************************************************//
          QTabWidget *Tab= new QTabWidget(this);
          Tab->setGeometry(5,5,995, 835);
          Tab->addTab(scrollAreaPlateform, "PLateform");
          Tab->addTab(scrollAreaUsart, "Usart");
          Tab->addTab(scrollAreaI2c, "I2C");
          Tab->addTab(new QScrollArea(this), "SPI");
          Tab->addTab(new QScrollArea(this), "CAN");
          Tab->addTab(new QScrollArea(this), "FD_CAN");









}

void Dialog::ADDMemory()
{

    QLabel *Line1Name = new QLabel(this);
    Line1Name->setGeometry(QRect(QPoint(30, 10),QSize(121, 21)));
    Line1Name->setText("Name :");


    QFont fontLineName;//( "MS Shell Dlg 2", 12, QFont::Bold);
    fontLineName.setFamily("MS Shell Dlg 2");
    fontLineName.setPointSize(12);
    fontLineName.setBold(true);
    Line1Name->setFont(fontLineName);

    QLineEdit *Connect=new QLineEdit(this);
    linememory.push_back(Connect);




    QLabel *Line2Start = new QLabel(this);
    Line2Start->setGeometry(QRect(QPoint(30, 10),QSize(121, 21)));
    Line2Start->setText("Start :");


    QFont fontLineStart;//( "MS Shell Dlg 2", 12, QFont::Bold);
    fontLineStart.setFamily("MS Shell Dlg 2");
    fontLineStart.setPointSize(12);
    fontLineStart.setBold(true);
    Line2Start->setFont(fontLineStart);

    QLineEdit *Start=new QLineEdit(this);
    linememory.push_back(Start);



    QLabel *Line3End = new QLabel(this);
    Line3End->setGeometry(QRect(QPoint(30, 10),QSize(121, 21)));
    Line3End->setText("End :");


    QFont fontLineEnd;//( "MS Shell Dlg 2", 12, QFont::Bold);
    fontLineEnd.setFamily("MS Shell Dlg 2");
    fontLineEnd.setPointSize(12);
    fontLineEnd.setBold(true);
    Line3End->setFont(fontLineEnd);

    QLineEdit *End=new QLineEdit(this);
    linememory.push_back(End);

    gridLayout->addWidget(Line1Name,++i, 0);
    gridLayout->addWidget( Connect ,i, 1);


    gridLayout->addWidget( Start ,i, 3);
    gridLayout->addWidget(Line2Start,i, 2);

    gridLayout->addWidget( End ,i, 5);
    gridLayout->addWidget(Line3End,i, 4);



}

void Dialog::handleButton()
 {

    Json::Value ALLjsonData;
    std::ofstream jsonFile;


    //***************platform***************//
    if(QPlatform->currentText() == "Cli")
    {
        ALLjsonData["plateform"][0]["Mode"]="Cli";
    }

    else if(QPlatform->currentText() == "Automated")
    {
        ALLjsonData["plateform"][0]["Mode"]="Automated";
    }


    UsartSt=lineUsartSt->text();
    UsartDt=lineUsartDt->text();


    ALLjsonData["plateform"][1]["Usart_ST"]=UsartSt.toLocal8Bit().constData();
    ALLjsonData["plateform"][2]["Usart_DT"]=UsartDt.toLocal8Bit().constData();

    //***************Target***************//
    STlink=lineSTLINK->text();
    ALLjsonData["target"][0]["STLink_SN"]=STlink.toLocal8Bit().constData();


    //***************blSpecific***************//

    if(comboBoxBlSpecificConnect->currentText() == "true")
    {
        ALLjsonData["bl_specific"][0]["connect"]="true";
    }

    if(comboBoxBlSpecificConnect->currentText() == "false")
    {
        ALLjsonData["bl_specific"][0]["connect"]="false";
    }


    if(comboBoxBlSpecificSupportMe->currentText() == "true")
    {
        ALLjsonData["bl_specific"][1]["support_ME"]="true";
    }

    if(comboBoxBlSpecificSupportMe->currentText() == "false")
    {
        ALLjsonData["bl_specific"][1]["support_ME"]="false";
    }


    if(comboBoxBlSpecificSupportBe->currentText() == "true")
    {
        ALLjsonData["bl_specific"][2]["support_BE"]="true";
    }

    if(comboBoxBlSpecificSupportBe->currentText() == "false")
    {
        ALLjsonData["bl_specific"][2]["support_BE"]="false";
    }
    //***************blData***************//
    DeviceId=blDataDeviceId->text();
    ALLjsonData["bl-data"][0]["device_id"]=DeviceId.toLocal8Bit().constData();

    i2cblVersion=blDataI2cBlVersion->text();
    ALLjsonData["bl-data"][1]["i2c_bl_version"]=i2cblVersion.toLocal8Bit().constData();

    spiBlVersion=blDataSpiBlVersion->text();
    ALLjsonData["bl-data"][2]["spi_bl_version"]=spiBlVersion.toLocal8Bit().constData();

    usartBlversion=blDataUsartBlVersion->text();
    ALLjsonData["bl-data"][3]["usart_bl_version"]=usartBlversion.toLocal8Bit().constData();

    fdCanBlversion=blDataFdCanBlVersion->text();
    ALLjsonData["bl-data"][4]["fd_can_bl_version"]=fdCanBlversion.toLocal8Bit().constData();

    usbBlVersion=blDataUsbBlVersion->text();
    ALLjsonData["bl-data"][5]["usb_bl_version"]=usbBlVersion.toLocal8Bit().constData();

    fWBlVersion=blDataFwBlVersion->text();
    ALLjsonData["bl-data"][6]["fw_bl_version"]=fWBlVersion.toLocal8Bit().constData();

    blRamSize=blDataBlRamSize->text();
    ALLjsonData["bl-data"][7]["bl_ram_size"]=blRamSize.toLocal8Bit().constData();

    canBlversion=blDataCanBlVersion->text();
    ALLjsonData["bl-data"][8]["can_bl_version"]=canBlversion.toLocal8Bit().constData();
    //***************memory***************//

    for(int j=0;j< linememory.size();j++)
    {
       if (j % 3==0 ||j % 3==3 )
       ALLjsonData["memory"][j]["connect"]= (linememory[j])->text().toLocal8Bit().constData();
       if (j % 3==1 )
       ALLjsonData["memory"][j]["start"]= (linememory[j])->text().toLocal8Bit().constData();
       if (j % 3==2 )
       ALLjsonData["memory"][j]["end"]= (linememory[j])->text().toLocal8Bit().constData();
    }

    //***************Usart***************//


    ALLjsonData["interfaces"][0]["Name"]= lineUsartName->text().toLocal8Bit().constData();
    if(BaudrateUsart->currentText() == "9600")
    {
        ALLjsonData["interfaces"][0]["Baudrate"]="9600";
    }
    if(BaudrateUsart->currentText() == "115200")
    {
        ALLjsonData["interfaces"][0]["Baudrate"]="115200";
    }
    ALLjsonData["interfaces"][0]["COM"]= lineUsartCom->text().toLocal8Bit().constData();
    ALLjsonData["interfaces"][0]["Driver"]= lineUsartDriver->text().toLocal8Bit().constData();
    ALLjsonData["interfaces"][0]["Static"]= lineUsartStatic->text().toLocal8Bit().constData();
    ALLjsonData["interfaces"][0]["Dynamic"]= lineUsartDynamic->text().toLocal8Bit().constData();







    //***************Save***************//
    jsonFile.open("C:/MEDBOUSSELMI/Plateform.json");
    Json::StyledWriter styledWriter;
    jsonFile << styledWriter.write(ALLjsonData);
    jsonFile.close();
    QMessageBox::information(this,"done","File successful generate");

 }

Dialog::~Dialog()
{
    delete ui;
}
