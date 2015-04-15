#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// set model
void MainWindow::setModel(pre_Model_QTGUIExample tmp_pre_m ,
                          post_Model_QTGUIExample tmp_post_m
                         )
{
    this->pre_m = tmp_pre_m ;
    this->post_m = tmp_post_m ;
}

// Save Listener
// - Updates the model with data from GUI
void MainWindow::on_pushButton_clicked()
{

    pre_m.setpre_checkBoxsdf(ui->pre_checkBoxsdf->isChecked());

    post_m.setpost_radioButton_3(ui->post_radioButton_3->isChecked());

    post_m.setpost_spinBox(ui->post_spinBox->value());

    pre_Save_QTGUIExample pre_save;
    pre_save.save(pre_m,"pre_dataMulti.xml");
    post_Save_QTGUIExample post_save;
    post_save.save(post_m,"post_dataMulti.xml");
}

// Load Listener
// - Updates the GUI with data from the model
void MainWindow::on_pushButton_2_clicked()
{
    pre_Load_QTGUIExample pre_loader;
    pre_loader.load(pre_m,"pre_dataMulti.xml");
    post_Load_QTGUIExample post_loader;
    post_loader.load(post_m,"post_dataMulti.xml");

    ui->pre_checkBoxsdf->setChecked(pre_m.getpre_checkBoxsdf());

    ui->post_radioButton_3->setChecked( post_m.getpost_radioButton_3());

    ui->post_spinBox->setValue(post_m.getpost_spinBox());

}
