#include "command.h"
#include <QDebug>
#include "action.h"


Device *Command::getDevice() const
{
    return device;
}

void Command::setDevice(Device *value)
{
    device = value;
}

QString Command::toString()
{
    return this->device->toString();
}

Command *Command::fromQString(QString str)
{
    Command *command = new Command();
    QRegExp rx("(<.+_)");
    rx.indexIn(str);
    QRegExp rx2("(<|_)");
    QString deviceName = rx.cap(1).remove(rx2);
    Device *device = Device::fromQString(deviceName);
    QRegExp rx3("(_.+:)");
    rx3.indexIn(str);
    QRegExp rx4("(_|:)");
    QString actionName = rx3.cap(1).remove(rx4);
    Action *action = Action::fromQString(actionName);
    QRegExp rx5("(-[A-Za-z0-9]+(=-?(\\d|[A-Za-z]|\\.)+)?)");
    int pos = 0;
    QList<QString> list;
    while((pos = rx5.indexIn(str, pos)) != -1)
    {
        list << rx5.cap(1);
//        qDebug() << rx5.cap(1) << endl;
        pos += rx5.matchedLength();
    }
    action->setFromQString(list);
    device->setAction(action);
    command->setDevice(device);
    return command;
}

Command::Command(QObject *parent) : QObject(parent)
{

}

Command::~Command()
{

}

