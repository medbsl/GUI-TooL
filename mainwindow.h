#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"
#include "appdialog.h"
#include "dialog.h"
#include "read.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_Next1_clicked();
private:
    Ui::MainWindow *ui;
    SecDialog *secDialog;
    appDialog *APPDialog;
    Dialog *dialog;
    Read *read;

};

#endif // MAINWINDOW_H
