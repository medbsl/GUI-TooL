#include "read.h"
#include "ui_read.h"
#include <fstream>
#include <QDebug>
#include "mainwindow.h"

unsigned int counterRequirement =0,counterRequirementI2C=0,counterRequirementSPI =0,counterRequirementUSB =0,counterRequirementCAN =0,counterRequirementFDCAN =0;
unsigned int counterStatic =0,counterStaticI2C =0,counterStaticSPI =0,counterStaticUSB =0,counterStaticCAN =0,counterStaticFDCAN =0;
unsigned int counterDynamic =0,counterDynamicI2C =0,counterDynamicSPI =0,counterDynamicUSB =0,counterDynamicCAN =0,counterDynamicFDCAN =0;
unsigned int page =0;
bool newfile =false;
int index =0;
int addmemory3=0;


/*The constructor will initialize the GUI by setting the scroll area of each communication protocol , collecting them in Table widget and create the generate button   */
Read::Read(QWidget *parent, QString filename,bool newFile,bool USARTSTATE,bool I2CSTATE,
           bool SPISTATE,bool CANSTATE,bool FDCANSTATE,bool USBSTATE) : QDialog(parent), ui(new Ui::Read){

    newfile =newFile;
    UsartState= USARTSTATE;
    I2cState=  I2CSTATE;
    SpiState= SPISTATE;
    CanState=  CANSTATE;
    FDCanState= FDCANSTATE;
    UsbState=  USBSTATE;

    ui->setupUi(this);

    /* if new file is checked then we will parse the json and add set all the adresses with 0x*/
    /* else we parse the json and keep all data*/

    /*on browse button is a function that parse the json file and save all data in vectors*/
    if (newFile)
        onBrowseNewFile();
    else
        onBrowseButton(filename);




//*****************************************************************************//
//****************************  scroll area         ***************************//
//*****************************************************************************//

/* Set up the scroll area for the Plateform interface */

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

/* Set up the scroll area for the USART interface */

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

/* Set up the scroll area for the SPI interface */

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

/* Set up the scroll area for the I2C interface */

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

/* Set up the scroll area for the USB interface */

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

/* Set up the scroll area for the CAN interface */

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

/* Set up the scroll area for the FDCAN interface */

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

/* Set up the TABLE widget and include all scroll area  */

              QTabWidget *Tab= new QTabWidget(this);
              Tab->setGeometry(5,5,995, 835);
              Tab->addTab(scrollArea, "PLateform");
              if(!newfile || UsartState)
                Tab->addTab(scrollAreaUsart, "Usart");
              if(!newfile || SpiState)
                Tab->addTab(scrollAreaSPI, "SPI");
              if(!newfile || I2cState)
                Tab->addTab(scrollAreaI2C, "I2C");
              if(!newfile || UsbState)
                Tab->addTab(scrollAreaUSB, "USB");
              if(!newfile || CanState)
                Tab->addTab(scrollAreaCan, "CAN");
              if(!newfile || FDCanState)
                Tab->addTab(scrollAreaFdCan, "FD_CAN");


//*****************************************************************************//
//****************************    Generate Button   ***************************//
//*****************************************************************************//

/* Set up the Generate button  */

// PushButton
    QHBoxLayout* layoutButton = new QHBoxLayout( this );
    layoutButton->setContentsMargins(0,0,0,0);
    m_button = new QPushButton("Save changes", this);
    m_button->setGeometry(QRect(QPoint(845, 855),QSize(150, 50)));
    connect(m_button,SIGNAL (clicked()), this, SLOT(onSaveChanegeButton()));


}

/* The destructor will clean all vector are used in the class */
Read::~Read()
{
    staticTest.clear();
    DynamicTest.clear();
    Requirement.clear();
    interfaces.clear();

    value.clear();
    valueCombo.clear();

    valueUsart.clear();
    valueUsartCombo.clear();

    valueSpi.clear();
    valueSpiCombo.clear();

    valueI2C.clear();
    valueI2CCombo.clear();

    valueCAN.clear();
    valueCANCombo.clear();

    valueFDCAN.clear();
    valueFDCANCombo.clear();

    valueUSB.clear();
    valueUSBCombo.clear();

    staticTest.clear() ; staticTestSpi.clear(); staticTestCAN.clear() ; staticTestFDCAN.clear() ; staticTestI2C.clear()
            ; staticTestUSB.clear();
    DynamicTest.clear(), DynamicTestSpi.clear(); DynamicTestCAN.clear() ; DynamicTestFDCAN.clear(); DynamicTestI2C.clear()
            ;DynamicTestUSB.clear();
    Requirement.clear(); RequirementSpi.clear();RequirementTestCAN.clear() ; RequirementTestFDCAN.clear();
             RequirementTestI2C.clear(); RequirementTestUSB.clear();

    delete ui;
}

