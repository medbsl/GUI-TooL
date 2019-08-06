#include "read.h"
#include "ui_read.h"
#include <fstream>
#include <QDebug>
#include "mainwindow.h"


unsigned int counterRequirement =0;
unsigned int counterStatic =0;
unsigned int counterDynamic =0;
bool newfile =false;
int index =0;

Read::Read(QWidget *parent, QString filename,bool newFile) : QDialog(parent), ui(new Ui::Read){

    newfile =newFile;
    ui->setupUi(this);
    
    onBrowseButton(filename);




//*****************************************************************************//
//****************************  scroll area         ***************************//
//*****************************************************************************//



            QScrollArea *scrollArea =new QScrollArea ;
            scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollArea->setWidgetResizable( true );
            scrollArea->setGeometry( 5, 5, 695, 895 );


            QWidget *widget = new QWidget;

            scrollArea->setWidget( widget );


            widget->setLayout( layout );

//*****************************************************************************//
//****************************  scroll area Usart   ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaUsart =new QScrollArea ;
            scrollAreaUsart->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaUsart->setWidgetResizable( true );
            scrollAreaUsart->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetUsart = new QWidget;

            scrollAreaUsart->setWidget( widgetUsart );
            widgetUsart->setLayout( layoutUsart );

//*****************************************************************************//
//****************************  scroll area SPI     ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaSPI =new QScrollArea ;
            scrollAreaSPI->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaSPI->setWidgetResizable( true );
            scrollAreaSPI->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetSpi = new QWidget;

            scrollAreaSPI->setWidget( widgetSpi );
            widgetSpi->setLayout( layoutSpi );


//*****************************************************************************//
//****************************  scroll area I2C    ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaI2C =new QScrollArea ;
            scrollAreaI2C->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaI2C->setWidgetResizable( true );
            scrollAreaI2C->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetI2c = new QWidget;

            scrollAreaI2C->setWidget( widgetI2c );
            widgetI2c->setLayout( layoutI2C );

//*****************************************************************************//
//****************************  scroll area USB    ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaUSB =new QScrollArea ;
            scrollAreaUSB->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaUSB->setWidgetResizable( true );
            scrollAreaUSB->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetUsb = new QWidget;

            scrollAreaUSB->setWidget( widgetUsb );
            widgetUsb->setLayout( layoutUSB );


//*****************************************************************************//
//****************************  scroll area CAN     ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaCan =new QScrollArea ;
            scrollAreaCan->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaCan->setWidgetResizable( true );
            scrollAreaCan->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetCan = new QWidget;

            scrollAreaCan->setWidget( widgetCan );
            widgetCan->setLayout( layoutCAN );


//*****************************************************************************//
//****************************  scroll area FDCAN     ***************************//
//*****************************************************************************//



            QScrollArea *scrollAreaFdCan =new QScrollArea ;
            scrollAreaFdCan->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            scrollAreaFdCan->setWidgetResizable( true );
            scrollAreaFdCan->setGeometry( 5, 5, 695, 895 );


            QWidget *widgetFdCan = new QWidget;

            scrollAreaFdCan->setWidget( widgetFdCan );
            widgetFdCan->setLayout( layoutFDCAN );





//*****************************************************************************//
//****************************      TAB            ****************************//
//*****************************************************************************//
              QTabWidget *Tab= new QTabWidget(this);
              Tab->setGeometry(5,5,995, 835);
              Tab->addTab(scrollArea, "PLateform");
              Tab->addTab(scrollAreaUsart, "Usart");
              Tab->addTab(scrollAreaSPI, "SPI");
              Tab->addTab(scrollAreaI2C, "I2C");
              Tab->addTab(scrollAreaUSB, "USB");
              Tab->addTab(scrollAreaCan, "CAN");
              Tab->addTab(scrollAreaFdCan, "FD_CAN");


//*****************************************************************************//
//****************************    Generate Button   ***************************//
//*****************************************************************************//


// PushButton
    QHBoxLayout* layoutButton = new QHBoxLayout( this );
    layoutButton->setContentsMargins(0,0,0,0);
    m_button = new QPushButton("Save changes", this);
    m_button->setGeometry(QRect(QPoint(845, 855),QSize(150, 50)));
    connect(m_button,SIGNAL (clicked()), this, SLOT(onSaveChanegeButton()));


}

Read::~Read()
{
    delete ui;
    staticTest.clear();
    DynamicTest.clear();
    Requirement.clear();
}

