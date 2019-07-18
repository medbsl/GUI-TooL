#ifndef APPDIALOG_H
#define APPDIALOG_H

#include <QHBoxLayout>
#include <QDialog>
class QLineEdit;

namespace Ui {
class appDialog;
}

class appDialog : public QDialog
{
    Q_OBJECT

public:
    explicit appDialog(QWidget *parent = 0);
    ~appDialog();

private slots:
    void on_pushButton_clicked();

    void on_scrollAreaWidgetContents_2_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_5_clicked();

private:
    Ui::appDialog *ui;
    QLineEdit* m_line;
};

#endif // APPDIALOG_H
