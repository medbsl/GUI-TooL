#include "read.h"
#include "ui_read.h"
#include <fstream>
#include <QDebug>

unsigned int counterRequirement =0;
unsigned int counterStatic =0;
unsigned int counterDynamic =0;
Read::Read(QWidget *parent) : QDialog(parent), ui(new Ui::Read){

    ui->setupUi(this);





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
//****************************      TAB            ****************************//
//*****************************************************************************//
              QTabWidget *Tab= new QTabWidget(this);
              Tab->setGeometry(5,5,995, 835);
              Tab->addTab(scrollArea, "PLateform");
              Tab->addTab(scrollAreaUsart, "Usart");
              Tab->addTab(new QScrollArea(this), "I2C");
              Tab->addTab(new QScrollArea(this), "SPI");
              Tab->addTab(new QScrollArea(this), "CAN");
              Tab->addTab(new QScrollArea(this), "FD_CAN");
//*****************************************************************************//
//****************************    Browse  Button   ***************************//
//*****************************************************************************//


// PushButton

    browseButton = new QPushButton("browse", this);
    browseButton->setGeometry(QRect(QPoint(795, 855),QSize(100, 20)));
    connect(browseButton,SIGNAL (clicked()), this, SLOT(onBrowseButton()));
//*****************************************************************************//
//****************************    Generate Button   ***************************//
//*****************************************************************************//


// PushButton
    QHBoxLayout* layoutButton = new QHBoxLayout( this );
    layoutButton->setContentsMargins(0,0,0,0);
    m_button = new QPushButton("Save changes", this);
    m_button->setGeometry(QRect(QPoint(895, 855),QSize(100, 20)));
    connect(m_button,SIGNAL (clicked()), this, SLOT(onSaveChanegeButton()));

}

Read::~Read()
{
    delete ui;
    staticTest.clear();
    DynamicTest.clear();
    Requirement.clear();
}