/* The onBrowseNewFile function will parse the JSON File and set all addresses to 0x */
void Read::onBrowseNewFile(){

/*The unsigned int s the line number in the scroll area widget */
        unsigned int s=0;

/*The file JSONFILE is a temporary ifstream file that contain the data of the json Template */
       std::ifstream JSONFILE(filename.toLocal8Bit().constData(), std::ifstream::binary);
       JSONFILE >> JSON;
       member= JSON.getMemberNames();

/* Parsing the json Template */
/* The i counter is for counting the members */
/* The j counter is for counting the value of each members */
        for (unsigned int i = 0; i < member.size(); i++) {
            for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){


                /* Parsing a General information of the device, such as Platform, Target, Driver, bl-data.. */
                /* If the data can be founded in a combo Box  then we will add that data to a vector named "valueCombo" and add a null pointer to "value" in order to keep the same index*/
                /* Else we will add a null pointer to "valueCombo" and add the data to the vector "value" */

                 if (    member[i] !="USART_static_tests"  &&  member[i] !="USART_dynamic_tests"  &&
                         member[i] !="SPI_static_tests"    &&  member[i] !="SPI_dynamic_tests"    &&
                         member[i] !="I2C_static_tests"    &&  member[i] !="I2C_dynamic_tests"    &&
                         member[i] !="CAN_static_tests"    &&  member[i] !="CAN_dynamic_tests"    &&
                         member[i] !="FDCAN_static_tests"  &&  member[i] !="FDCAN_dynamic_tests"  &&
                         member[i] !="USB_static_tests"    &&  member[i] !="USB_dynamic_tests"    &&
                         member[i] !="interfaces"          ){



                            /*create and add the label the widget */
                            /*The newLabel is a function that take a QString name and create a QLabel, It create the Label of the members in the JSONFILE*/
                            label = newLabel(QString::fromStdString(member[i]));

                            /*The k counter is for counting the values of a value*/
                            for (unsigned int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){


                                /*The newLabel is a function that take a QString name and create a QLabel, It create the Label of the members in the JSONFILE*/
                                 Label = newSubLabel(QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]));

                                /*check if the values can be a in a ComboBox */
                                /*The list of comboBox is "connect" "supprot_ME" "supprot_BE" "Mode" "WRP" "UseReset" "STLink_SN" */
                                if (JSON[member[i]][j].getMemberNames()[k] == "connect"){

                                    QComboBox *combo = new QComboBox( this );
                                    combo->setEditable( false );
                                    combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                    combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                    combo->addItem(tr("true"));
                                    combo->addItem(tr("false"));
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
                                    valueCombo.push_back(combo);
                                    value.push_back(NULL);
                                    break;
                                }
                                if (JSON[member[i]][j].getMemberNames()[k] == "WRP"){

                                    QComboBox *combo = new QComboBox( this );
                                    combo->setEditable( false );
                                    combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                    combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                    combo->addItem(tr("byArea"));
                                    combo->addItem(tr("bySectors"));
                                    valueCombo.push_back(combo);
                                    value.push_back(NULL);
                                    break;
                                }
                                if (JSON[member[i]][j].getMemberNames()[k] == "UseReset"){

                                    QComboBox *combo = new QComboBox( this );
                                    combo->setEditable( false );
                                    combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                    combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                    combo->addItem(tr("true"));
                                    combo->addItem(tr("false"));
                                    valueCombo.push_back(combo);
                                    value.push_back(NULL);
                                    break;
                                }
                                if (JSON[member[i]][j].getMemberNames()[k] == "STLink_SN"){

                                    lineEdit = new QLineEdit(this);
                                    lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                    lineEdit->setText("");
                                    valueCombo.push_back(NULL);
                                    value.push_back(lineEdit);
                                    break;
                                }

                                if(JSON[member[i]][j].getMemberNames()[k] == "Name" && member[i]== "memory"){
                                    lineEdit = new QLineEdit(this);
                                    lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                    lineEdit->setText("");
                                    valueCombo.push_back(NULL);
                                    value.push_back(lineEdit);
                                }

                                /*The other choices will be a LineEdit as a Default */
                                else {

                                    lineEdit = new QLineEdit(this);
                                    lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                    lineEdit->setText("0x");
                                    valueCombo.push_back(NULL);
                                    value.push_back(lineEdit);

                                }
                            }
                        }

                 /*If The member is "interfaces" then it check if the type of communication protocol */
                else if (member[i] == "interfaces"){

                    /*If the Name of the interfaces value is I2C then it will fill the I2C TAB */
                    if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "I2C"){

                        /*The s counter the lines of the I2C scroll area */
                        s=0;
                        /*Create a checkBox that to activate of deactivate the I2C*/
                        QCheckBox *valide = new QCheckBox("I2C",this);
                        if (I2cState)
                            valide->setChecked(1);
                        else
                            valide->setChecked(0);
                        interfaces.push_back(valide);
                        //layoutI2C->addWidget(valide,s,0);

                        for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                            if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){

                            /*Create and QLabel of the interfaces value */
                                Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                                layoutI2C->addWidget(Label, ++s,0);
                            }

                            /*Test if the value will be in CheckBox or in LineEdit*/
                            /*The list of the CheckBox is "Baudrate" "address" */

                            if (JSON["interfaces"][j].getMemberNames()[k] == "Bitrate"){

                                QComboBox *combo = new QComboBox( this );
                                combo->setEditable( true  );
                                combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                combo->addItem(tr("400"));
                                layoutI2C->addWidget(combo, s,1);
                                valueI2CCombo.push_back(combo);
                                valueI2C.push_back(NULL);

                            }

                            if (JSON["interfaces"][j].getMemberNames()[k] == "address"){

                                lineEdit = new QLineEdit(this);
                                lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                lineEdit->setText("0x");
                                layoutI2C->addWidget(lineEdit, s,1);
                                valueI2CCombo.push_back(NULL);
                                valueI2C.push_back(lineEdit);

                            }
                            /*Else the value will be in a LineEdit */

                            else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ) {

                                lineEdit = new QLineEdit(this);
                                lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                lineEdit->setText("");
                                layoutI2C->addWidget(lineEdit, s,1);
                                valueI2CCombo.push_back(NULL);
                                valueI2C.push_back(lineEdit);
                            }
                        }

                        /*Then we will include to the TabWidget the static and dynamic tests of the I2C*/
                        if(JSON["I2C_static_tests"] != 0){

                            /*Including the Label in the TabWidget*/
                            QLabel *labelBlData = newLabel("Static :");
                            layoutI2C->addWidget(labelBlData,++s,0);
                            QLabel *labelDynamic = newLabel("Dynamic :");
                            layoutI2C->addWidget(labelDynamic,s,1);


                            QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticI2C()));
                            layoutI2C->addWidget(checkAllTestStatic,++s,0);

                            QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicI2C()));
                            layoutI2C->addWidget(checkAllTestDynamic,s,1);

                            QLabel *req = newLabel("");
                            layoutI2C->addWidget(req,s,2);

                            /* ************************  Static  *********************/
                            for (unsigned int j = 0; j < JSON["I2C_static_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_static_tests"][j][JSON["I2C_static_tests"][j].getMemberNames()[2]].asString()) ,this);
                                if( JSON["I2C_static_tests"][j]["state"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["I2C_static_tests"][j]["state"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutI2C->addWidget(box,++s,0);
                                staticTestI2C.push_back(box);
                            }
                            /* ************************  Dynamic   *********************/
                            /*Return the counter s to the same position of the static test in order to include the dynamic test with the same position as the static (next to each other)*/
                            s-= staticTestI2C.size();
                            for (unsigned int j = 0; j < JSON["I2C_dynamic_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_dynamic_tests"][j][JSON["I2C_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);
                                if( JSON["I2C_dynamic_tests"][j]["state"].asString() == "ON" )
                                    box->setChecked(1);
                                if(JSON["I2C_dynamic_tests"][j]["state"].asString() == "OFF")
                                    box->setChecked(0);
                                layoutI2C->addWidget(box,++s,1);
                                DynamicTestI2C.push_back(box);

                            }
                        }
                    }
                    /*If the Name of the interfaces value is SPI then it will fill the SPI TAB */
                    else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "SPI"){
                    /*The s counter is for counting the lines of scroll area */
                    s=0;
                    QCheckBox *valide = new QCheckBox("SPI",this);
                    if (SpiState)
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);
                        interfaces.push_back(valide);
                        /*Add the checkBox validate to the scroll area*/
                        //layoutSpi->addWidget(valide,s,0);
                        /*Parsing the Interfaces Values */
                            for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                                /*If the values of interfaces wasn't Name or state then it creat the label and add to the widget*/
                                if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                                    Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                                    layoutSpi->addWidget(Label, ++s,0);
                                }
                                /*Test if the value is



*/
                                /*If the value is baudrate then it create the ComboBox*/
                                if (JSON["interfaces"][j].getMemberNames()[k] == "Bitrate"){

                                    QComboBox *combo = new QComboBox( this );
                                    combo->setEditable( true );
                                    combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                    combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                    combo->addItem(tr("400"));
                                    combo->addItem(tr("8000"));
                                    layoutSpi->addWidget(combo, s,1);
                                    valueSpiCombo.push_back(combo);
                                    valueSpi.push_back(NULL);

                                }
                                /*else it will create a Line Edit for the rest of all value*/
                                else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ) {                                  // Line Edit

                                    lineEdit = new QLineEdit(this);
                                    lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                    lineEdit->setText("");
                                    layoutSpi->addWidget(lineEdit, s,1);
                                    valueSpiCombo.push_back(NULL);
                                    valueSpi.push_back(lineEdit);
                                }

                            }
                            /*Adding the static/dynamic test of SPI communication protocol */
                            if(JSON["SPI_static_tests"] != 0){

                                QLabel *labelBlData = newLabel("Static :");
                                layoutSpi->addWidget(labelBlData,++s,0);


                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutSpi->addWidget(labelDynamic,s,1);

                                QLabel *req = newLabel("");
                                layoutSpi->addWidget(labelDynamic,s,2);


                                QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                                connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticSPI()));
                                layoutSpi->addWidget(checkAllTestStatic,++s,0);

                                QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                                connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicSPI()));
                                layoutSpi->addWidget(checkAllTestDynamic,s,1);



                                /* ************************  Static  **********************/
                                for (unsigned int j = 0; j < JSON["SPI_static_tests"].size()  ; j++){

                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_static_tests"][j][JSON["SPI_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                                    if( JSON["SPI_static_tests"][j]["state"].asString() == "ON" )
                                        box->setChecked(1);

                                    if(JSON["SPI_static_tests"][j]["state"].asString() == "OFF")
                                        box->setChecked(0);

                                    layoutSpi->addWidget(box,++s,0);
                                    staticTestSpi.push_back(box);
                                }
                                /* ************************  Dynamic   **********************/
                                s-= staticTestSpi.size();
                                for (unsigned int j = 0; j < JSON["SPI_dynamic_tests"].size()  ; j++){

                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_dynamic_tests"][j][JSON["SPI_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                                    if( JSON["SPI_dynamic_tests"][j]["state"].asString() == "ON" )
                                        box->setChecked(1);

                                    if(JSON["SPI_dynamic_tests"][j]["state"].asString() == "OFF")
                                        box->setChecked(0);

                                    layoutSpi->addWidget(box,++s,1);
                                    DynamicTestSpi.push_back(box);

                                }
                            }
                    }
                    /*If the Name of the interfaces value is SPI then it will fill the USB TAB */
                    else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[1] ].asString() == "USB" ){
                        /*The s count the lines in the scroll area of the USB widget */
                        s=0;
                        /*Creating the checkBox validate and test if in the json is ON or OFF */
                        /*If testchck is ON then it check the checkbox*/
                        /*else it will not check the checkbox*/
                        QCheckBox *valide = new QCheckBox("USB",this);

                        if (UsbState)
                            valide->setChecked(1);

                        else
                            valide->setChecked(0);

                        interfaces.push_back(valide);
                        //layoutUSB->addWidget(valide,s,0);
                            for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                                /*Creating the label*/
                                if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){

                                Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                                layoutUSB->addWidget(Label, ++s,0);

                                }
                                /*if the value is a baudrate then it will create a combo box*/
                                if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                    QComboBox *combo = new QComboBox( this );
                                    combo->setEditable( false );
                                    combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                    combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                    combo->addItem(tr("921600"));
                                    combo->addItem(tr("460800"));
                                    combo->addItem(tr("230400"));
                                    combo->addItem(tr("115200"));
                                    combo->addItem(tr("57600"));
                                    combo->addItem(tr("56000"));
                                    combo->addItem(tr("38400"));
                                    combo->addItem(tr("19200"));
                                    combo->addItem(tr("14400"));
                                    combo->addItem(tr("9600"));
                                    combo->addItem(tr("4800"));
                                    combo->addItem(tr("2400"));
                                    combo->addItem(tr("1200"));
                                    layoutUSB->addWidget(combo, s,1);
                                    valueUSBCombo.push_back(combo);
                                    valueUSB.push_back(NULL);

                                }

                                /*it will create a lineEdit for the rest of the other values */
                                else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                                    lineEdit = new QLineEdit(this);
                                    lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                    lineEdit->setText("");
                                    layoutUSB->addWidget(lineEdit, s,1);

                                    valueUSBCombo.push_back(NULL);
                                    valueUSB.push_back(lineEdit);
                                }
                            }

                            /*adding the static/dynamic test of the USB*/
                            if(JSON["USB_static_tests"] != 0){

                                QLabel *labelBlData = newLabel("Static :");

                                layoutUSB->addWidget(labelBlData,++s,0);

                                QLabel *labelDynamic = newLabel("Dynamic :");
                                layoutUSB->addWidget(labelDynamic,s,1);

                                QLabel *labelRequirement = newLabel("");
                                layoutUSB->addWidget(labelRequirement,s,2);

                                QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                                connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticUSB()));
                                layoutUSB->addWidget(checkAllTestStatic,++s,0);

                                QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                                connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicUSB()));
                                layoutUSB->addWidget(checkAllTestDynamic,s,1);



                                /* ************************  Static  **********************/
                                for (unsigned int j = 0; j < JSON["USB_static_tests"].size()  ; j++){

                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_static_tests"][j][JSON["USB_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                                    if( JSON["USB_static_tests"][j]["state"].asString() == "ON" )
                                           box->setChecked(1);

                                    if(JSON["USB_static_tests"][j]["state"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutUSB->addWidget(box,++s,0);
                                    staticTestUSB.push_back(box);


                                }

                                /* ************************  Dynamic   **********************/
                                s-= staticTestUSB.size();
                                for (unsigned int j = 0; j < JSON["USB_dynamic_tests"].size()  ; j++){

                                    QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_dynamic_tests"][j][JSON["USB_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                                    if( JSON["USB_dynamic_tests"][j]["state"].asString() == "ON" )
                                           box->setChecked(1);

                                    if(JSON["USB_dynamic_tests"][j]["state"].asString() == "OFF")
                                           box->setChecked(0);

                                    layoutUSB->addWidget(box,++s,1);
                                    DynamicTestUSB.push_back(box);


                                }
                                for(int i=0;i<10;i++){
                                    QLabel *label= newLabel("");
                                    layoutUSB->addWidget(label,++s,0);

                                }


                            }


                    }
                    /*If the Name of the interfaces value is SPI then it will fill the CAN TAB */
                    else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "CAN" ){
                    /*The s counter is for counting the line in the CAN widget*/
                    s=0;
                    /*Creatin a CheckBox to valid or no the CAN communication testing */
                    /*If the state is ON then it will check the checkBox*/
                    /*else it will not check the checkBox*/
                    QCheckBox *valide = new QCheckBox("CAN",this);
                    if (CanState)
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);
                    /*Adding the checkbox to the vector "interfaces"*/
                    interfaces.push_back(valide);
                    //layoutCAN->addWidget(valide,s,0);
                    for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                        /*Creating the label*/
                        if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                            Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                            layoutCAN->addWidget(Label, ++s,0);
                        }
                        /*if the value is a baudrate then it will create a cobobox*/
                        if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("921600"));
                            combo->addItem(tr("460800"));
                            combo->addItem(tr("230400"));
                            combo->addItem(tr("115200"));
                            combo->addItem(tr("57600"));
                            combo->addItem(tr("56000"));
                            combo->addItem(tr("38400"));
                            combo->addItem(tr("19200"));
                            combo->addItem(tr("14400"));
                            combo->addItem(tr("9600"));
                            combo->addItem(tr("4800"));
                            combo->addItem(tr("2400"));
                            combo->addItem(tr("1200"));
                            layoutCAN->addWidget(combo, s,1);
                            valueCANCombo.push_back(combo);
                            valueCAN.push_back(NULL);

                        }
                        /*else it will create a lineEdit for the rest of the values */
                        else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                            lineEdit = new QLineEdit(this);
                            lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                            lineEdit->setText("");
                            layoutCAN->addWidget(lineEdit, s,1);
                            valueCANCombo.push_back(NULL);
                            valueCAN.push_back(lineEdit);
                        }
                    }
                    /*Bring the Static/dynamic tests */
                    if(JSON["CAN_static_tests"] != 0){

                        QLabel *labelBlData = newLabel("Static :");
                        layoutCAN->addWidget(labelBlData,++s,0);

                        QLabel *labelDynamic = newLabel("Dynamic :");
                        layoutCAN->addWidget(labelDynamic,s,1);

                        QLabel *labelRequirement = newLabel("");
                        layoutCAN->addWidget(labelRequirement,s,2);


                        QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticCAN()));
                        layoutCAN->addWidget(checkAllTestStatic,++s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicCAN()));
                        layoutCAN->addWidget(checkAllTestDynamic,s,1);



                            /* ************************  Static  **********************/
                        for (unsigned int j = 0; j < JSON["CAN_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["CAN_static_tests"][j][JSON["CAN_static_tests"][j].getMemberNames()[2]].asString()) ,this);
                            if( JSON["CAN_static_tests"][j]["state"].asString() == "ON" )
                                box->setChecked(1);

                            if(JSON["CAN_static_tests"][j]["state"].asString() == "OFF")
                                box->setChecked(0);

                            layoutCAN->addWidget(box,++s,0);
                            staticTestCAN.push_back(box);


                        }

                        /* ************************  Dynamic   **********************/
                        s-= staticTestCAN.size();

                        for (unsigned int j = 0; j < JSON["CAN_dynamic_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["CAN_dynamic_tests"][j][JSON["CAN_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["CAN_dynamic_tests"][j]["state"].asString() == "ON" )
                                box->setChecked(1);
                            if(JSON["CAN_dynamic_tests"][j]["state"].asString() == "OFF")
                                box->setChecked(0);

                            layoutCAN->addWidget(box,++s,1);
                            DynamicTestCAN.push_back(box);

                        }
                    }
                    }
                    /*If the Name of the interfaces value is SPI then it will fill the FDCAN TAB */
                    else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "FDCAN" ){
                    /*The s counter is for counting the widget of the FDCAN*/
                    s=0;
                    /*The "valid" checkbox is to activate or not the FDCAN testing*/
                    QCheckBox *valide = new QCheckBox("FDCAN",this);
                    if (FDCanState)
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);

                    interfaces.push_back(valide);
                    //layoutFDCAN->addWidget(valide,s,0);
                    for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                        /*Creating the labels*/
                        if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                        Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                        layoutFDCAN->addWidget(Label, ++s,0);

                        }
                        /*If the value is a Baudrate then it will create a comboBox */
                        if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("921600"));
                            combo->addItem(tr("460800"));
                            combo->addItem(tr("230400"));
                            combo->addItem(tr("115200"));
                            combo->addItem(tr("57600"));
                            combo->addItem(tr("56000"));
                            combo->addItem(tr("38400"));
                            combo->addItem(tr("19200"));
                            combo->addItem(tr("14400"));
                            combo->addItem(tr("9600"));
                            combo->addItem(tr("4800"));
                            combo->addItem(tr("2400"));
                            combo->addItem(tr("1200"));
                            layoutFDCAN->addWidget(combo, s,1);
                            valueFDCANCombo.push_back(combo);
                            valueFDCAN.push_back(NULL);

                        }
                        /*it create a lineEdit for the rest of the other values */
                        else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                            lineEdit = new QLineEdit(this);
                            lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                            lineEdit->setText("");
                            layoutFDCAN->addWidget(lineEdit, s,1);
                            valueFDCANCombo.push_back(NULL);
                            valueFDCAN.push_back(lineEdit);
                        }

                    }
                    /*including the static/dynamic tests*/

                    if(JSON["FDCAN_static_tests"] != 0){

                        QLabel *labelBlData = newLabel("Static :");
                        layoutFDCAN->addWidget(labelBlData,++s,0);

                        QLabel *labelDynamic = newLabel("Dynamic :");
                        layoutFDCAN->addWidget(labelDynamic,s,1);

                        QLabel *labelRequirement = newLabel("");
                        layoutFDCAN->addWidget(labelRequirement,s,2);

                        QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticFDCAN()));
                        layoutFDCAN->addWidget(checkAllTestStatic,++s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicFDCAN()));
                        layoutFDCAN->addWidget(checkAllTestDynamic,s,1);



                        /* ************************  Static  **********************/
                        for (unsigned int j = 0; j < JSON["FDCAN_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["FDCAN_static_tests"][j][JSON["FDCAN_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["FDCAN_static_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["FDCAN_static_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutFDCAN->addWidget(box,++s,0);
                            staticTestFDCAN.push_back(box);

                        }

                        /* ************************  Dynamic   **********************/
                        s-= staticTestFDCAN.size();
                        for (unsigned int j = 0; j < JSON["FDCAN_dynamic_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["FDCAN_dynamic_tests"][j][JSON["FDCAN_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["FDCAN_dynamic_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["FDCAN_dynamic_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutFDCAN->addWidget(box,++s,1);
                            DynamicTestFDCAN.push_back(box);

                        }
                    }
                    }
                    /*If the Name of the interfaces value is SPI then it will fill the USART TAB */
                    else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[4] ].asString() == "USART" ){
                        /*The s counter is for counting the line in the widget of USART*/
                        s=0;
                        /*The Check Box is for activate or not the USART test*/
                        QCheckBox *valide = new QCheckBox("USART",this);
                        if (UsartState)
                            valide->setChecked(1);
                        else
                            valide->setChecked(0);
                        /*Add the checkBox to the interfaces vector */
                        interfaces.push_back(valide);
                        //layoutUsart->addWidget(valide,s,0);
                        for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                            /*creating the Labels*/
                            if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                                Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                layoutUsart->addWidget(Label, ++s,0);
                            }
                            /*if the value is a "baudrate" the it will create a combobox */
                            if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                QComboBox *combo = new QComboBox( this );
                                combo->setEditable( false );
                                combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                combo->addItem(tr("921600"));
                                combo->addItem(tr("460800"));
                                combo->addItem(tr("230400"));
                                combo->addItem(tr("115200"));
                                combo->addItem(tr("57600"));
                                combo->addItem(tr("56000"));
                                combo->addItem(tr("38400"));
                                combo->addItem(tr("19200"));
                                combo->addItem(tr("14400"));
                                combo->addItem(tr("9600"));
                                combo->addItem(tr("4800"));
                                combo->addItem(tr("2400"));
                                combo->addItem(tr("1200"));
                                layoutUsart->addWidget(combo, s,1);
                                /*Add the comboBox the valueUsartCombo vector*/
                                /*Add a null pointer to the value USART vector in order to keep the same index*/
                                valueUsartCombo.push_back(combo);
                                valueUsart.push_back(NULL);

                            }
                            else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                                lineEdit = new QLineEdit(this);
                                lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                lineEdit->setText("");
                                layoutUsart->addWidget(lineEdit, s,1);
                                valueUsartCombo.push_back(NULL);
                                valueUsart.push_back(lineEdit);

                            }

                        }
                        /*We add the Static/ dynamic test in the widget of the USART */

                        if(JSON["USART_static_tests"] != 0){

                            QLabel *labelBlData = newLabel("Static :");
                            layoutUsart->addWidget(labelBlData,++s,0);


                            QLabel *labelDynamic = newLabel("Dynamic :");
                            layoutUsart->addWidget(labelDynamic,s,1);

                            QLabel *labelRequirement = newLabel("");
                            layoutUsart->addWidget(labelRequirement,s,2);

                            QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                            layoutUsart->addWidget(checkAllTestStatic,++s,0);

                            QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                            layoutUsart->addWidget(checkAllTestDynamic,s,1);



                            /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_static_tests"][j][JSON["USART_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                                if( JSON["USART_static_tests"][j]["state"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["USART_static_tests"][j]["state"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutUsart->addWidget(box,++s,0);
                                staticTest.push_back(box);


                            }

                            /* ************************  Dynamic   **********************/
                            s-= staticTest.size();
                            for (unsigned int j = 0; j < JSON["USART_dynamic_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_dynamic_tests"][j][JSON["USART_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);
                                if( JSON["USART_dynamic_tests"][j]["state"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["USART_dynamic_tests"][j]["state"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutUsart->addWidget(box,++s,1);
                                DynamicTest.push_back(box);

                            }
                        }
                    }
                }
            }
        }
    /*The Affiche function will fill the Plateform*/
    Affiche();
}

/*The Function "onBrowseButton" will Edit a JsonFile  */
/*The difference between the "onBrowseButton" and "onBrowseNewFile" is that the first will show all the content of the jsonFile  */
/*The "onBrowseNewFile" show all the member but it clean the values in order to fill the empty LineEdit*/
void Read::onBrowseButton(QString filename){
    /*The s counter is for counting the lines of the "platform" widget*/
    unsigned int s=0;
    std::ifstream JSONFILE(filename.toLocal8Bit().constData(), std::ifstream::binary);
    JSONFILE >> JSON;
    member= JSON.getMemberNames();
    /*The i count the member in the json File */
    /*The j parse the value of the each member */
    /*The k parse the value of each object of each member*/
    for (unsigned int i = 0; i < member.size(); i++) {
        for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){
            /*firstly we test if the member is not*/

            if (   member[i] !="USART_static_tests"  &&  member[i] !="USART_dynamic_tests"  &&
                member[i] !="SPI_static_tests"    &&  member[i] !="SPI_dynamic_tests"    &&
                member[i] !="I2C_static_tests"    &&  member[i] !="I2C_dynamic_tests"    &&
                member[i] !="CAN_static_tests"    &&  member[i] !="CAN_dynamic_tests"    &&
                member[i] !="FDCAN_static_tests"  &&  member[i] !="FDCAN_dynamic_tests"  &&
                member[i] !="USB_static_tests"    &&  member[i] !="USB_dynamic_tests"    &&
                member[i] !="interfaces"){

                     /*Create the label*/
                    label = newLabel(QString::fromStdString(member[i]));
                    for (unsigned int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){
                        Label = newSubLabel(QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]));


                        /*If the value is "connect" | "supprot_BE" | WRP | UseReset the it create a comboBox*/
                        if (JSON[member[i]][j].getMemberNames()[k] == "connect"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("true"));
                            combo->addItem(tr("false"));
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

                            valueCombo.push_back(combo);
                            value.push_back(NULL);
                            break;
                        }
                        if (JSON[member[i]][j].getMemberNames()[k] == "WRP"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("byArea"));
                            combo->addItem(tr("bySectors"));

                            valueCombo.push_back(combo);
                            value.push_back(NULL);
                            break;
                        }
                        if (JSON[member[i]][j].getMemberNames()[k] == "UseReset"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("true"));
                            combo->addItem(tr("false"));

                            valueCombo.push_back(combo);
                            value.push_back(NULL);
                            break;
                        }

                        /*Else the rest of value will be A LineEdit by default*/
                        else {
                                lineEdit = new QLineEdit(this);
                                lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                lineEdit->setText(QString::fromStdString(JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k] ].asString()));
                                valueCombo.push_back(NULL);
                                value.push_back(lineEdit);

                        }
                        }
                    }


            else if (member[i] == "interfaces"){
                /*If the Name of the interfaces value is I2C then it will fill the I2C TAB */
                if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "I2C"){
                    /*The counter s is counting the line of the I2C widget */
                    s=0;
                    /*Create a checkBox that will identify if we want to test the I2C communication protocol or not*/
                    QCheckBox *valide = new QCheckBox("I2C",this);
                    /*If the "state" is ON then the checkBox will Be checked*/
                    /*Else the check box will be not checked*/
                    if (JSON["interfaces"][0]["state" ].asString()== "ON")
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);
                    /*Add the checkBox to the "interfaces" vector*/
                    interfaces.push_back(valide);
                    layoutI2C->addWidget(valide,s,0);
                    for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                        if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){

                            /*Create a label then we put it to the widgetLayout*/
                            Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                            layoutI2C->addWidget(Label, ++s,0);
                        }
                        /*If the value is "Baudrate" then we create a comboBox  */
                        if (JSON["interfaces"][j].getMemberNames()[k] == "Bitrate"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( true );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("400"));
                            layoutI2C->addWidget(combo, s,1);

                            valueI2CCombo.push_back(combo);
                            valueI2C.push_back(NULL);

                        }
                        /*The rest of values will be a LineEdit by default*/
                        else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ) {

                            lineEdit = new QLineEdit(this);
                            lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                            lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                            layoutI2C->addWidget(lineEdit, s,1);

                            valueI2CCombo.push_back(NULL);
                            valueI2C.push_back(lineEdit);
                        }
                    }
                    /*Add the static /dynamic test to the widget Lyout of the I2C*/
                    if(JSON["I2C_static_tests"] != 0){

                        QLabel *labelBlData = newLabel("Static :");
                        layoutI2C->addWidget(labelBlData,++s,0);

                        QLabel *labelDynamic = newLabel("Dynamic :");
                        layoutI2C->addWidget(labelDynamic,s,1);

                        QLabel *labelRequirement = newLabel("");
                        layoutI2C->addWidget(labelRequirement,s,2);

                        QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticI2C()));
                        layoutI2C->addWidget(checkAllTestStatic,++s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicI2C()));
                        layoutI2C->addWidget(checkAllTestDynamic,s,1);



                        /* ************************  Static  *********************/
                        for (unsigned int j = 0; j < JSON["I2C_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_static_tests"][j][JSON["I2C_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["I2C_static_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["I2C_static_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutI2C->addWidget(box,++s,0);
                            staticTestI2C.push_back(box);


                        }
                        /* ************************  Dynamic   *********************/
                        s-= staticTestI2C.size();
                        for (unsigned int j = 0; j < JSON["I2C_dynamic_tests"].size()  ; j++){


                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["I2C_dynamic_tests"][j][JSON["I2C_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["I2C_dynamic_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["I2C_dynamic_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutI2C->addWidget(box,++s,1);
                            DynamicTestI2C.push_back(box);
                        }
                    }
                }

                /*If the Name of the interfaces value is SPI then it will fill the SPI TAB */
                else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "SPI"){
                /*The s count the lines of the SPI widget */
                s=0;
                /*create a check box "valid" to Check if we want to test the SPI or not*/
                QCheckBox *valide = new QCheckBox("SPI",this);
                    if (JSON["interfaces"][j]["state"  ].asString()== "ON")
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);

                    interfaces.push_back(valide);
                    layoutSpi->addWidget(valide,s,0);

                for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                    if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                        /*Create a Label*/
                        Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                        layoutSpi->addWidget(Label, ++s,0);
                    }
                    /*If the value is a Baudrate then we create a comboBox*/
                    if (JSON["interfaces"][j].getMemberNames()[k] == "Bitrate"){

                        QComboBox *combo = new QComboBox( this );
                        combo->setEditable( true );
                        combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                        combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                        combo->addItem(tr("125"));
                        combo->addItem(tr("8000"));
                        layoutSpi->addWidget(combo, s,1);
                        /*add the comboBox to the "valueSpiCombo" vector */
                        /*add a null pointer to the value SPI in order to keep the same index*/
                        valueSpiCombo.push_back(combo);
                        valueSpi.push_back(NULL);

                    }
                    /*The other values will be a lineEdit by default */
                    else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ) {                                  // Line Edit

                        lineEdit = new QLineEdit(this);
                        lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                        lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                        layoutSpi->addWidget(lineEdit, s,1);

                        valueSpiCombo.push_back(NULL);
                        valueSpi.push_back(lineEdit);
                    }
                }
                /*add static/Dynamic test to the SPI widget*/
                if(JSON["SPI_static_tests"] != 0){

                    QLabel *labelBlData = newLabel("Static :");
                    layoutSpi->addWidget(labelBlData,++s,0);

                    QLabel *labelDynamic = newLabel("Dynamic :");
                    layoutSpi->addWidget(labelDynamic,s,1);

                    QLabel *labelRequirement = newLabel("");
                    layoutSpi->addWidget(labelRequirement,s,2);

                    QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                    connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticSPI()));
                    layoutSpi->addWidget(checkAllTestStatic,++s,0);

                    QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                    connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicSPI()));
                    layoutSpi->addWidget(checkAllTestDynamic,s,1);


                    /* ************************  Static  **********************/
                    for (unsigned int j = 0; j < JSON["SPI_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_static_tests"][j][JSON["SPI_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["SPI_static_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["SPI_static_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutSpi->addWidget(box,++s,0);
                            staticTestSpi.push_back(box);
                    }

                    /* ************************  Dynamic   **********************/
                    s-= staticTestSpi.size();
                    for (unsigned int j = 0; j < JSON["SPI_dynamic_tests"].size()  ; j++){

                        QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["SPI_dynamic_tests"][j][JSON["SPI_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                        if( JSON["SPI_dynamic_tests"][j]["state"].asString() == "ON" )
                            box->setChecked(1);
                        if(JSON["SPI_dynamic_tests"][j]["state"].asString() == "OFF")
                            box->setChecked(0);

                        layoutSpi->addWidget(box,++s,1);
                        DynamicTestSpi.push_back(box);
                    }
                }
                }
                /*If the Name of the interfaces value is USB then it will fill the USB TAB */
                else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[1] ].asString() == "USB" ){
                    /*The s count the lines in the USB Scroll area*/
                    s=0;
                    /*create checkBox "valid"*/
                    /*If the "state" is ON then the checkBox is checked */
                    QCheckBox *valide = new QCheckBox("USB",this);
                        if (JSON["interfaces"][j]["state"  ].asString()== "ON")
                            valide->setChecked(1);
                        else
                            valide->setChecked(0);
                        interfaces.push_back(valide);
                        layoutUSB->addWidget(valide,s,0);

                        for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                            if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                            /*Create labels*/
                                Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                                layoutUSB->addWidget(Label, ++s,0);
                            }

                            if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                QComboBox *combo = new QComboBox( this );
                                combo->setEditable( false );
                                combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                combo->addItem(tr("921600"));
                                combo->addItem(tr("460800"));
                                combo->addItem(tr("230400"));
                                combo->addItem(tr("115200"));
                                combo->addItem(tr("57600"));
                                combo->addItem(tr("56000"));
                                combo->addItem(tr("38400"));
                                combo->addItem(tr("19200"));
                                combo->addItem(tr("14400"));
                                combo->addItem(tr("9600"));
                                combo->addItem(tr("4800"));
                                combo->addItem(tr("2400"));
                                combo->addItem(tr("1200"));
                                layoutUSB->addWidget(combo, s,1);

                                valueUSBCombo.push_back(combo);
                                valueUSB.push_back(NULL);

                            }

                            else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

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

                            QLabel *labelRequirement = newLabel("");
                            layoutUSB->addWidget(labelRequirement,s,2);

                            QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticUSB()));
                            layoutUSB->addWidget(checkAllTestStatic,++s,0);

                            QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicUSB()));
                            layoutUSB->addWidget(checkAllTestDynamic,s,1);



                            /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["USB_static_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_static_tests"][j][JSON["USB_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                                if( JSON["USB_static_tests"][j]["state"].asString() == "ON" )
                                    box->setChecked(1);
                                if(JSON["USB_static_tests"][j]["state"].asString() == "OFF")
                                    box->setChecked(0);

                                layoutUSB->addWidget(box,++s,0);
                                staticTestUSB.push_back(box);
                            }
                            /* ************************  Dynamic   **********************/
                            s-= staticTestUSB.size();
                            for (unsigned int j = 0; j < JSON["USB_dynamic_tests"].size()  ; j++){
                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USB_dynamic_tests"][j][JSON["USB_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                                if( JSON["USB_dynamic_tests"][j]["state"].asString() == "ON" )
                                    box->setChecked(1);
                                if(JSON["USB_dynamic_tests"][j]["state"].asString() == "OFF")
                                    box->setChecked(0);

                                layoutUSB->addWidget(box,++s,1);
                                DynamicTestUSB.push_back(box);
                            }
                            for(int i=0;i<10; i++){
                                QLabel * label= newLabel("");
                                layoutUSB->addWidget(label,++s,0);
                            }
                        }
                }
                /*If the Name of the interfaces value is CAN then it will fill the CAN TAB */
                else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "CAN" ){
                    /*The s counter count the lines in the scroll area*/
                    s=0;
                    /*Create a checkbox*/
                    QCheckBox *valide = new QCheckBox("CAN",this);
                        if (JSON["interfaces"][j]["state"  ].asString()== "ON")
                            valide->setChecked(1);
                        else
                            valide->setChecked(0);

                        interfaces.push_back(valide);
                        layoutCAN->addWidget(valide,s,0);
                        for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                            if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                                Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                                layoutCAN->addWidget(Label, ++s,0);
                            }

                            if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                                QComboBox *combo = new QComboBox( this );
                                combo->setEditable( false );
                                combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                                combo->addItem(tr("921600"));
                                combo->addItem(tr("460800"));
                                combo->addItem(tr("230400"));
                                combo->addItem(tr("115200"));
                                combo->addItem(tr("57600"));
                                combo->addItem(tr("56000"));
                                combo->addItem(tr("38400"));
                                combo->addItem(tr("19200"));
                                combo->addItem(tr("14400"));
                                combo->addItem(tr("9600"));
                                combo->addItem(tr("4800"));
                                combo->addItem(tr("2400"));
                                combo->addItem(tr("1200"));
                                layoutCAN->addWidget(combo, s,1);

                                valueCANCombo.push_back(combo);
                                valueCAN.push_back(NULL);
                            }
                            else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                                lineEdit = new QLineEdit(this);
                                lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                                lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                                layoutCAN->addWidget(lineEdit, s,1);

                                valueCANCombo.push_back(NULL);
                                valueCAN.push_back(lineEdit);
                            }
                        }
                        if(JSON["CAN_static_tests"] != 0){

                            QLabel *labelBlData = newLabel("Static :");
                            layoutCAN->addWidget(labelBlData,++s,0);


                            QLabel *labelDynamic = newLabel("Dynamic :");
                            layoutCAN->addWidget(labelDynamic,s,1);

                            QLabel *labelRequirement = newLabel("");
                            layoutCAN->addWidget(labelRequirement,s,2);


                            QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticCAN()));
                            layoutCAN->addWidget(checkAllTestStatic,++s,0);

                            QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                            connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicCAN()));
                            layoutCAN->addWidget(checkAllTestDynamic,s,1);



                            /* ************************  Static  **********************/
                            for (unsigned int j = 0; j < JSON["CAN_static_tests"].size()  ; j++){

                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["CAN_static_tests"][j][JSON["CAN_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                                if( JSON["CAN_static_tests"][j]["state"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["CAN_static_tests"][j]["state"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutCAN->addWidget(box,++s,0);
                                staticTestCAN.push_back(box);
                            }

                            /* ************************  Dynamic   **********************/
                            s-= staticTestCAN.size();
                            for (unsigned int j = 0; j < JSON["CAN_dynamic_tests"].size()  ; j++){
                                QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["CAN_dynamic_tests"][j][JSON["CAN_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                                if( JSON["CAN_dynamic_tests"][j]["state"].asString() == "ON" )
                                       box->setChecked(1);
                                if(JSON["CAN_dynamic_tests"][j]["state"].asString() == "OFF")
                                       box->setChecked(0);

                                layoutCAN->addWidget(box,++s,1);
                                DynamicTestCAN.push_back(box);
                            }
                        }
                }

                else if (JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "FDCAN" ){

                    s=0;
                    QCheckBox *valide = new QCheckBox("FDCAN",this);
                        if (JSON["interfaces"][j]["state"  ].asString()== "ON")
                            valide->setChecked(1);
                        else
                            valide->setChecked(0);

                        interfaces.push_back(valide);
                        layoutFDCAN->addWidget(valide,s,0);
                    for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                        if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){

                            Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));
                            layoutFDCAN->addWidget(Label, ++s,0);
                        }

                        if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("921600"));
                            combo->addItem(tr("460800"));
                            combo->addItem(tr("230400"));
                            combo->addItem(tr("115200"));
                            combo->addItem(tr("57600"));
                            combo->addItem(tr("56000"));
                            combo->addItem(tr("38400"));
                            combo->addItem(tr("19200"));
                            combo->addItem(tr("14400"));
                            combo->addItem(tr("9600"));
                            combo->addItem(tr("4800"));
                            combo->addItem(tr("2400"));
                            combo->addItem(tr("1200"));
                            layoutFDCAN->addWidget(combo, s,1);
                            valueFDCANCombo.push_back(combo);
                            valueFDCAN.push_back(NULL);
                        }

                        else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){                                  // Line Edit

                            lineEdit = new QLineEdit(this);
                            lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                            lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                            layoutFDCAN->addWidget(lineEdit, s,1);

                            valueFDCANCombo.push_back(NULL);
                            valueFDCAN.push_back(lineEdit);
                        }
                    }

                    if(JSON["FDCAN_static_tests"] != 0){

                        QLabel *labelBlData = newLabel("Static :");
                        layoutFDCAN->addWidget(labelBlData,++s,0);


                        QLabel *labelDynamic = newLabel("Dynamic :");
                        layoutFDCAN->addWidget(labelDynamic,s,1);

                        QLabel *labelRequirement = newLabel("");
                        layoutFDCAN->addWidget(labelRequirement,s,2);

                        QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStaticFDCAN()));
                        layoutFDCAN->addWidget(checkAllTestStatic,++s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamicFDCAN()));
                        layoutFDCAN->addWidget(checkAllTestDynamic,s,1);


                        /* ************************  Static  **********************/
                        for (unsigned int j = 0; j < JSON["FDCAN_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["FDCAN_static_tests"][j][JSON["FDCAN_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["FDCAN_static_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["FDCAN_static_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutFDCAN->addWidget(box,++s,0);
                            staticTestFDCAN.push_back(box);
                        }

                        /* ************************  Dynamic   **********************/
                        s-= staticTestFDCAN.size();
                        for (unsigned int j = 0; j < JSON["FDCAN_dynamic_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["FDCAN_dynamic_tests"][j][JSON["FDCAN_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["FDCAN_dynamic_tests"][j]["state"].asString() == "ON" )
                                   box->setChecked(1);
                            if(JSON["FDCAN_dynamic_tests"][j]["state"].asString() == "OFF")
                                   box->setChecked(0);

                            layoutFDCAN->addWidget(box,++s,1);
                            DynamicTestFDCAN.push_back(box);
                        }
                    }
                }

                else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[4] ].asString() == "USART" ){
                    s=0;
                    QCheckBox *valide = new QCheckBox("USART",this);
                    if (JSON["interfaces"][j]["state"  ].asString()== "ON")
                        valide->setChecked(1);
                    else
                        valide->setChecked(0);

                    interfaces.push_back(valide);
                    layoutUsart->addWidget(valide,s,0);
                    for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){

                        if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){
                        Label = newSubLabel(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));

                           layoutUsart->addWidget(Label, ++s,0);}

                        if (JSON["interfaces"][j].getMemberNames()[k] == "Baudrate"){

                            QComboBox *combo = new QComboBox( this );
                            combo->setEditable( false );
                            combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                            combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                            combo->addItem(tr("921600"));
                            combo->addItem(tr("460800"));
                            combo->addItem(tr("230400"));
                            combo->addItem(tr("115200"));
                            combo->addItem(tr("57600"));
                            combo->addItem(tr("56000"));
                            combo->addItem(tr("38400"));
                            combo->addItem(tr("19200"));
                            combo->addItem(tr("14400"));
                            combo->addItem(tr("9600"));
                            combo->addItem(tr("4800"));
                            combo->addItem(tr("2400"));
                            combo->addItem(tr("1200"));
                            layoutUsart->addWidget(combo, s,1);
                            valueUsartCombo.push_back(combo);
                            valueUsart.push_back(NULL);

                        }
                        else if (JSON["interfaces"][j].getMemberNames()[k] != "Name" && JSON["interfaces"][j].getMemberNames()[k] != "state" ){

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

                        QLabel *labelRequirement = newLabel("");
                        layoutUsart->addWidget(labelRequirement,s,2);

                        QPushButton *checkAllTestStatic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                        layoutUsart->addWidget(checkAllTestStatic,++s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select/Unselect",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                        layoutUsart->addWidget(checkAllTestDynamic,s,1);



                        /* ************************  Static  **********************/
                        for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){

                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_static_tests"][j][JSON["USART_static_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["USART_static_tests"][j]["state"].asString() == "ON" )
                                box->setChecked(1);
                            if(JSON["USART_static_tests"][j]["state"].asString() == "OFF")
                                box->setChecked(0);

                            layoutUsart->addWidget(box,++s,0);
                            staticTest.push_back(box);
                        }
                        /* ************************  Dynamic   **********************/
                        s-= staticTest.size();
                        for (unsigned int j = 0; j < JSON["USART_dynamic_tests"].size()  ; j++){


                            QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_dynamic_tests"][j][JSON["USART_dynamic_tests"][j].getMemberNames()[2]].asString()) ,this);

                            if( JSON["USART_dynamic_tests"][j]["state"].asString() == "ON" )
                                box->setChecked(1);
                            if(JSON["USART_dynamic_tests"][j]["state"].asString() == "OFF")
                                box->setChecked(0);
                            layoutUsart->addWidget(box,++s,1);
                            DynamicTest.push_back(box);
                        }
                    }
                }
            }
        }
    }
    Affiche();
}