void Read::onBrowseButton(QString filename){


    unsigned int s=0;


   std::ifstream JSONFILE(filename.toLocal8Bit().constData(), std::ifstream::binary);


   JSONFILE >> JSON;
   member= JSON.getMemberNames();


    for (unsigned int i = 0; i < member.size(); i++) {
        for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){

         if (member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests" &&
             member[i] !="SPI_static_tests" && member[i] !="SPI_dynamic_tests" &&
                 member[i] !="I2C_static_tests" && member[i] !="I2C_dynamic_tests" &&
                 member[i] !="CAN_static_tests" && member[i] !="CAN_dynamic_tests" &&
                 member[i] !="FDCAN_static_tests" && member[i] !="FDCAN_dynamic_tests" &&
                 member[i] !="USB_static_tests" && member[i] !="USB_dynamic_tests"



                               &&member[i] !="interfaces"){





             //label of member
            label = newLabel(QString::fromStdString(member[i]));
            //layout->addWidget(label, ++s,0);



             for (unsigned int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){



                 // Label
                   Label = newSubLabel(QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]));
                  // layout->addWidget(Label, ++s,0);

                 if (JSON[member[i]][j].getMemberNames()[k] == "connect"){

                     QComboBox *combo = new QComboBox( this );
                     combo->setEditable( false );
                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                     combo->addItem(tr("true"));
                     combo->addItem(tr("false"));
                   //  layout->addWidget(combo, s,1);

                     valueCombo.push_back(combo);
                     value.push_back(NULL);
                     break;
                 }
                 if (JSON[member[i]][j].getMemberNames()[k] == "supprot_ME"){

                     QComboBox *combo = new QComboBox( this );
                     combo->setEditable( false );
                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                     combo->addItem(tr("true"));
                     combo->addItem(tr("false"));
                  //   layout->addWidget(combo, s,1);

                     valueCombo.push_back(combo);
                     value.push_back(NULL);
                     break;
                 }
                 if (JSON[member[i]][j].getMemberNames()[k] == "supprot_BE"){

                     QComboBox *combo = new QComboBox( this );
                     combo->setEditable( false );
                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                     combo->addItem(tr("true"));
                     combo->addItem(tr("false"));
                  //   layout->addWidget(combo, s,1);

                     valueCombo.push_back(combo);
                     value.push_back(NULL);
                     break;
                 }
                 if (JSON[member[i]][j].getMemberNames()[k] == "Mode"){

                     QComboBox *combo = new QComboBox( this );
                     combo->setEditable( false );
                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                     combo->addItem(tr("Cli"));
                     combo->addItem(tr("Automated"));
                  //   layout->addWidget(combo, s,1);

                     valueCombo.push_back(combo);
                     value.push_back(NULL);
                     break;
                 }
                 else {
                     // Line Edit

                         lineEdit = new QLineEdit(this);
                         lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                         lineEdit->setText(QString::fromStdString(JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k] ].asString()));
                      //   layout->addWidget(lineEdit, s,1);
                         valueCombo.push_back(NULL);
                         value.push_back(lineEdit);

                 }















                   }
        }





         else if (member[i] == "interfaces" && JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "I2C"){

                  s=0;
                            QCheckBox *valide = new QCheckBox("I2C",this);
                                    if (JSON["interfaces"][0]["testcheck" ].asString()== "ON")
                                        valide->setChecked(1);
                                    else
                                        valide->setChecked(0);

                                    interfaces.push_back(valide);
                                    layoutI2C->addWidget(valide,s,0);
                             for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                                 if(JSON["interfaces"][j].getMemberNames()[k]== "testcheck" ) break;
                                 // Label

                                 Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                    layoutI2C->addWidget(Label, ++s,0);

                                 if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                     QComboBox *combo = new QComboBox( this );
                                     combo->setEditable( false );
                                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                     combo->addItem(tr("115200"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("38400"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("19200"));
                                     combo->addItem(tr("9600"));
                                     layoutI2C->addWidget(combo, s,1);

                                     valueI2CCombo.push_back(combo);
                                     valueI2C.push_back(NULL);

                                 }





                                   else {                                  // Line Edit

                                     lineEdit = new QLineEdit(this);
                                     lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                     lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                                     layoutI2C->addWidget(lineEdit, s,1);

                                     valueI2CCombo.push_back(NULL);
                                     valueI2C.push_back(lineEdit);
   }





                             }
                       if(JSON["I2C_static_tests"] != 0){




                                QLabel *labelBlData = newLabel("Static :");
                                layoutI2C->addWidget(labelBlData,++s,0);


                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutI2C->addWidget(labelDynamic,s,1);

                                QLabel *labelRequirement = newLabel("Requirement :");
                                layoutI2C->addWidget(labelRequirement,s,2);


                                        //Read::Test(layoutUsart, ++s);
                                        QPushButton *checkAllTestStatic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                                        layoutI2C->addWidget(checkAllTestStatic,s,0);

                                        QPushButton *checkAllTestDynamic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                                        layoutI2C->addWidget(checkAllTestDynamic,s,1);

                                        QPushButton *checkAllTestReq =new QPushButton("Select ALL",this);
                                        connect(checkAllTestReq,SIGNAL (clicked()), this, SLOT(onCheckAllTestReq()));
                                        layoutI2C->addWidget(checkAllTestReq,s++,2);

                               /* ************************  Static  *********************/
                            for (unsigned int j = 0; j < JSON["I2C_static_tests"].size()  ; j++){



                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_static_tests"][j][JSON["I2C_static_tests"][j].getMemberNames()[1]].asString()) ,this);

                                    if( JSON["I2C_static_tests"][j]["testcheck"].asString() == "ON" )
                                           box->setChecked(1);
                                    if(JSON["I2C_static_tests"][j]["testcheck"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutI2C->addWidget(box,++s,0);
                                    staticTestI2C.push_back(box);


                       }
                               /* ************************  Dynamic   *********************/
                                           s-= staticTestI2C.size();
                            for (unsigned int j = 0; j < JSON["I2C_dynamic_tests"].size()  ; j++){


                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_dynamic_tests"][j][JSON["I2C_dynamic_tests"][j].getMemberNames()[1]].asString()) ,this);

                                if( JSON["I2C_dynamic_tests"][j]["testcheck"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["I2C_dynamic_tests"][j]["testcheck"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutI2C->addWidget(box,++s,1);
                                DynamicTestI2C.push_back(box);



                       }




                       }


   }


         else if (member[i] == "interfaces" && JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "SPI"){

                  s=0;
                            QCheckBox *valide = new QCheckBox("SPI",this);
                                    if (JSON["interfaces"][0]["testcheck"  ].asString()== "ON")
                                        valide->setChecked(1);
                                    else
                                        valide->setChecked(0);

                                    interfaces.push_back(valide);
                                    layoutSpi->addWidget(valide,s,0);
                             for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                                 if(JSON["interfaces"][j].getMemberNames()[k]== "testcheck" ) break;
                                 // Label

                                 Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                    layoutSpi->addWidget(Label, ++s,0);

                                 if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                     QComboBox *combo = new QComboBox( this );
                                     combo->setEditable( false );
                                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                     combo->addItem(tr("115200"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("38400"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("19200"));
                                     combo->addItem(tr("9600"));
                                     layoutSpi->addWidget(combo, s,1);

                                     valueSpiCombo.push_back(combo);
                                     valueSpi.push_back(NULL);

                                 }





                                   else {                                  // Line Edit

                                     lineEdit = new QLineEdit(this);
                                     lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                     lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                                     layoutSpi->addWidget(lineEdit, s,1);

                                     valueSpiCombo.push_back(NULL);
                                     valueSpi.push_back(lineEdit);
   }





                             }
                       if(JSON["SPI_static_tests"] != 0){




                                QLabel *labelBlData = newLabel("Static :");
                                layoutSpi->addWidget(labelBlData,++s,0);


                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutSpi->addWidget(labelDynamic,s,1);

                                QLabel *labelRequirement = newLabel("Requirement :");
                                layoutSpi->addWidget(labelRequirement,s,2);


                                        //Read::Test(layoutUsart, ++s);
                                        QPushButton *checkAllTestStatic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                                        layoutSpi->addWidget(checkAllTestStatic,s,0);

                                        QPushButton *checkAllTestDynamic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                                        layoutSpi->addWidget(checkAllTestDynamic,s,1);

                                        QPushButton *checkAllTestReq =new QPushButton("Select ALL",this);
                                        connect(checkAllTestReq,SIGNAL (clicked()), this, SLOT(onCheckAllTestReq()));
                                        layoutSpi->addWidget(checkAllTestReq,s++,2);

                               /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["SPI_static_tests"].size()  ; j++){



                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_static_tests"][j][JSON["SPI_static_tests"][j].getMemberNames()[1]].asString()) ,this);

                                    if( JSON["SPI_static_tests"][j]["testcheck"].asString() == "ON" )
                                           box->setChecked(1);
                                    if(JSON["SPI_static_tests"][j]["testcheck"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutSpi->addWidget(box,++s,0);
                                    staticTestSpi.push_back(box);


                       }
                               /* ************************  Dynamic   **********************/
                                           s-= staticTestSpi.size();
                            for (unsigned int j = 0; j < JSON["SPI_dynamic_tests"].size()  ; j++){


                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_dynamic_tests"][j][JSON["SPI_dynamic_tests"][j].getMemberNames()[1]].asString()) ,this);

                                if( JSON["SPI_dynamic_tests"][j]["testcheck"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["SPI_dynamic_tests"][j]["testcheck"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutSpi->addWidget(box,++s,1);
                                DynamicTestSpi.push_back(box);



                       }




                       }


   }




         else if (member[i] == "interfaces" && JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[4] ].asString() == "USART"){
 s=0;
                     QCheckBox *valide = new QCheckBox("USART",this);
                             if (JSON["interfaces"][j]["testcheck"  ].asString()== "ON")
                                 valide->setChecked(1);
                             else
                                 valide->setChecked(0);

                             interfaces.push_back(valide);
                             layoutUsart->addWidget(valide,s,0);
                             for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                                 // Label
                                if(JSON["interfaces"][j].getMemberNames()[k]== "testcheck" ) break;
                                 Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                    layoutUsart->addWidget(Label, ++s,0);

                                 if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                     QComboBox *combo = new QComboBox( this );
                                     combo->setEditable( false );
                                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                     combo->addItem(tr("115200"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("38400"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("19200"));
                                     combo->addItem(tr("9600"));
                                     layoutUsart->addWidget(combo, s,1);

                                     valueUsartCombo.push_back(combo);
                                     valueUsart.push_back(NULL);

                                 }





                                   else {                                  // Line Edit

                                     lineEdit = new QLineEdit(this);
                                     lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                     lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                                     layoutUsart->addWidget(lineEdit, s,1);

                                     valueUsartCombo.push_back(NULL);
                                     valueUsart.push_back(lineEdit);
   }





                             }
                       if(JSON["USART_static_tests"] != 0){




                                QLabel *labelBlData = newLabel("Static :");
                                layoutUsart->addWidget(labelBlData,++s,0);


                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutUsart->addWidget(labelDynamic,s,1);

                                QLabel *labelRequirement = newLabel("Requirement :");
                                layoutUsart->addWidget(labelRequirement,s,2);


                                        //Read::Test(layoutUsart, ++s);
                                        QPushButton *checkAllTestStatic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                                        layoutUsart->addWidget(checkAllTestStatic,s,0);

                                        QPushButton *checkAllTestDynamic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                                        layoutUsart->addWidget(checkAllTestDynamic,s,1);

                                        QPushButton *checkAllTestReq =new QPushButton("Select ALL",this);
                                        connect(checkAllTestReq,SIGNAL (clicked()), this, SLOT(onCheckAllTestReq()));
                                        layoutUsart->addWidget(checkAllTestReq,s++,2);

                               /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){


                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_static_tests"][j][JSON["USART_static_tests"][j].getMemberNames()[1]].asString()) ,this);

                                    if( JSON["USART_static_tests"][j]["testcheck"].asString() == "ON" )
                                           box->setChecked(1);
                                    if(JSON["USART_static_tests"][j]["testcheck"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutUsart->addWidget(box,++s,0);
                                    staticTest.push_back(box);


                       }
                               /* ************************  Dynamic   **********************/
                                           s-= staticTest.size();
                            for (unsigned int j = 0; j < JSON["USART_dynamic_tests"].size()  ; j++){


                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_dynamic_tests"][j][JSON["USART_dynamic_tests"][j].getMemberNames()[1]].asString()) ,this);

                                if( JSON["USART_dynamic_tests"][j]["testcheck"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["USART_dynamic_tests"][j]["testcheck"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutUsart->addWidget(box,++s,1);
                                DynamicTest.push_back(box);



                       }




                       }


   }





         else if (member[i] == "interfaces" && JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[1] ].asString() == "USB"){

                  s=0;
                            QCheckBox *valide = new QCheckBox("USB",this);
                                    if (JSON["interfaces"][0]["testcheck"  ].asString()== "ON")
                                        valide->setChecked(1);
                                    else
                                        valide->setChecked(0);

                                    interfaces.push_back(valide);
                                    layoutUSB->addWidget(valide,s,0);
                             for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                                 if(JSON["interfaces"][j].getMemberNames()[k]== "testcheck" ) break;
                                 // Label

                                 Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                    layoutUSB->addWidget(Label, ++s,0);

                                 if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                     QComboBox *combo = new QComboBox( this );
                                     combo->setEditable( false );
                                     combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                     combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                     combo->addItem(tr("115200"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("38400"));
                                     combo->addItem(tr("57600"));
                                     combo->addItem(tr("19200"));
                                     combo->addItem(tr("9600"));
                                     layoutUSB->addWidget(combo, s,1);

                                     valueUSBCombo.push_back(combo);
                                     valueUSB.push_back(NULL);

                                 }





                                   else {                                  // Line Edit

                                     lineEdit = new QLineEdit(this);
                                     lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                     lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                                     layoutUSB->addWidget(lineEdit, s,1);

                                     valueUSBCombo.push_back(NULL);
                                     valueUSB.push_back(lineEdit);
   }





                             }
                       if(JSON["USB_static_tests"] != 0){




                                QLabel *labelBlData = newLabel("Static :");
                                layoutUSB->addWidget(labelBlData,++s,0);


                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutUSB->addWidget(labelDynamic,s,1);

                                QLabel *labelRequirement = newLabel("Requirement :");
                                layoutUSB->addWidget(labelRequirement,s,2);


                                        //Read::Test(layoutUsart, ++s);
                                        QPushButton *checkAllTestStatic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                                        layoutUSB->addWidget(checkAllTestStatic,s,0);

                                        QPushButton *checkAllTestDynamic =new QPushButton("Select ALL",this);
                                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                                        layoutUSB->addWidget(checkAllTestDynamic,s,1);

                                        QPushButton *checkAllTestReq =new QPushButton("Select ALL",this);
                                        connect(checkAllTestReq,SIGNAL (clicked()), this, SLOT(onCheckAllTestReq()));
                                        layoutUSB->addWidget(checkAllTestReq,s++,2);

                               /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["USB_static_tests"].size()  ; j++){



                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_static_tests"][j][JSON["USB_static_tests"][j].getMemberNames()[1]].asString()) ,this);

                                    if( JSON["USB_static_tests"][j]["testcheck"].asString() == "ON" )
                                           box->setChecked(1);
                                    if(JSON["USB_static_tests"][j]["testcheck"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutUSB->addWidget(box,++s,0);
                                    staticTestUSB.push_back(box);


                       }
                               /* ************************  Dynamic   **********************/
                                           s-= staticTestUSB.size();
                            for (unsigned int j = 0; j < JSON["USB_dynamic_tests"].size()  ; j++){


                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_dynamic_tests"][j][JSON["USB_dynamic_tests"][j].getMemberNames()[1]].asString()) ,this);

                                if( JSON["USB_dynamic_tests"][j]["testcheck"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["USB_dynamic_tests"][j]["testcheck"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutUSB->addWidget(box,++s,1);
                                DynamicTestUSB.push_back(box);



                       }




                       }


   }










    }
    }

   Affiche();
   }



void Read::onSaveChanegeButton(){


int f=0;
int U=0;
/*int ordreJSON =0;
int ordreJSON1=0;*/




     for (unsigned int i = 0; i < member.size(); i++) {

        if (member[i] == "USART_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTest.size();j++){

              if (DynamicTest[j]->checkState() == Qt::Checked){


                    JSON["USART_dynamic_tests"][j]["testcheck"]= "ON";

                }
              else if(DynamicTest[j]->checkState() == Qt::Unchecked){
                  JSON["USART_dynamic_tests"][j]["testcheck"]= "OFF";
              }
              }
          }




        if (member[i] == "USART_static_tests" ){
            for (unsigned int j=0; j < staticTest.size() ;j++){

              if ( staticTest[j]->checkState() == Qt::Checked ){
                  JSON["USART_static_tests"][j]["testcheck"]= "ON";


              }

              else if(staticTest[j]->checkState() == Qt::Unchecked){
                  JSON["USART_static_tests"][j]["testcheck"]= "OFF";
              }

              }

              }





        if (member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests"&& member[i] !="interfaces"){
                for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){
                     for (unsigned int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){



                if (value[f] != NULL)
                JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] =value[f++]->text().toLocal8Bit().constData();

                else{
                    if(valueCombo[f]->currentText() == "true")
                    {
                        JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="true";
                        f++;
                        break;
                    }

                    if(valueCombo[f]->currentText() == "false")
                    {
                       JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="false";
                       f++;
                       break;
                    }

                    if(valueCombo[f]->currentText() == "Cli")
                    {
                        JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="Cli";
                        f++;
                        break;
                    }

                    if(valueCombo[f]->currentText() == "Automated")
                    {
                       JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="Automated";
                       f++;
                       break;
                    }
                }








                    }
                }



        }




}


     for (unsigned int k = 0; k < JSON["interfaces"][0].getMemberNames().size(); k++){




         if (valueUsart[U] != NULL)
             JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k] ] =valueUsart[U++]->text().toLocal8Bit().constData();


         else if(valueUsartCombo[U] != NULL) {

             switch (valueUsartCombo[U]->currentText().toInt()) {
             case 9600:
                 JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]] ="9600";
                 U++;
                 break;


             case 19200:
                 JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]] ="9600";
                 U++;
                 break;


             case 38400:
                 JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]] ="38400";
                 U++;
                 break;


             case 57600:
                 JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]] ="57600";
                 U++;
                 break;


             case 115200:
                 JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]] ="115200";
                 U++;
                 break;
             default:
                 break;
             }

         }


         }
     if(Mandatory()){
         //***************Save***************//
         for(unsigned int i=0; i< value.size();i++)
             if(value[i]!= NULL && value[i]->text() != "")
                 value[i]->setStyleSheet("");

          if(newfile){

              QString NewfileName = QFileDialog::getSaveFileName(this,tr("browse"), filename, "json File(*.json)");
              std::ofstream JSONFILE;
              JSONFILE.open(NewfileName.toLocal8Bit().constData());
              Json::StyledWriter styledWriter;
              JSONFILE << styledWriter.write(JSON);
              JSONFILE.close();
              QMessageBox::information(this,"Done","New File successful created");
          }
          else if(!newfile){
              std::ofstream JSONFILE;
              JSONFILE.open(filename.toLocal8Bit().constData());
              Json::StyledWriter styledWriter;
              JSONFILE << styledWriter.write(JSON);
              JSONFILE.close();
              QMessageBox::information(this,"done","File successful edited");
          }

     }
     else {
         //*************** Return to edit ***************//
         QMessageBox::warning(this,"Warning","some field are empty");
     }

}

