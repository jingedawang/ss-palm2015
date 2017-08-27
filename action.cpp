#include "action.h"
#include "actionrpt.h"

Action::Action(QObject *parent) : QObject(parent)
{

}

Action::~Action()
{

}

QString Action::toString()
{
    return "From Action.";
}

Action *Action::fromQString(QString actionName)
{
    if(actionName == "RPT")
    {
        return new ActionRPT();
    }
    else
        return 0;
}

void Action::setFromQString(QList<QString> list)
{

}

void Action::notify()
{

}