/*The "onSaveChanegeButton" will save the changes that the user was changed*/

void Read::onSaveChanegeButton(){
    /*The "Mandatory" function will check and test if all the lineEdit are not empty */

    if(!Mandatory()){

        for(unsigned int i=0; i< additionalMemory.size();i++)
         if(additionalMemory[i]!= NULL && (additionalMemory[i]->text()!= ""|| additionalMemory[i]->text()!= "0x" ))
             additionalMemory[i]->setStyleSheet("");

        for(unsigned int i=0; i< value.size();i++)
            if(value[i]!= NULL && (value[i]->text() != "" ||value[i]->text() != "0x") )
                value[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueUsart.size();i++)
            if(valueUsart[i]!= NULL &&( valueUsart[i]->text() != ""||valueUsart[i]->text() != "0x"))
                valueUsart[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueSpi.size();i++)
            if(valueSpi[i]!= NULL &&( valueSpi[i]->text() != ""||valueSpi[i]->text() != "0x"))
                valueSpi[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueCAN.size();i++)
            if(valueCAN[i]!= NULL && (valueCAN[i]->text() != ""||valueCAN[i]->text() != "0x"))
                valueCAN[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueFDCAN.size();i++)
            if(valueFDCAN[i]!= NULL &&( valueFDCAN[i]->text() != ""||valueFDCAN[i]->text() != "0x"))
                valueFDCAN[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueI2C.size();i++)
            if(valueI2C[i]!= NULL && (valueI2C[i]->text() != ""||valueI2C[i]->text() != "0x"))
                valueI2C[i]->setStyleSheet("");

        for(unsigned int i=0; i< valueUSB.size();i++)
            if(valueUSB[i]!= NULL && (valueUSB[i]->text() != ""||valueUSB[i]->text() != "0x"))
                valueUSB[i]->setStyleSheet("");
       }
    /*If the Mandatory return True then it save to the file*/
    if(Mandatory()){
        //  ***************Save**************
        for(unsigned int i=0; i< additionalMemory.size();i++)
        if(additionalMemory[i]!= NULL && (additionalMemory[i]->text() != ""|| additionalMemory[i]->text() != "0x" ))
            additionalMemory[i]->setStyleSheet("");


        for(unsigned int i=0; i< value.size();i++)
            if(value[i]!= NULL && (value[i]->text() != "" ||value[i]->text() != "0x") )
                value[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueUsart.size();i++)
            if(valueUsart[i]!= NULL &&( valueUsart[i]->text() != ""||valueUsart[i]->text() != "0x"))
                valueUsart[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueSpi.size();i++)
            if(valueSpi[i]!= NULL &&( valueSpi[i]->text() != ""||valueSpi[i]->text() != "0x"))
                valueSpi[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueCAN.size();i++)
            if(valueCAN[i]!= NULL && (valueCAN[i]->text() != ""||valueCAN[i]->text() != "0x"))
                valueCAN[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueFDCAN.size();i++)
            if(valueFDCAN[i]!= NULL &&( valueFDCAN[i]->text() != ""||valueFDCAN[i]->text() != "0x"))
                valueFDCAN[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueI2C.size();i++)
            if(valueI2C[i]!= NULL && (valueI2C[i]->text() != ""||valueI2C[i]->text() != "0x"))
                valueI2C[i]->setStyleSheet("");
        for(unsigned int i=0; i< valueUSB.size();i++)
            if(valueUSB[i]!= NULL && (valueUSB[i]->text() != ""||valueUSB[i]->text() != "0x"))
                valueUSB[i]->setStyleSheet("");
        /*"Plateform" Function will save the the Platform to the JsonFile */
        Plateform();
        /*The "Test" will save all the dynamic and the static test to the Json File */
        Test();
        /*The "interfaces" Function will save the interface to the JsonFile */
        Interfaces();
        /*if the New File is checked then it ask you a new path */
        if(1){

            QString NewfileName = QFileDialog::getSaveFileName(this,tr("browse"), filename, "json File(*.json)");
            std::ofstream JSONFILE;
            JSONFILE.open(NewfileName.toLocal8Bit().constData());
            Json::StyledWriter styledWriter;
            JSONFILE << styledWriter.write(JSON);
            JSONFILE.close();
            additionalMemory.clear();
            addmemory3=0;
            QMessageBox::information(this,"Done","New File successful created");
        }


    }
    else {
        // *************** Return to edit ***************
        QMessageBox::warning(this,"Warning","some field are empty");
    }





}
/*when we click to the button of the req usart test it check all the requirement*/
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
/*when we click to the button of the Dynamic Test it check all the USART synamic test */
void Read::onCheckAllTestDynamic(){

    for (unsigned int i=0; i< DynamicTest.size();i++){

        if (counterDynamic==0)
        DynamicTest[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTest[i]->setCheckState(Qt::Checked);
    }
    counterDynamic= 1-counterDynamic;
}
/*By clicking the button of the static test it check all the Usart Static test */
void Read::onCheckAllTestStatic(){

    for (unsigned int i=0; i< staticTest.size();i++){
        if (counterStatic ==0)
            staticTest[i]->setCheckState(Qt::Unchecked);
        else
            staticTest[i]->setCheckState(Qt::Checked);
    }
    counterStatic = 1-counterStatic;

}

void Read::onCheckAllTestDynamicCAN(){

    for (unsigned int i=0; i< DynamicTestCAN.size();i++){

        if (counterDynamicCAN==0)
            DynamicTestCAN[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTestCAN[i]->setCheckState(Qt::Checked);
    }
    counterDynamicCAN= 1-counterDynamicCAN;
}

void Read::onCheckAllTestStaticCAN(){

    for (unsigned int i=0; i< staticTestCAN.size();i++){
        if (counterStaticCAN ==0)
            staticTestCAN[i]->setCheckState(Qt::Unchecked);
        else
            staticTestCAN[i]->setCheckState(Qt::Checked);
    }

    counterStaticCAN  = 1-counterStaticCAN;

}
void Read::onCheckAllTestReqCAN(){}

void Read::onCheckAllTestDynamicFDCAN(){
    for (unsigned int i=0; i< DynamicTestFDCAN.size();i++){

        if (counterDynamicFDCAN==0)
            DynamicTestFDCAN[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTestFDCAN[i]->setCheckState(Qt::Checked);
    }

    counterDynamicFDCAN= 1-counterDynamicFDCAN;

}
void Read::onCheckAllTestStaticFDCAN(){
    for (unsigned int i=0; i< staticTestFDCAN.size();i++){
        if (counterStaticFDCAN ==0)
            staticTestFDCAN[i]->setCheckState(Qt::Unchecked);
        else
            staticTestFDCAN[i]->setCheckState(Qt::Checked);
        }
    counterStaticFDCAN= 1-counterStaticFDCAN;
}
void Read::onCheckAllTestReqFDCAN(){}


void Read::onCheckAllTestDynamicSPI(){
    for (unsigned int i=0; i< DynamicTestSpi.size();i++){
        if (counterDynamicSPI==0)
            DynamicTestSpi[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTestSpi[i]->setCheckState(Qt::Checked);
    }
    counterDynamicSPI= 1-counterDynamicSPI;
}

void Read::onCheckAllTestStaticSPI(){
    for (unsigned int i=0; i< staticTestSpi.size();i++){
        if (counterStaticSPI ==0)
            staticTestSpi[i]->setCheckState(Qt::Unchecked);
        else
            staticTestSpi[i]->setCheckState(Qt::Checked);
    }
    counterStaticSPI= 1-counterStaticSPI;
}
void Read::onCheckAllTestReqSPI(){}

void Read::onCheckAllTestDynamicI2C(){

    for (unsigned int i=0; i< DynamicTestI2C.size();i++){
        if (counterDynamicI2C==0)
            DynamicTestI2C[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTestI2C[i]->setCheckState(Qt::Checked);
         }
    counterDynamicI2C= 1-counterDynamicI2C;
}

void Read::onCheckAllTestStaticI2C(){
    for (unsigned int i=0; i< staticTestI2C.size();i++){
        if (counterStaticI2C ==0)
            staticTestI2C[i]->setCheckState(Qt::Unchecked);
        else
            staticTestI2C[i]->setCheckState(Qt::Checked);
    }
    counterStaticI2C = 1-counterStaticI2C;
}
void Read::onCheckAllTestReqI2C(){}

void Read::onCheckAllTestDynamicUSB(){
    for (unsigned int i=0; i< DynamicTestUSB.size();i++){
        if (counterDynamicUSB==0)
            DynamicTestUSB[i]->setCheckState(Qt::Unchecked);
        else
            DynamicTestUSB[i]->setCheckState(Qt::Checked);
    }
    counterDynamicUSB= 1-counterDynamicUSB;
}

void Read::onCheckAllTestStaticUSB(){
    for (unsigned int i=0; i< staticTestUSB.size();i++){
        if (counterStaticUSB ==0)
        staticTestUSB[i]->setCheckState(Qt::Unchecked);
        else
            staticTestUSB[i]->setCheckState(Qt::Checked);
    }
    counterStaticUSB= 1-counterStaticUSB;
}
void Read::onCheckAllTestReqUSB(){}

/*The requirement just work in the USART protocol communication*/
void Read::requirement(){

/********************************************************************************************************************/
/******************      The index of all vector must be mines 1 of the real index static/dynamic test     **********/
/********************************************************************************************************************/

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

/*Set the Path to the filename*/
void Read::setPath(QString f){
    filename=f;
}

/*"newLabel" create a label */
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
/*"newLabel" create a subLabel */
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
/*The affiche function will affiche the data in the scroll area widget */
/*Affich will only the data only in the Plateform*/

void Read::Affiche(){

    QString ch= QString::fromStdString(member[getIndex("Mode",newfile)[0]]);
    QLabel* f= newLabel(ch);
    layout->addWidget(f,++page,0);
    QString ch1 =QString::fromStdString(JSON[member[getIndex("Mode",newfile)[0]]][getIndex("Mode",newfile)[1]].getMemberNames()[getIndex("Mode",newfile)[2]]);
    QLabel* f1 =newSubLabel(ch1);
    layout->addWidget(f1,++page,0);
    int modeindex=getIndex("Mode",newfile)[3];
    layout->addWidget(valueCombo[getIndex("Mode",newfile)[3]],page,1);
    /*Add the data to the widget*/
    for (unsigned int i =0; i< member.size();i++){
        if(        !(member[i]== "memory") && !(member[i]== "interfaces")
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
                && !(member[i]== "USB_static_tests")
                && !(member[i]== "platform")
                 ){
                    /*Add all the label to the widget*/
            QString t=  QString::fromStdString( member[i] );
            QLabel *tx= newLabel(t);
            layout->addWidget(tx,++page,0);

            for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){
                 for (unsigned int k =0; k<JSON[member[i]][j].getMemberNames().size() ; k++){
                    /* Add the Lables to the widget */
                    QString T=QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]);
                    QLabel *T1= newSubLabel(T);
                    layout->addWidget( T1,++page,0);

                    if(value[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]),newfile )[3]] && i<= value.size())
                        layout->addWidget(value[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]) ,newfile)[3]],page,1);
                    else
                        layout->addWidget(valueCombo[getIndex( QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]),newfile )[3]],page,1);
                }
            }
        }
    }
    /*By giving the name of a value the function "getIndex" will retur a vector of 4 member */
    int indexName = getIndex("Name",newfile)[3];
    int indexStart = getIndex("Start",newfile)[3];
    int indexEnd = getIndex("End",newfile)[3];

    QString ch2= QString::fromStdString(member[getIndex("End",newfile)[0]]);
    QLabel* f2= newLabel(ch2);
    layout->addWidget(f2,++page,0);

    /* Create the button of the add memory*/
    QPushButton *addmemory= new QPushButton("ADD",this);
    layout->addWidget(addmemory,++page,0);
    connect(addmemory,SIGNAL (clicked()  ), this, SLOT( onAddMemory() ));

    /*Create and add the Name Label*/
    QString ch4 =QString::fromStdString(JSON[member[getIndex("Name",newfile)[0]]][getIndex("Name",newfile)[1]].getMemberNames()[getIndex("Name",newfile)[2]]);
    QLabel* f4 =newSubLabel(ch4);
    layout->addWidget(f4,++page,0);

    /*Create and add the Start Label*/
    QString ch5 =QString::fromStdString(JSON[member[getIndex("Start",newfile)[0]]][getIndex("Start",newfile)[1]].getMemberNames()[getIndex("Start",newfile)[2]]);
    QLabel* f5 =newSubLabel(ch5);
    layout->addWidget(f5,page,1);

    /*Create and add the End label*/
    QString ch3 =QString::fromStdString(JSON[member[getIndex("End",newfile)[0]]][getIndex("End",newfile)[1]].getMemberNames()[getIndex("End",newfile)[2]]);
    QLabel* f3 =newSubLabel(ch3);
    layout->addWidget(f3,page,2);

    /*If new file then add just one line*/
    /*else it add all existant*/

    if(newfile){
        onAddMemory();
    }


    if(!newfile){
        for (unsigned int j = 0; j < JSON["memory"].size() ; j++){
            /*Add the memory to the layout*/

            layout->addWidget(value[indexName],++page,0);
            layout->addWidget(value[indexStart],page,1);
            layout->addWidget(value[indexEnd],page,2);
            indexName+=3;
            indexStart+=3;
            indexEnd +=3;
        }
    }
}