void Read::onCheckAllTestReq(){


    for (unsigned int i=0; i< Requirement.size();i++){
        if (counterRequirement==0)
        {
            Requirement[i]->setCheckState(Qt::Checked);
            Requirement[i]->clicked(true);
        }


        else{

            Requirement[i]->setCheckState(Qt::Unchecked);
           Requirement[i]->clicked(true);
        }

         }

    counterRequirement= 1- counterRequirement;

}

void Read::onCheckAllTestDynamic(){



    for (unsigned int i=0; i< DynamicTest.size();i++){
        if (counterDynamic==0)
        DynamicTest[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTest[i]->setCheckState(Qt::Checked);
         }

    counterDynamic= 1-counterDynamic;

}

void Read::onCheckAllTestStatic(){


    for (unsigned int i=0; i< staticTest.size();i++){
        if (counterStatic==0)
        staticTest[i]->setCheckState(Qt::Unchecked);
        else
            staticTest[i]->setCheckState(Qt::Checked);
         }

    counterStatic= 1-counterStatic;

}

void Read::requirement(){
//toujour i-1


    if (Requirement[0]->checkState() == Qt::Checked)
    {
            staticTest[4 -1]->setChecked(1);
            staticTest[5 -1]->setChecked(1);
            DynamicTest[1 -1]->setChecked(1);
    }
    if (Requirement[0]->checkState() == Qt::Unchecked)
    {
            staticTest[4 -1]->setChecked(0);
            staticTest[5 -1]->setChecked(0);
            DynamicTest[1 -1]->setChecked(0);
    }

    if (Requirement[1]->checkState() == Qt::Checked)
    {
            staticTest[1 -1]->setChecked(1);
            staticTest[2 -1]->setChecked(1);
            staticTest[3 -1]->setChecked(1);
    }
    if (Requirement[1]->checkState() == Qt::Unchecked)
    {
            staticTest[1 -1]->setChecked(0);
            staticTest[2 -1]->setChecked(0);
            staticTest[3 -1]->setChecked(0);
    }

    if (Requirement[2]->checkState() == Qt::Checked)
    {

            DynamicTest[2 -1]->setChecked(1);

    }
    if (Requirement[2]->checkState() == Qt::Unchecked)
    {
            DynamicTest[2 -1]->setChecked(0);
    }

    if (Requirement[3]->checkState() == Qt::Checked)
    {
            staticTest[6 -1]->setChecked(1);
            staticTest[7 -1]->setChecked(1);
            DynamicTest[3 -1]->setChecked(1);
    }
    if (Requirement[3]->checkState() == Qt::Unchecked)
    {
         staticTest[6 -1]->setChecked(0);
         staticTest[7 -1]->setChecked(0);
        DynamicTest[3 -1]->setChecked(0);
    }

    if (Requirement[4]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);
            DynamicTest[16 -1]->setChecked(1);
            DynamicTest[17 -1]->setChecked(1);
    }
    if (Requirement[4]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);
       DynamicTest[16 -1]->setChecked(0);
       DynamicTest[17 -1]->setChecked(0);
    }
    if (Requirement[5]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);
            DynamicTest[18 -1]->setChecked(1);

    }
    if (Requirement[5]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);
       DynamicTest[18 -1]->setChecked(0);

    }

    if (Requirement[6]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);


    }
    if (Requirement[6]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);


    }

    if (Requirement[7]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);


    }
    if (Requirement[7]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);


    }
    if (Requirement[8]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);


    }
    if (Requirement[8]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);


    }
    if (Requirement[9]->checkState() == Qt::Checked)
    {
             staticTest[21 -1]->setChecked(1);
             staticTest[22 -1]->setChecked(1);
             staticTest[23 -1]->setChecked(1);
             staticTest[24 -1]->setChecked(1);
             staticTest[25 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[26 -1]->setChecked(1);
             staticTest[27 -1]->setChecked(1);
             staticTest[28 -1]->setChecked(1);
             DynamicTest[28 -1]->setChecked(1);


    }
    if (Requirement[9]->checkState() == Qt::Unchecked)
    {
        staticTest[21 -1]->setChecked(0);
        staticTest[22 -1]->setChecked(0);
        staticTest[23 -1]->setChecked(0);
        staticTest[24 -1]->setChecked(0);
        staticTest[25 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[26 -1]->setChecked(0);
        staticTest[27 -1]->setChecked(0);
        staticTest[28 -1]->setChecked(0);
        DynamicTest[28 -1]->setChecked(0);


    }

    if (Requirement[10]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);
             DynamicTest[16 -1]->setChecked(1);
             DynamicTest[17 -1]->setChecked(1);


    }
    if (Requirement[10]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);
       DynamicTest[16 -1]->setChecked(0);
       DynamicTest[17 -1]->setChecked(0);


    }

    if (Requirement[11]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);
             DynamicTest[18 -1]->setChecked(1);



    }
    if (Requirement[11]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);
       DynamicTest[18 -1]->setChecked(0);



    }

    if (Requirement[12]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);




    }
    if (Requirement[12]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);




    }

    if (Requirement[13]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);
             DynamicTest[27 -1]->setChecked(1);




    }
    if (Requirement[13]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);
        DynamicTest[27 -1]->setChecked(0);



    }

    if (Requirement[14]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);





    }
    if (Requirement[14]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);




    }

    if (Requirement[15]->checkState() == Qt::Checked)
    {
             staticTest[8 -1]->setChecked(1);
             staticTest[9 -1]->setChecked(1);
             staticTest[10 -1]->setChecked(1);
             staticTest[11 -1]->setChecked(1);
             staticTest[12 -1]->setChecked(1);
             staticTest[13 -1]->setChecked(1);
             staticTest[14 -1]->setChecked(1);
             staticTest[15 -1]->setChecked(1);





    }
    if (Requirement[15]->checkState() == Qt::Unchecked)
    {
         staticTest[8 -1]->setChecked(0);
         staticTest[9 -1]->setChecked(0);
        staticTest[10 -1]->setChecked(0);
        staticTest[11 -1]->setChecked(0);
        staticTest[12 -1]->setChecked(0);
        staticTest[13 -1]->setChecked(0);
        staticTest[14 -1]->setChecked(0);
        staticTest[15 -1]->setChecked(0);




    }
    if (Requirement[16]->checkState() == Qt::Checked)
    {
             staticTest[29 -1]->setChecked(1);
             staticTest[30 -1]->setChecked(1);
             staticTest[31 -1]->setChecked(1);
             staticTest[32 -1]->setChecked(1);
             staticTest[33 -1]->setChecked(1);
             staticTest[34 -1]->setChecked(1);
             staticTest[35 -1]->setChecked(1);
             staticTest[36 -1]->setChecked(1);
             staticTest[37 -1]->setChecked(1);
             staticTest[38 -1]->setChecked(1);
             staticTest[39 -1]->setChecked(1);
             staticTest[40 -1]->setChecked(1);
             staticTest[41 -1]->setChecked(1);

             DynamicTest[19 -1]->setChecked(1);
             DynamicTest[20 -1]->setChecked(1);



    }
    if (Requirement[16]->checkState() == Qt::Unchecked)
    {
        staticTest[29 -1]->setChecked(0);
        staticTest[30 -1]->setChecked(0);
        staticTest[31 -1]->setChecked(0);
        staticTest[32 -1]->setChecked(0);
        staticTest[33 -1]->setChecked(0);
        staticTest[34 -1]->setChecked(0);
        staticTest[35 -1]->setChecked(0);
        staticTest[36 -1]->setChecked(0);
        staticTest[37 -1]->setChecked(0);
        staticTest[38 -1]->setChecked(0);
        staticTest[39 -1]->setChecked(0);
        staticTest[40 -1]->setChecked(0);
        staticTest[41 -1]->setChecked(0);

        DynamicTest[19 -1]->setChecked(0);
        DynamicTest[20 -1]->setChecked(0);

    }
    if (Requirement[17]->checkState() == Qt::Checked)
    {
             staticTest[29 -1]->setChecked(1);
             staticTest[30 -1]->setChecked(1);
             staticTest[31 -1]->setChecked(1);
             staticTest[32 -1]->setChecked(1);
             staticTest[33 -1]->setChecked(1);
             staticTest[34 -1]->setChecked(1);
             staticTest[35 -1]->setChecked(1);
             staticTest[36 -1]->setChecked(1);
             staticTest[37 -1]->setChecked(1);
             staticTest[38 -1]->setChecked(1);
             staticTest[39 -1]->setChecked(1);
             staticTest[40 -1]->setChecked(1);
             staticTest[41 -1]->setChecked(1);





    }
    if (Requirement[17]->checkState() == Qt::Unchecked)
    {
        staticTest[29 -1]->setChecked(0);
        staticTest[30 -1]->setChecked(0);
        staticTest[31 -1]->setChecked(0);
        staticTest[32 -1]->setChecked(0);
        staticTest[33 -1]->setChecked(0);
        staticTest[34 -1]->setChecked(0);
        staticTest[35 -1]->setChecked(0);
        staticTest[36 -1]->setChecked(0);
        staticTest[37 -1]->setChecked(0);
        staticTest[38 -1]->setChecked(0);
        staticTest[39 -1]->setChecked(0);
        staticTest[40 -1]->setChecked(0);
        staticTest[41 -1]->setChecked(0);



    }

    if (Requirement[18]->checkState() == Qt::Checked)
    {
             staticTest[16 -1]->setChecked(1);
             staticTest[17 -1]->setChecked(1);
             staticTest[18 -1]->setChecked(1);
             staticTest[19 -1]->setChecked(1);
             staticTest[20 -1]->setChecked(1);


             DynamicTest[24 -1]->setChecked(1);




    }
    if (Requirement[18]->checkState() == Qt::Unchecked)
    {
        staticTest[16 -1]->setChecked(0);
        staticTest[17 -1]->setChecked(0);
        staticTest[18 -1]->setChecked(0);
        staticTest[19 -1]->setChecked(0);
        staticTest[20 -1]->setChecked(0);


        DynamicTest[24 -1]->setChecked(0);


    }


    if (Requirement[19]->checkState() == Qt::Checked)
    {
             staticTest[16 -1]->setChecked(1);
             staticTest[17 -1]->setChecked(1);
             staticTest[18 -1]->setChecked(1);
             staticTest[19 -1]->setChecked(1);
             staticTest[20 -1]->setChecked(1);


             DynamicTest[25 -1]->setChecked(1);




    }
    if (Requirement[19]->checkState() == Qt::Unchecked)
    {
        staticTest[16 -1]->setChecked(0);
        staticTest[17 -1]->setChecked(0);
        staticTest[18 -1]->setChecked(0);
        staticTest[19 -1]->setChecked(0);
        staticTest[20 -1]->setChecked(0);


        DynamicTest[25 -1]->setChecked(0);


    }

    if (Requirement[20]->checkState() == Qt::Checked)
    {
             staticTest[42 -1]->setChecked(1);
             staticTest[43 -1]->setChecked(1);
             staticTest[44 -1]->setChecked(1);
             staticTest[45 -1]->setChecked(1);
             staticTest[46 -1]->setChecked(1);


             DynamicTest[21 -1]->setChecked(1);




    }
    if (Requirement[20]->checkState() == Qt::Unchecked)
    {
        staticTest[42 -1]->setChecked(0);
        staticTest[43 -1]->setChecked(0);
        staticTest[44 -1]->setChecked(0);
        staticTest[45 -1]->setChecked(0);
        staticTest[46 -1]->setChecked(0);


        DynamicTest[21 -1]->setChecked(0);


    }

    if (Requirement[21]->checkState() == Qt::Checked)
    {
             staticTest[47 -1]->setChecked(1);
             staticTest[48 -1]->setChecked(1);
             staticTest[49 -1]->setChecked(1);








    }
    if (Requirement[21]->checkState() == Qt::Unchecked)
    {
        staticTest[47 -1]->setChecked(0);
        staticTest[48 -1]->setChecked(0);
        staticTest[49 -1]->setChecked(0);


    }

    if (Requirement[22]->checkState() == Qt::Checked)
    {
             DynamicTest[22 -1]->setChecked(1);


    }
    if (Requirement[22]->checkState() == Qt::Unchecked)
    {
                 DynamicTest[22 -1]->setChecked(0);


    }
    if (Requirement[23]->checkState() == Qt::Checked)
    {
             staticTest[50 -1]->setChecked(1);
             staticTest[51 -1]->setChecked(1);
             staticTest[52 -1]->setChecked(1);

             DynamicTest[22 -1]->setChecked(1);
             DynamicTest[23 -1]->setChecked(1);


    }
    if (Requirement[23]->checkState() == Qt::Unchecked)
    {
        staticTest[50 -1]->setChecked(0);
        staticTest[51 -1]->setChecked(0);
        staticTest[52 -1]->setChecked(0);

        DynamicTest[22 -1]->setChecked(0);
        DynamicTest[23 -1]->setChecked(0);


    }

    if (Requirement[24]->checkState() == Qt::Checked)
    {
             staticTest[53 -1]->setChecked(1);
             staticTest[54 -1]->setChecked(1);
             staticTest[55 -1]->setChecked(1);


             DynamicTest[23 -1]->setChecked(1);


    }
    if (Requirement[24]->checkState() == Qt::Unchecked)
    {
        staticTest[53 -1]->setChecked(0);
        staticTest[54 -1]->setChecked(0);
        staticTest[55 -1]->setChecked(0);


        DynamicTest[23 -1]->setChecked(0);


    }
    if (Requirement[25]->checkState() == Qt::Checked)
    {
             DynamicTest[4 -1]->setChecked(1);
             DynamicTest[5 -1]->setChecked(1);
             DynamicTest[6 -1]->setChecked(1);
             DynamicTest[7 -1]->setChecked(1);
             DynamicTest[8 -1]->setChecked(1);
             DynamicTest[9 -1]->setChecked(1);
             DynamicTest[10 -1]->setChecked(1);
             DynamicTest[11 -1]->setChecked(1);
             DynamicTest[12 -1]->setChecked(1);
             DynamicTest[13 -1]->setChecked(1);
             DynamicTest[14 -1]->setChecked(1);
             DynamicTest[15 -1]->setChecked(1);





    }
    if (Requirement[25]->checkState() == Qt::Unchecked)
    {
         DynamicTest[4 -1]->setChecked(0);
         DynamicTest[5 -1]->setChecked(0);
         DynamicTest[6 -1]->setChecked(0);
         DynamicTest[7 -1]->setChecked(0);
         DynamicTest[8 -1]->setChecked(0);
         DynamicTest[9 -1]->setChecked(0);
        DynamicTest[10 -1]->setChecked(0);
        DynamicTest[11 -1]->setChecked(0);
        DynamicTest[12 -1]->setChecked(0);
        DynamicTest[13 -1]->setChecked(0);
        DynamicTest[14 -1]->setChecked(0);
        DynamicTest[15 -1]->setChecked(0);


    }


}

