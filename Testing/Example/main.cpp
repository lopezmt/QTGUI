
#include <QApplication>
#include "QTGUIExampleModel.h"
#include "QTGUIExampleSave.h"
#include "QTGUIExampleLoad.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QTGUIExampleModel m;
    w.setModel(m);
    w.show();

    return a.exec();
}