/*The "getindex" Function return a vector of Four int */
/*The first item is the  i : the number of the memeber*/
/*The second item is the j : the value of the memeber */
/*The third item is the  k : the object of values mameber*/
/*The fourth item is the value of the object values member*/

std::vector<unsigned int> Read::getIndex( QString ch, bool NEW){

    std::vector<unsigned int> result;
    unsigned int index=0;
    for (unsigned int i=0; i<JSON.getMemberNames().size(); i++){
        if( NEW && member[i] !="interfaces" && member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests" &&
                member[i] !="SPI_static_tests" && member[i] !="SPI_dynamic_tests" &&
                    member[i] !="I2C_static_tests" && member[i] !="I2C_dynamic_tests" &&
                                 member[i] !="CAN_static_tests" && member[i] !="CAN_dynamic_tests" &&
                    member[i] !="FDCAN_static_tests" && member[i] !="FDCAN_dynamic_tests" &&
                    member[i] !="USB_static_tests" && member[i] !="USB_dynamic_tests"&& member[i]!="memory" ){
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
        }
        }


        else if (member[i] !="interfaces" && member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests" &&
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
            }
        }


    }
}

/*The "Mandatry" function will check all the editLine if empty or "0x" */
/*If not empty or not "0x" it will return true */
/*else it will return false*/
bool Read::Mandatory(){
    int indexMemory=getIndex("End",newfile)[3];
    int indexUsart= getIndex("usart_bl_version",newfile)[3];
    int indexI2C= getIndex("i2c_bl_version",newfile)[3];
    int indexSpi= getIndex("spi_bl_version",newfile)[3];
    int indexCan= getIndex("can_bl_version",newfile)[3];
    int indexFDCan= getIndex("fd_can_bl_version",newfile)[3];
    int indexUsb= getIndex("usb_bl_version",newfile)[3];

    bool t =true;
    if (newfile){
        for(unsigned int i=0; i< value.size();i++){
            if(value[i]!= NULL && (value[i]->text()== ""|| value[i]->text()== "0x" )){

                if ((i == indexUsart && !UsartState)||(i == indexI2C && !I2cState)||
                        (i == indexSpi && !SpiState) ||(i == indexCan && !CanState) ||
                        (i == indexFDCan && !FDCanState )||(i == indexUsb && !UsbState))
                    ;
                else if (i == indexMemory) break;
                else {
                    value[i]->setStyleSheet("border: 1.5px solid red");
                    if(t== true) t=false;
                }
            }
        }
        if(value[value.size()-1]->text()== ""|| value[value.size()-1]->text()== "0x" ){
            value[value.size()-1]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
        }
    }

    if(!newfile){
        for(unsigned int i=0; i< value.size();i++){
            if(value[i]!= NULL && (value[i]->text()== ""|| value[i]->text()== "0x" )){
                value[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }

    }

    if(!newfile || UsartState){
        for(unsigned int i=0; i< valueUsart.size();i++){
            if(valueUsart[i]!= NULL && (valueUsart[i]->text()== ""|| valueUsart[i]->text()== "0x" )){
                valueUsart[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }
    }

    if(!newfile || I2cState){
        for(unsigned int i=0; i< valueI2C.size();i++){
        if(valueI2C[i]!= NULL && (valueI2C[i]->text()== ""|| valueI2C[i]->text()== "0x" )){
            valueI2C[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }
    }

    if(!newfile || SpiState){
        for(unsigned int i=0; i< valueSpi.size();i++){
        if(valueSpi[i]!= NULL && (valueSpi[i]->text()== ""|| valueSpi[i]->text()== "0x" )){
            valueSpi[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }
    }

    if(!newfile|| CanState){
        for(unsigned int i=0; i< valueCAN.size();i++){
        if(valueCAN[i]!= NULL && (valueCAN[i]->text()== ""|| valueCAN[i]->text()== "0x" )){
            valueCAN[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }
    }

    if(!newfile|| FDCanState){
        for(unsigned int i=0; i< valueFDCAN.size();i++){
        if(valueFDCAN[i]!= NULL && (valueFDCAN[i]->text()== ""|| valueFDCAN[i]->text()== "0x" )){
            valueFDCAN[i]->setStyleSheet("border: 1.5px solid red");
            if(t== true) t=false;
            }
        }
    }

    if(!newfile|| UsbState){
        for(unsigned int i=0; i< valueUSB.size();i++){
        if(valueUSB[i]!= NULL && (valueUSB[i]->text()== ""|| valueUSB[i]->text()== "0x" )){
            valueUSB[i]->setStyleSheet("border: 1.5px solid red");
            if(t == true) t=false;
            }
        }
    }


    for(unsigned int i=0; i< additionalMemory.size();i++){
        if(additionalMemory[i]!= NULL && (additionalMemory[i]->text()== "" || additionalMemory[i]->text()== "0x" )){
            additionalMemory[i]->setStyleSheet("border: 1.5px solid red");
            if(t == true) t=false;

        }
    }

    return t;
}

/*The role of the "Plateform" function is to create data in the JsonFile*/
void Read::Plateform(){

    unsigned int f=0;
    unsigned int U=0;
    for (unsigned int i = 0; i < member.size() ; i++){
        if (    member[i] !="USART_static_tests"  &&  member[i] !="USART_dynamic_tests"  &&
                member[i] !="SPI_static_tests"    &&  member[i] !="SPI_dynamic_tests"    &&
                member[i] !="I2C_static_tests"    &&  member[i] !="I2C_dynamic_tests"    &&
                member[i] !="CAN_static_tests"    &&  member[i] !="CAN_dynamic_tests"    &&
                member[i] !="FDCAN_static_tests"  &&  member[i] !="FDCAN_dynamic_tests"  &&
                member[i] !="USB_static_tests"    &&  member[i] !="USB_dynamic_tests"    &&
                member[i] !="interfaces" ){//&& member[i] !="memory"


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

                        if(valueCombo[f]->currentText() == "byArea")
                        {
                           JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="byArea";
                           f++;
                           break;
                        }

                        if(valueCombo[f]->currentText() == "bySectors")
                        {
                           JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] ="bySectors";
                           f++;
                           break;
                        }
                    }
                }
            }
        }
    }
/*the memory add by the user is added to the json*/
    if(additionalMemory.size()> 0){

        int j1=JSON["memory"].size();
        int k1=0;
        for (unsigned int i1=0;i1 <( additionalMemory.size() /3);i1++){

            JSON["memory"][j1][ "Name"] =additionalMemory[k1++]->text().toLocal8Bit().constData();
            JSON["memory"][j1]["Start"] =additionalMemory[k1++]->text().toLocal8Bit().constData();
            JSON["memory"][j1++][ "End"] =additionalMemory[k1++]->text().toLocal8Bit().constData();
        }
    }
}

/*The test function is designed to create the static and the dynamic testes */
void Read::Test(){

    /*Parse the data in the vector of the static/dynamic tests*/
    for (unsigned int i = 0; i < member.size(); i++) {

        if (member[i] == "USART_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTest.size();j++){

                if (DynamicTest[j]->checkState() == Qt::Checked)
                    JSON["USART_dynamic_tests"][j]["state"]= "ON";

                else if(DynamicTest[j]->checkState() == Qt::Unchecked)
                    JSON["USART_dynamic_tests"][j]["state"]= "OFF";
            }
        }


        if (member[i] == "USART_static_tests" ){
            for (unsigned int j=0; j < staticTest.size() ;j++){
                if ( staticTest[j]->checkState() == Qt::Checked )
                    JSON["USART_static_tests"][j]["state"]= "ON";

                else if(staticTest[j]->checkState() == Qt::Unchecked)
                    JSON["USART_static_tests"][j]["state"]= "OFF";
            }
        }

        if (member[i] == "SPI_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTestSpi.size();j++){

                if (DynamicTestSpi[j]->checkState() == Qt::Checked)
                      JSON["SPI_dynamic_tests"][j]["state"]= "ON";

                else if(DynamicTestSpi[j]->checkState() == Qt::Unchecked)
                    JSON["SPI_dynamic_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "SPI_static_tests" ){
            for (unsigned int j=0; j < staticTestSpi.size() ;j++){

                if ( staticTestSpi[j]->checkState() == Qt::Checked )
                    JSON["SPI_static_tests"][j]["state"]= "ON";

                else if(staticTestSpi[j]->checkState() == Qt::Unchecked)
                    JSON["SPI_static_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "I2C_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTestI2C.size();j++){

              if (DynamicTestI2C[j]->checkState() == Qt::Checked)
                    JSON["I2C_dynamic_tests"][j]["state"]= "ON";

              else if(DynamicTestI2C[j]->checkState() == Qt::Unchecked)
                  JSON["I2C_dynamic_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "I2C_static_tests" ){
            for (unsigned int j=0; j < staticTestI2C.size() ;j++){

                if ( staticTestI2C[j]->checkState() == Qt::Checked )
                    JSON["I2C_static_tests"][j]["state"]= "ON";

                else if(staticTestI2C[j]->checkState() == Qt::Unchecked)
                    JSON["I2C_static_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "CAN_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTestCAN.size();j++){
              if (DynamicTestCAN[j]->checkState() == Qt::Checked)
                    JSON["CAN_dynamic_tests"][j]["state"]= "ON";

              else if(DynamicTestCAN[j]->checkState() == Qt::Unchecked)
                 JSON["CAN_dynamic_tests"][j]["state"]= "OFF";

            }
        }


        if (member[i] == "CAN_static_tests" ){
            for (unsigned int j=0; j < staticTestCAN.size() ;j++){
                if ( staticTestCAN[j]->checkState() == Qt::Checked )
                    JSON["CAN_static_tests"][j]["state"]= "ON";

                else if(staticTestCAN[j]->checkState() == Qt::Unchecked)
                    JSON["CAN_static_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "FDCAN_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTestFDCAN.size();j++){

                if (DynamicTestFDCAN[j]->checkState() == Qt::Checked)
                    JSON["FDCAN_dynamic_tests"][j]["state"]= "ON";

                else if(DynamicTestFDCAN[j]->checkState() == Qt::Unchecked)
                    JSON["FDCAN_dynamic_tests"][j]["state"]= "OFF";

            }
        }

        if (member[i] == "FDCAN_static_tests" ){
            for (unsigned int j=0; j < staticTestFDCAN.size() ;j++){

                if ( staticTestFDCAN[j]->checkState() == Qt::Checked )
                    JSON["FDCAN_static_tests"][j]["state"]= "ON";

                else if(staticTestFDCAN[j]->checkState() == Qt::Unchecked)
                    JSON["FDCAN_static_tests"][j]["state"]= "OFF";


            }
        }

       if (member[i] == "USB_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTestUSB.size();j++){

                if (DynamicTestUSB[j]->checkState() == Qt::Checked)
                    JSON["USB_dynamic_tests"][j]["state"]= "ON";

                else if(DynamicTestUSB[j]->checkState() == Qt::Unchecked)
                    JSON["USB_dynamic_tests"][j]["state"]= "OFF";

            }
        }

       if (member[i] == "USB_static_tests" ){
            for (unsigned int j=0; j < staticTestUSB.size() ;j++){

                if ( staticTestUSB[j]->checkState() == Qt::Checked )
                    JSON["USB_static_tests"][j]["state"]= "ON";

                else if(staticTestUSB[j]->checkState() == Qt::Unchecked)
                    JSON["USB_static_tests"][j]["state"]= "OFF";

            }
        }
    }
}

/*save the Interfaces member to jsonFile */
void Read::Interfaces(){
    unsigned int U=0;
    unsigned int UI2C=0;
    unsigned int USPI=0;
    unsigned int UCAN=0;
    unsigned int UFDCAN=0;
    unsigned int UUSB=0;

    for (unsigned int i=0; i< member.size();i++){
        if(member[i]=="interfaces"){
            for (unsigned int j = 0; j < JSON["interfaces"].size() ; j++){
                for (unsigned int k = 0; k < JSON["interfaces"][j].getMemberNames().size(); k++){
                    if(JSON["interfaces"][j].getMemberNames()[k] != "Name"
                            &&  JSON["interfaces"][j].getMemberNames()[k] != "state"){


                        if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "I2C"){

                            JSON["interfaces"][j][ "Name"] = "I2C";

                            if (interfaces[j]->checkState() == Qt::Checked)
                                JSON[member[i]][j]["state"]= "ON";
                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                            if (valueI2C[UI2C] != NULL)
                                JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueI2C[UI2C++]->text().toLocal8Bit().constData();

                            else if(valueI2CCombo[UI2C] != NULL) {

                                switch (valueI2CCombo[UI2C]->currentText().toInt()) {

                                    case 400:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="400";
                                        UI2C++;
                                        break;
                                case 4000:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="4000";
                                    UI2C++;
                                    break;




                                    default:
                                        break;
                                }
                            }
                        }

                        else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "SPI"){

                            JSON["interfaces"][j][ "Name"] = "SPI";

                            if (interfaces[j]->checkState() == Qt::Checked)
                                JSON[member[i]][j]["state"]= "ON";

                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                            if (valueSpi[USPI] != NULL &&  JSON["interfaces"][j].getMemberNames()[k]  != "Name")
                                 JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueSpi[USPI++]->text().toLocal8Bit().constData();

                            else if(valueSpiCombo[USPI] != NULL) {
                                switch (valueSpiCombo[USPI]->currentText().toInt()) {
                                    case 400:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="400";
                                        USPI++;
                                        break;

                                case 125:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="125";
                                    USPI++;
                                    break;

                                    case 8000:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="8000";
                                        USPI++;
                                        break;



                                    default:
                                    break;
                                }
                            }
                        }

                        else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[1] ].asString() == "USB")
                        {
                            JSON["interfaces"][j][ "Name"] = "USB";
                            if (interfaces[j]->checkState() == Qt::Checked)
                                JSON[member[i]][j]["state"]= "ON";
                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                            if (valueUSB[UUSB] != NULL &&  JSON["interfaces"][j].getMemberNames()[k]  != "Name")
                                JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueUSB[UUSB++]->text().toLocal8Bit().constData();

                            else if(valueUSBCombo[UUSB] != NULL) {

                                switch (valueUSBCombo[UUSB]->currentText().toInt()) {
                                    case 9600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UUSB++;
                                        break;

                                     case 19200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UUSB++;
                                        break;

                                     case 38400:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="38400";
                                        UUSB++;
                                        break;

                                     case 57600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="57600";
                                        UUSB++;
                                        break;

                                     case 115200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="115200";
                                        UUSB++;
                                        break;

                                     default:
                                        break;

                                }
                            }
                        }

                        else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "CAN"){

                            JSON["interfaces"][j][ "Name"] = "CAN";
                            if (interfaces[j]->checkState() == Qt::Checked)
                                JSON[member[i]][j]["state"]= "ON";

                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                            if (valueCAN[UCAN] != NULL &&  JSON["interfaces"][j].getMemberNames()[k]  != "Name")
                                JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueCAN[UCAN++]->text().toLocal8Bit().constData();

                            else if(valueCANCombo[UCAN] != NULL) {

                                switch (valueCANCombo[UCAN]->currentText().toInt()) {
                                    case 9600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UCAN++;
                                        break;

                                    case 19200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UCAN++;
                                        break;

                                    case 38400:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="38400";
                                        UCAN++;
                                        break;

                                    case 57600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="57600";
                                        UCAN++;
                                        break;

                                    case 115200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="115200";
                                        UCAN++;
                                        break;

                                    default:
                                        break;
                                }
                            }
                        }

                        else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[3] ].asString() == "FDCAN")
                        {
                            JSON["interfaces"][j][ "Name"] = "FDCAN";
                            if (interfaces[j]->checkState() == Qt::Checked)
                                  JSON[member[i]][j]["state"]= "ON";
                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                            if (valueFDCAN[UFDCAN] != NULL&&  JSON["interfaces"][j].getMemberNames()[k]  != "Name")
                                JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueFDCAN[UFDCAN++]->text().toLocal8Bit().constData();

                            else if(valueFDCANCombo[UFDCAN] != NULL) {

                                switch (valueFDCANCombo[UFDCAN]->currentText().toInt()) {
                                    case 9600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UFDCAN++;
                                        break;


                                    case 19200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                        UFDCAN++;
                                        break;


                                    case 38400:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="38400";
                                        UCAN++;
                                        break;


                                    case 57600:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="57600";
                                        UFDCAN++;
                                        break;


                                    case 115200:
                                        JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="115200";
                                        UFDCAN++;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }

                        else if ( JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[4] ].asString() == "USART"){
                            JSON["interfaces"][j][ "Name"] = "USART";
                            if (interfaces[j]->checkState() == Qt::Checked)
                                JSON[member[i]][j]["state"]= "ON";
                            if (interfaces[j]->checkState() == Qt::Unchecked)
                                JSON[member[i]][j]["state"]= "OFF";

                        else if (valueUsart[U] != NULL&&  JSON["interfaces"][j].getMemberNames()[k]  != "Name")
                            JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k] ] =valueUsart[U++]->text().toLocal8Bit().constData();


                        else if(valueUsartCombo[U] != NULL) {

                            switch (valueUsartCombo[U]->currentText().toInt()) {
                                case 9600:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                    U++;
                                    break;

                                case 19200:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="9600";
                                    U++;
                                    break;

                                case 38400:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="38400";
                                    U++;
                                    break;

                                case 57600:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="57600";
                                    U++;
                                    break;

                                case 115200:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="115200";
                                    U++;
                                    break;

                                case 921600:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="921600";
                                    U++;
                                break;
                                case 460800:
                                    JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]] ="460800";
                                    U++;
                                    break;

                                default:
                                    break;

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/*The on add memory will add a three EditLine of the Name Start and the End*/

void Read::onAddMemory(){

    QLineEdit *Name= new QLineEdit(this);
    QLineEdit *Start= new QLineEdit("0x",this);
    QLineEdit *End= new QLineEdit("0x",this);
    additionalMemory.push_back(Name);
    additionalMemory.push_back(Start);
    additionalMemory.push_back(End);
    layout->addWidget(additionalMemory[addmemory3++] ,++page,0);
    layout->addWidget(additionalMemory[addmemory3++],page,1);
    layout->addWidget(additionalMemory[addmemory3++],page,2);
}
