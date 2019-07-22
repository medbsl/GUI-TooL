#include "read.h"
#include "ui_read.h"
#include <fstream>


Read::Read(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Read)
{
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
//****************************    Brows  Button   ***************************//
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
}
void Read::onBrowseButton(){
    int s=0;
    filename=QFileDialog::getOpenFileName(
                this,tr("browse"), (" C:\ "), "json File(*.json)");
    QMessageBox::information(this,tr("File Name"), filename);




std::ifstream JSONFILE(filename.toLocal8Bit().constData(), std::ifstream::binary);


JSONFILE >> JSON;
member= JSON.getMemberNames();


 for (int i = 0; i < member.size(); i++) {
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


     for (int j = 0; j < JSON[member[i]].size() ; j++){
          for (int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){


              if(JSON[member[i]][j][JSON[member[i]][j].getMemberNames()[k]].type()==6)// array type "tableau"
              {
                   for (int l= 0; l < JSON[member[i]][j][JSON[member[i]][j].getMemberNames()[k]].size(); l++){



                   }

              }
              else  //n'est pas un tableau
              {
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

                  // Line Edit

                      lineEdit = new QLineEdit(this);
                      lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                      lineEdit->setText(QString::fromStdString(JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k] ].asString()));
                      layout->addWidget(lineEdit, s,1);
                      name.push_back(JSON[member[i]][j].getMemberNames()[k]);
                      value.push_back(lineEdit);

              }





                }
     }
} //end if


     else if(member[i] == "interfaces" && JSON["interfaces"][0][ JSON["interfaces"][0].getMemberNames()[4] ].asString() == "USART"){

                     for (int j = 0; j < JSON[member[i]].size() ; j++){
                          for (int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){

                          // Label
                              QLabel *Label = new QLabel(this);
                              Label->setGeometry(QRect(QPoint(50, 138),QSize(176, 25)));
                              Label->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
                              Label->setText(QString::fromStdString( JSON["interfaces"][j].getMemberNames()[k]));


                              QFont fontSTLINK;
                              fontSTLINK.setFamily("MS Shell Dlg 2");
                              fontSTLINK.setPointSize(10);
                              fontSTLINK.setBold(false);
                              Label->setFont(fontSTLINK);

                             layoutUsart->addWidget(Label, ++s,0);

                          // Line Edit

                              lineEdit = new QLineEdit(this);
                              lineEdit->setGeometry(QRect(QPoint(230, 138),QSize(176, 27)));
                              lineEdit->setText(QString::fromStdString((JSON["interfaces"][j][ JSON["interfaces"][j].getMemberNames()[k]]).asString()));
                              layoutUsart->addWidget(lineEdit, s,1);

                              valueUsart.push_back(lineEdit);











                       }
             }
                     if(JSON["USART_static_tests"]){

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


                         for (int j = 0; j < JSON["USART_static_tests"].size() ; j++){
                              for (int k = 0; k < JSON["USART_static_tests"][j].getMemberNames().size(); k++){

                         QCheckBox *StaticTestUsart =new QCheckBox(QString::fromStdString(

                            JSON["USART_static_tests"][j][ JSON["USART_static_tests"][j].getMemberNames()[1] ].asString()),this);
                         StaticTestUsart->setChecked(1);

                         layoutUsart->addWidget(StaticTestUsart, ++s,0);
                     }}}



}






















 }


}
void Read::onSaveChanegeButton(){

int f=0;
    for (int i = 0; i < member.size(); i++) {
        if (member[i] !="USART_static_tests" && member[i] !="USART_dynamic_tests"&& member[i] !="interfaces"){
        for (int j = 0; j < JSON[member[i]].size() ; j++){
             for (int k = 0; k < JSON[member[i]][j].getMemberNames().size(); k++){

    if(JSON[member[i]][j][JSON[member[i]][j].getMemberNames()[k]].type()==6)// array type "tableau"
    {

    }
    else //n'est pas un tableau
    {
        JSON[member[i]][j][ JSON[member[i]][j].getMemberNames()[k]] =value[f++]->text().toLocal8Bit().constData();

    }


            }
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
