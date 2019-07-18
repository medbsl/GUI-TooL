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

namespace Ui {
class Read;
}

class Read : public QDialog
{
    Q_OBJECT

public:
    explicit Read(QWidget *parent = 0);
     QGridLayout *canLayout    = new QGridLayout(this);
     QString filename;
    ~Read();

private slots:
     void onBrowseButton();
     void onGenerateButton();

private:
    Ui::Read *ui;
    QPushButton *browseButton,*m_button;
};

#endif // READ_H
