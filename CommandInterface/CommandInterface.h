#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include <thread>

#include "CommandInterfaceConverter.h"

class CommandInterface : public CommandInterfaceConverter
{
public:
    CommandInterface(DBus::Connection& connection,
                     CommandInterfaceNotifications& notifications);
    ~CommandInterface();

private:
    std::thread mThread;

    void run();

};

#endif // COMMANDINTERFACE_H