void Read::setPath(QString f){
    filename=f;
}

QLabel* Read::newLabel(QString ch){

    QLabel *label= new QLabel(this);
    label->setGeometry(QRect(QPoint(30, 100),QSize(121, 25)));
    label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
    label->setText(ch);


    QFont font;
    font.setFamily("MS Shell Dlg 2");
    font.setPointSize(12);
    font.setBold(true);
    label->setFont(font);
    return label;
}

QLabel* Read::newSubLabel(QString ch){

    QLabel *Label = new QLabel(this);
    Label->setGeometry(QRect(QPoint(50, 138),QSize(176, 25)));
    Label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
    Label->setText(ch);


    QFont fontSTLINK;
    fontSTLINK.setFamily("MS Shell Dlg 2");
    fontSTLINK.setPointSize(10);
    fontSTLINK.setBold(false);
    Label->setFont(fontSTLINK);
    return Label;
}

void Read::Affiche(){
unsigned int page=0;
    //platforme

QString ch= QString::fromStdString(member[getIndex("Mode")[0]]);
QLabel* f= newLabel(ch);
layout->addWidget(f,++page,0);

QString ch1 =QString::fromStdString(JSON[member[getIndex("Mode")[0]]][getIndex("Mode")[1]].getMemberNames()[getIndex("Mode")[2]]);
QLabel* f1 =newSubLabel(ch1);
layout->addWidget(f1,++page,0);
int modeindex=getIndex("Mode")[3];

layout->addWidget(valueCombo[getIndex("Mode")[3]],page,1);


//memory
for (unsigned int i =0; i< member.size();i++){
    if(!(member[i]== "memory") && !(member[i]== "interfaces")
            && !(member[i]== "USART_dynamic_tests")
            && !(member[i]== "USART_static_tests")
            && !(member[i]== "SPI_dynamic_tests")
            && !(member[i]== "SPI_static_tests")
            && !(member[i]== "I2C_dynamic_tests")
            && !(member[i]== "I2C_static_tests")
            && !(member[i]== "CAN_dynamic_tests")
            && !(member[i]== "CAN_static_tests")
            && !(member[i]== "FDCAN_dynamic_tests")
            && !(member[i]== "FDCAN_static_tests")
            && !(member[i]== "USB_dynamic_tests")
            && !(member[i]== "USB_static_tests")&& !(member[i]== "platform")){
        QString t=  QString::fromStdString( member[i] );
        QLabel *tx= newLabel(t);
        layout->addWidget(tx,++page,0);

        for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){
             for (unsigned int k =0; k<JSON[member[i]][j].getMemberNames().size() ; k++){

            QString T=QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]);
            QLabel *T1= newSubLabel(T);
             layout->addWidget( T1,++page,0);

             if(value[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]) )[3]])
                 layout->addWidget(value[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]) )[3]],page,1);
             else
                 layout->addWidget(valueCombo[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]) )[3]],page,1);

             }
        }
    }


    if(member[i]== "memory"){
int indexName = getIndex("Name")[3];
int indexStart = getIndex("Start")[3];
int indexEnd = getIndex("End")[3];

        QString ch2= QString::fromStdString(member[getIndex("End")[0]]);
        QLabel* f2= newLabel(ch2);
        layout->addWidget(f2,++page,0);

        //Name
        QString ch4 =QString::fromStdString(JSON[member[getIndex("Name")[0]]][getIndex("Name")[1]].getMemberNames()[getIndex("Name")[2]]);
        QLabel* f4 =newSubLabel(ch4);
        layout->addWidget(f4,++page,0);
        //Start
        QString ch5 =QString::fromStdString(JSON[member[getIndex("Start")[0]]][getIndex("Start")[1]].getMemberNames()[getIndex("Start")[2]]);
        QLabel* f5 =newSubLabel(ch5);
        layout->addWidget(f5,page,1);
        //End
        QString ch3 =QString::fromStdString(JSON[member[getIndex("End")[0]]][getIndex("End")[1]].getMemberNames()[getIndex("End")[2]]);
        QLabel* f3 =newSubLabel(ch3);
        layout->addWidget(f3,page,2);


        for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){


            layout->addWidget(value[indexName],++page,0);
            layout->addWidget(value[indexStart],page,1);
            layout->addWidget(value[indexEnd],page,2);

            indexName+=3;
            indexStart+=3;
            indexEnd +=3;
}
}

}
}

