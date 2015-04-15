#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "post_Load_QTGUIExample.h"
#include "post_Save_QTGUIExample.h"
#include "post_Model_QTGUIExample.h"
#include "pre_Load_QTGUIExample.h"
#include "pre_Save_QTGUIExample.h"
#include "pre_Model_QTGUIExample.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    pre_Model_QTGUIExample pre_m;
    post_Model_QTGUIExample post_m;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // getter and setter for the model
    void setModel(pre_Model_QTGUIExample tmp_pre_m , post_Model_QTGUIExample tmp_post_m);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
