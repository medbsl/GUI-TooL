#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>


namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_21_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
