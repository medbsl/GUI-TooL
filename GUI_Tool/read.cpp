#include "read.h"
#include "ui_read.h"
#include <fstream>
#include <QDebug>
#include "mainwindow.h"


unsigned int counterRequirement =0;
unsigned int counterStatic =0;
unsigned int counterDynamic =0;
bool newfile =false;
 Read::Read(QWidget *parent, QString filename,bool newFile) : QDialog(parent), ui(new Ui::Read){

    newfile =newFile;
    ui->setupUi(this);
    
    onBrowseButton(filename, newFile);




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

void Read::Test(QGridLayout *layout, int s){

/*
    QString add;
    QString add2;
    QString add3;


                        QPushButton *checkAllTestStatic =new QPushButton("Select ALL",this);
                        connect(checkAllTestStatic,SIGNAL (clicked()), this, SLOT(onCheckAllTestStatic()));
                        layout->addWidget(checkAllTestStatic,s,0);

                        QPushButton *checkAllTestDynamic =new QPushButton("Select ALL",this);
                        connect(checkAllTestDynamic,SIGNAL (clicked()), this, SLOT(onCheckAllTestDynamic()));
                        layout->addWidget(checkAllTestDynamic,s,1);

                        QPushButton *checkAllTestReq =new QPushButton("Select ALL",this);
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
        connect(Requirement[i],SIGNAL (clicked() ), this, SLOT( requirement()));*/


}

void Read::onBrowseButton(QString filename, bool newFile){


    int s=0;


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

                            /* ************************  Requirements  ********************/
                                        s-= DynamicTest.size();

                        /*  for (unsigned int j = 0; j < JSON["USART_static_tests"].size()  ; j++){
             for(unsigned int l=0;l<JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[0] ].size();l++){



     QCheckBox * box = new QCheckBox(QString::fromStdString(JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[0] ][l].asString()) ,this);
     if( JSON["USART_static_tests"][j]["testcheck"].asString() == "ON" ||JSON["USART_dynamic_tests"][j]["testcheck"].asString() == "ON" )
            box->setChecked(1);
     if(JSON["USART_static_tests"][j]["testcheck"].asString() == "OFF" ||JSON["USART_dynamic_tests"][j]["testcheck"].asString() == "OFF")
            box->setChecked(0);
      // QString k = QString::fromStdString(JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[0] ][l].asString());

         Requirement.push_back(box);
         layoutUsart->addWidget(box,++s,2);




            }}*/


                    }


}


}
}

void Read::onSaveChanegeButton(){


int f=0;
int U=0;
int ordreJSON =0;
int ordreJSON1=0;




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

    //***************Save***************//

     if(newfile){

         QString NewfileName = QFileDialog::getSaveFileName(this,tr("browse"), filename, "json File(*.json)");
         std::ofstream JSONFILE;
         JSONFILE.open(NewfileName.toLocal8Bit().constData());
         Json::StyledWriter styledWriter;
         JSONFILE << styledWriter.write(JSON);
         JSONFILE.close();
         QMessageBox::information(this,"done","New File successful created");
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

bool Read::getNewFile(){
    return newFile;
}
