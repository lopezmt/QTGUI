
#include <QApplication>
#include "model.h"
#include "saver.h"
#include "loader.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    model m;
    w.setModel(m);
    w.show();

    return a.exec();
}