void Read::Test(QGridLayout *layout, int s){


    QString add;
    QString add2;
    QString add3;


                        QPushButton *checkAllTestStatic =new QPushButton("ALL Static",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                        layout->addWidget(checkAllTestStatic,s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("ALL Dynamic",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                        layout->addWidget(checkAllTestDynamic,s,1);

                        QPushButton *checkAllTestReq =new QPushButton("ALL Req",this);
                        connect(checkAllTestReq,SIGNAL (clicked()), this, SLOT(onCheckAllTestReq()));
                        layout->addWidget(checkAllTestReq,s++,2);


    add3 = "USART_Req000";
         QCheckBox *checktestRequirement0 =new QCheckBox(add3,this);
         layout->addWidget(checktestRequirement0,s,2);
         Requirement.push_back(checktestRequirement0);


    for(int i=1; i<63;i++){

            if (i<10)
            {
                add  = "USART_S_00" + QString::number(i);
                add2 = "USART_D_00" + QString::number(i);
                add3 = "USART_Req00" + QString::number(i);
            }
            if (i<100 && i>=10)
            {
                add ="USART_S_0" + QString::number(i);
                add2 = "USART_D_0" + QString::number(i);
                add3 = "USART_Req0" + QString::number(i);
            }

        QCheckBox *checktest =new QCheckBox(add,this);
        checktest->setChecked(0);
        QCheckBox *checktestDynamic =new QCheckBox(add2,this);
        checktestDynamic->setChecked(0);
        QCheckBox *checktestRequirement =new QCheckBox(add3,this);
        checktestRequirement->setChecked(0);




        if (i<26){// req
            Requirement.push_back(checktestRequirement);
            DynamicTest.push_back(checktestDynamic);
            staticTest.push_back(checktest);
            layout->addWidget(checktest,s,0);
            layout->addWidget(checktestDynamic,s,1);
            layout->addWidget(checktestRequirement,++s,2);
    }
        if (i>25 && i<35){// Dynamic

            DynamicTest.push_back(checktestDynamic);
            staticTest.push_back(checktest);
            layout->addWidget(checktest,s,0);
            layout->addWidget(checktestDynamic,s++,1);


        }
        if (i>35){// Static


            staticTest.push_back(checktest);
            layout->addWidget(checktest,s++,0);


        }


    }



    for (unsigned int i=0;i< Requirement.size();i++ )
        connect(Requirement[i],SIGNAL (clicked() ), this, SLOT( requirement()));


}

void Read::onBrowseButton(){


    int s=0;
    do{
        filename=QFileDialog::getOpenFileName(
                    this,tr("browse"), "C:/", "json File(*.json)");
    }while( filename.isNull()  );


    QMessageBox::information(this,tr("File Name"), filename);




std::ifstream JSONFILE(filename.toLocal8Bit().constData(), std::ifstream::binary);


JSONFILE >> JSON;
member= JSON.getMemberNames();


 for (unsigned int i = 0; i < member.size(); i++) {

      if (member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests"&& member[i] !="interfaces"){

        //std::cout << member[i] <<" *** "<< member[i]<<endl<<endl;
     QLabel *label = new QLabel(this);
     label->setGeometry(QRect(QPoint(30, 100),QSize(121, 25)));
     label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
     label->setText(QString::fromStdString(member[i]));


     QFont font;
     font.setFamily("MS Shell Dlg 2");
     font.setPointSize(12);
     font.setBold(true);
     label->setFont(font);


        layout->addWidget(label, ++s,0);


     for (unsigned int j = 0; j < JSON[member[i]].size() ; j++){
          for (unsigned int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){



              // Label
                  QLabel *Label = new QLabel(this);
                  Label->setGeometry(QRect(QPoint(50, 138),QSize(176, 25)));
                  Label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                  Label->setText(QString::fromStdString(JSON[member[i]][j].getMemberNames()[k]));


                  QFont fontSTLINK;
                  fontSTLINK.setFamily("MS Shell Dlg 2");
                  fontSTLINK.setPointSize(10);
                  fontSTLINK.setBold(false);
                  Label->setFont(fontSTLINK);

                 layout->addWidget(Label, ++s,0);

              if (JSON[member[i]][j].getMemberNames()[k] == "connect"){

                  QComboBox *combo = new QComboBox( this );
                  combo->setEditable( false );
                  combo->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                  combo->setGeometry(QRect(QPoint(230,50),QSize(176, 23)));
                  combo->addItem(tr("true"));
                  combo->addItem(tr("false"));
                  layout->addWidget(combo, s,1);

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
                  layout->addWidget(combo, s,1);

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
                  layout->addWidget(combo, s,1);

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
                  layout->addWidget(combo, s,1);

                  valueCombo.push_back(combo);
                  value.push_back(NULL);
                  break;
              }
              else {
                  // Line Edit

                      lineEdit = new QLineEdit(this);
                      lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                      lineEdit->setText(QString::fromStdString(JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k] ].asString()));
                      layout->addWidget(lineEdit, s,1);
                      valueCombo.push_back(NULL);
                      value.push_back(lineEdit);

              }















                }
     }
     }



      if (member[i] == "interfaces" && JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[4] ].asString() == "USART"){


                          for (unsigned int k = 0; k < JSON["interfaces"][0].getMemberNames().size(); k++){

                              // Label
                                  QLabel *Label = new QLabel(this);
                                  Label->setGeometry(QRect(QPoint(50, 138),QSize(176, 25)));
                                  Label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                  Label->setText(QString::fromStdString( JSON["interfaces"][0].getMemberNames()[k]));


                                  QFont fontSTLINK;
                                  fontSTLINK.setFamily("MS Shell Dlg 2");
                                  fontSTLINK.setPointSize(10);
                                  fontSTLINK.setBold(false);
                                  Label->setFont(fontSTLINK);

                                 layoutUsart->addWidget(Label, ++s,0);

                              if (JSON["interfaces"][0].getMemberNames()[k] == "Baudrate"){

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
                                  lineEdit->setText(QString::fromStdString((JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[k]]).asString()));
                                  layoutUsart->addWidget(lineEdit, s,1);

                                  valueUsartCombo.push_back(NULL);
                                  valueUsart.push_back(lineEdit);
}





                          }
                    if(JSON["USART_static_tests"] != 0){

                             QLabel *labelBlData = new QLabel(this);
                             labelBlData->setGeometry(QRect(QPoint(20, 136),QSize(121, 100)));
                             labelBlData->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                             labelBlData->setText("Static :");


                             QFont fontBlData;
                             fontBlData.setFamily("MS Shell Dlg 2");
                             fontBlData.setPointSize(12);
                             fontBlData.setBold(true);
                             labelBlData->setFont(fontBlData);
                             layoutUsart->addWidget(labelBlData,++s,0);



                                 QLabel *labelDynamic = new QLabel(this);
                                 labelDynamic->setGeometry(QRect(QPoint(20, 136),QSize(121, 100)));
                                 labelDynamic->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                 labelDynamic->setText("Dynamic :");


                                 QFont fontDynamic;
                                 fontDynamic.setFamily("MS Shell Dlg 2");
                                 fontDynamic.setPointSize(12);
                                 fontDynamic.setBold(true);
                                 labelDynamic->setFont(fontDynamic);

                                 layoutUsart->addWidget(labelDynamic,s,1);

                                     QLabel *labelRequirement = new QLabel(this);
                                     labelRequirement->setGeometry(QRect(QPoint(20, 136),QSize(121, 100)));
                                     labelRequirement->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                                     labelRequirement->setText("Requirement :");


                                     QFont fontRequirement;
                                     fontRequirement.setFamily("MS Shell Dlg 2");
                                     fontRequirement.setPointSize(12);
                                     fontRequirement.setBold(true);
                                     labelRequirement->setFont(fontRequirement);

                                     layoutUsart->addWidget(labelRequirement,s,2);

                                     Read::Test(layoutUsart, ++s);

                            /* ************************  Static  **********************/
                         for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){
                             for(unsigned int k =0 ;k< staticTest.size();k++)

                                if( QString::compare(staticTest[k]->text(), QString::fromStdString(JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[1] ].asString()), Qt::CaseInsensitive) == 0)

                                    staticTest[ k ]->setChecked(1);


                    }
                            /* ************************  Dynamic   **********************/

                 for (unsigned int j = 0; j < JSON["USART_dynamic_tests"].size()  ; j++){
                     for(unsigned int k =0 ;k< 11;k++){

                        if(DynamicTest[k]->text() == QString::fromStdString(JSON["USART_dynamic_tests"][j][ JSON["USART_dynamic_tests"][j].getMemberNames()[1] ].asString()))

                            DynamicTest[ k ]->setChecked(1);



}}

                         /* ************************  Requirements  ********************/


                            for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){
                             for(unsigned int l=0;l<JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[0] ].size();l++){

                                         for(unsigned int k =0 ;k< Requirement.size();k++){


                                 //JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[1] ]

                                if( Requirement[k]->text() == QString::fromStdString(JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[0] ][l].asString()))

                                    Requirement[ k ]->setChecked(1);



                            }}}

                         for (unsigned int j = 0; j < JSON["USART_dynamic_tests"].size()  ; j++){
                             for(unsigned int l=0;l<JSON["USART_dynamic_tests"][j][ JSON["USART_dynamic_tests"][j].getMemberNames()[0] ].size();l++){


                                for(unsigned int k =0 ;k< Requirement.size();k++){

                                if( ! Requirement[ k ]->checkState() &&

                                   Requirement[k]->text() == QString::fromStdString(JSON["USART_dynamic_tests"][j][ JSON["USART_dynamic_tests"][j].getMemberNames()[0] ][l].asString()))

                                    Requirement[ k ]->setChecked(1);



                            }}}




                    }



}


}



}

