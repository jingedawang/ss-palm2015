#include "actionstp.h"

ActionSTP::ActionSTP()
{

}
ActionSTP::~ActionSTP()
{

}
void ActionSTP::setStpimu()
{
    str += " -stpimu";
}
void ActionSTP::setStpgps()
{
    str += " -stpgps";
}
QString ActionSTP::toString()
{
    return "STP:" + str;
}

void ActionSTP::notify()
{

}
