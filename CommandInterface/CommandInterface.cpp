#include "CommandInterface.h"

using namespace am;
using namespace std;

CommandInterface::CommandInterface(DBus::Connection& connection,
                                   CommandInterfaceNotifications& notifications) :
    CommandInterfaceConverter(connection, notifications)
{
    mThread = thread(&CommandInterface::run, this);
}

CommandInterface::~CommandInterface()
{
    DBus::default_dispatcher->leave();

    mThread.join();
}

void CommandInterface::run()
{
    DBus::default_dispatcher->enter();
}
