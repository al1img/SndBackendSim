#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <audiomanager/audiomanagertypes.h>

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mBus(DBus::Connection::SessionBus())
{
    mCommandInterface = new CommandInterface(mBus);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mCommandInterface;
}

void MainWindow::onBtnConnect()
{
    try
    {
        std::vector<am::am_SinkType_s> sinks;

        auto result = mCommandInterface->GetListMainSinks(sinks);

        qDebug() << "List result:" << result << "count:" << sinks.size();

        for(auto sink : sinks)
        {
            qDebug() << "sinkID:" << sink.sinkID << "name:" << sink.name.c_str()
                     << "sinkClassID:" << sink.sinkClassID;
        }
    }
    catch(const DBus::Error& e)
    {
        qDebug() << "Error:" << e.what();
    }
}
