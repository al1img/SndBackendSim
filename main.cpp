#include <dbus-c++/dbus.h>
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;

    DBus::_init_threading();

    MainWindow w;
    w.show();

    return a.exec();
}
