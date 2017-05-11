#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;

    MainWindow w;
    w.show();

    return a.exec();
}
