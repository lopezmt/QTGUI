#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Load_QTGUIExample.h"
#include "Save_QTGUIExample.h"
#include "Model_QTGUIExample.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Model_QTGUIExample m;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // getter and setter for the model
    void setModel(Model_QTGUIExample m_pre);
    Model_QTGUIExample getModel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
