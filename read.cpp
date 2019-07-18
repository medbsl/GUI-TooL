#include "read.h"
#include "ui_read.h"
#include <fstream>
#include "dist\json\json.h"

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


            widget->setLayout( canLayout );


//*****************************************************************************//
//****************************      TAB            ****************************//
//*****************************************************************************//
              QTabWidget *Tab= new QTabWidget(this);
              Tab->setGeometry(5,5,995, 835);
              Tab->addTab(scrollArea, "PLateform");
              Tab->addTab(new QScrollArea(this), "Usart");
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
    m_button = new QPushButton("Generate", this);
    m_button->setGeometry(QRect(QPoint(895, 855),QSize(100, 20)));
    connect(m_button,SIGNAL (clicked()), this, SLOT(onGenerateButton()));

}

Read::~Read()
{
    delete ui;
}
void Read::onBrowseButton(){
    QString filename=QFileDialog::getOpenFileName(
                this,tr("browse"), (" C:\ "), "json File(*.json)");
    QMessageBox::information(this,tr("File Name"), filename);
Json::Value root;
std::ifstream file(filename.toLocal8Bit().constData());
file >> root;
        // QString cin;
        // Json::Value root;
        // Json::Reader reader;
        // bool b = reader.parse()

}
void Read::onGenerateButton(){

}