void Read::onSaveChanegeButton(){


int f=0;
int U=0;
int ordreJSON =0;
int ordreJSON1=0;

JSON["USART_static_tests"].clear() ;
JSON["USART_dynamic_tests"].clear() ;


    for (unsigned int i = 0; i < member.size(); i++) {

        if (member[i] == "USART_dynamic_tests" ){
            for (unsigned int j=0 ; j < DynamicTest.size();j++){
              if (DynamicTest[j]->checkState() == Qt::Checked){

                    switch (j) {

                    case 0 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_001";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req000";

                        break;
                   case 1 :JSON["USART_dynamic_tests"][ ordreJSON  ]["test_id"] = "USART_D_002";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req002";
                        break;
                    case 2 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_003";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req003";
                        break;
                    case 3 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_004";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                        break;
                    case 4 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_005";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                        break;
                    case 5 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_006";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                        break;
                    case 6 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_007";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                        break;
                    case 7 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_008";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 8 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_009";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;


                    case 9 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_010";
                            JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 10 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_011";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 11 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_012";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 12 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_013";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 13 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_014";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 14 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_015";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req025";
                            break;

                    case 15 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_016";
                            JSON["USART_dynamic_tests"][ ordreJSON  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][1] ="USART_Req010";
                            break;

                    case 16 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_017";
                            JSON["USART_dynamic_tests"][ ordreJSON  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][1] ="USART_Req010";
                            break;

                    case 17 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_018";
                            JSON["USART_dynamic_tests"][ ordreJSON  ]["req_id"][0] ="USART_Req005";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][1] ="USART_Req011";
                            break;

                    case 18 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_019";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req016";
                            break;

                    case 19 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_020";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req016";
                            break;

                    case 20 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_021";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req016";
                            break;

                    case 21 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_022";
                            JSON["USART_dynamic_tests"][ ordreJSON  ]["req_id"][0] ="USART_Req022";
                             JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][1] ="USART_Req023";
                            break;

                    case 22 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_023";
                            JSON["USART_dynamic_tests"][ ordreJSON  ]["req_id"][0] ="USART_Req023";
                             JSON["USART_dynamic_tests"][ordreJSON++]["req_id"][1] ="USART_Req024";
                            break;

                    case 23 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_024";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req018";
                            break;

                    case 24 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_025";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req019";
                            break;

                    case 25 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_026";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;

                    case 26 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_027";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req013";
                            break;

                    case 27 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_028";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="USART_Req009";
                            break;

                    case 28 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_029";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;

                    case 29 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_030";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;
                    case 30 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_031";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;
                    case 31 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_032";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;
                    case 32 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_033";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;
                    case 33 :JSON["USART_dynamic_tests"][ordreJSON  ]["test_id"] = "USART_D_034";
                            JSON["USART_dynamic_tests"][ ordreJSON++]["req_id"][0] ="none";
                            break;
                    default:
                        break;
}
}
}}



        if (member[i] == "USART_static_tests" ){
            for (unsigned int j=0; j < staticTest.size() ;j++){

              if ( staticTest[j]->checkState() == Qt::Checked ){

                    switch (j) {

                    case 0 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_001";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req001";
                        break;
                    case 1 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_002";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req001";
                        break;
                    case 2 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_003";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req001";
                        break;
                    case 3 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_004";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req000";
                        break;
                    case 4 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_005";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req000";
                        break;
                    case 5 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_006";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req003";
                        break;
                    case 6 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_007";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req003";
                        break;
                    case 7 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_008";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                    case 8 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_009";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;


                    case 9 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 10 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 11 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 12 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 13 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_014";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 14 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_015";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req010";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req011";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req012";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req013";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req014";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req015";
                            break;

                   case 15 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_016";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req018";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req019";
                            break;

                   case 16 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_017";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req018";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req019";
                            break;

                   case 17 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_018";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req018";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req019";
                            break;

                   case 18 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_019";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req018";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req019";
                            break;

                   case 19 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_020";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req018";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req019";
                            break;

                   case 20 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_021";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 21 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_022";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 22 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_023";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 23 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_024";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 24 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_025";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 25 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_026";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 26 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_027";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;

                   case 27 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_028";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req004";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][1] ="USART_Req005";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][2] ="USART_Req006";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][3] ="USART_Req007";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][4] ="USART_Req008";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][5] ="USART_Req009";
                            break;


                   case 28 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_029";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 29 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_030";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 30 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_031";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 31 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_032";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 32 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_033";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 33 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_034";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 34 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_035";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 35 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_036";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 36 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_037";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 37 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_038";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 38 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_039";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 39 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_040";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 40 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_041";
                            JSON["USART_static_tests"][ordreJSON1  ]["req_id"][0] ="USART_Req016";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][1] ="USART_Req017";
                            break;

                   case 41 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_042";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req020";
                            break;

                   case 42 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_043";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req020";
                            break;

                   case 43 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_044";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req020";
                            break;

                   case 44 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_045";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req020";
                            break;

                   case 45 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_046";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req020";
                            break;


                   case 46 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_047";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req021";
                            break;

                   case 47 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_048";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req021";
                            break;


                   case 48 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_049";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req021";
                            break;

                   case 49 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_050";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req023";
                            break;

                   case 50 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_051";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req023";
                            break;

                   case 51 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_052";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req023";
                            break;

                   case 52 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_053";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req024";
                            break;

                   case 53 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_054";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req024";
                            break;

                   case 54 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_055";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="USART_Req024";
                            break;

                   case 55 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_056";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 56 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_057";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 57 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_058";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 58 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_059";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 59 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_060";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 60 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_061";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;

                   case 61 :JSON["USART_static_tests"][ordreJSON1  ]["test_id"] = "USART_S_062";
                            JSON["USART_static_tests"][ordreJSON1++]["req_id"][0] ="TBD";
                            break;











            }

        }


            }}




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

    //***************Save***************//
    std::ofstream JSONFILE;
     JSONFILE.open(filename.toLocal8Bit().constData());
    Json::StyledWriter styledWriter;
    JSONFILE << styledWriter.write(JSON);
    JSONFILE.close();
    QMessageBox::information(this,"done","File successful edited");
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
