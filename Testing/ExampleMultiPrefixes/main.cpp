
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    pre_Model_QTGUIExample pre_m;
    post_Model_QTGUIExample post_m;
    w.setModel(pre_m,post_m);
    w.show();

    return a.exec();
}


