#include <QDebug>
#include "commandmanager.h"

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{

}

CommandManager::~CommandManager()
{

}

CommandManager* CommandManager::commandManager = NULL;

CommandManager *CommandManager::getInstance()
{
    if(commandManager == NULL)
    {
        commandManager = new CommandManager();
    }
    return commandManager;
}

Command *CommandManager::createCommand(Device *device)
{
    Command* command = new Command();
    command->setDevice(device);
    return command;
}

QList<Command *> *CommandManager::parseCommand(QString parseStr)
{
    QList<Command *> *list = new QList<Command *>();
//    qDebug() << parseStr << endl;
    QRegExp rx("(<.+>)");
    rx.setMinimal(true);
    int pos = 0;
    while ((pos = rx.indexIn(parseStr, pos)) != -1) {
        Command *command = Command::fromQString(rx.cap(1));
        list->append(command);
        pos += rx.matchedLength();
    }
    return list;
}