std::vector<unsigned int> Read::getIndex( QString ch){

std::vector<unsigned int> result;
unsigned int index=0;
    for (unsigned int i=0; i<JSON.getMemberNames().size(); i++){
        if( !(member[i]=="interfaces") && member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests" &&
                member[i] !="SPI_static_tests" && member[i] !="SPI_dynamic_tests" &&
                    member[i] !="I2C_static_tests" && member[i] !="I2C_dynamic_tests" &&
                                 member[i] !="CAN_static_tests" && member[i] !="CAN_dynamic_tests" &&
                    member[i] !="FDCAN_static_tests" && member[i] !="FDCAN_dynamic_tests" &&
                    member[i] !="USB_static_tests" && member[i] !="USB_dynamic_tests" ){
        for (unsigned int j=0; j<JSON[member[i]].size() ;j++){
            for (unsigned int k =0; k<JSON[member[i]][j].getMemberNames().size() ; k++, index++){

            if(ch == QString::fromStdString(JSON[member[i]][j].getMemberNames()[k])){
                result.push_back(i);
                result.push_back(j);
                result.push_back(k);
                result.push_back(index);

                return (result);
            }
}

        }}
    }

}

bool Read::Mandatory(){
    bool t =true;
    for(unsigned int i=0; i< value.size();i++){
        if(value[i]!= NULL && value[i]->text()== ""){
            value[i]->setStyleSheet("border: 1.5px solid red");
            t= false;

        }
    }
    return t;
}



