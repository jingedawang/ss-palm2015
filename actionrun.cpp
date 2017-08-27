#include "actionrun.h"

ActionRUN::ActionRUN(QObject *parent) : Action(parent)
{

}
ActionRUN::~ActionRUN()
{

}

void ActionRUN::setFreq(int value)
{
    str += " -freq=";
    str += QString::number(value);
}

void ActionRUN::setFreq(float value)
{
    str += " -freq=";
    str += QString::number(value);
}

void ActionRUN::setPower(int value)
{
    str += " -power=";
    str += QString::number(value);
}
void ActionRUN::setM()
{
    str += " -m";
}
void ActionRUN::setM(int value)
{
    str += " -m=";
    str += QString::number(value);
}
void ActionRUN::setQ()
{
    str += " -q";
}
void ActionRUN::setRoit(int start, int end)
{
    str += " -roit=(";
    str += QString::number(start);
    str += ",";
    str += QString::number(end);
    str += ")";
}
void ActionRUN::setMin(int value)
{
    str += " -min=";
    str += QString::number(value);
}
void ActionRUN::setMax(int value)
{
    str += " -max=";
    str += QString::number(value);
}
void ActionRUN::setEcho(int value)
{
    str += " -echo=";
    str += QString::number(value);
}
void ActionRUN::setNetFlow()
{
    str += " -netflow";
}
void ActionRUN::setRois(int start, int end)
{
    str += " -rois=(";
    str += QString::number(start);
    str += ",";
    str += QString::number(end);
    str += ")";
}

void ActionRUN::setCmra()
{
    str += " -cmra";
}

void ActionRUN::setCmrb()
{
    str += " -cmrb";
}
void ActionRUN::setCode(unsigned int value)
{
    str += " -code=";
    str += QString::number(value);
}
void ActionRUN::setCirc(float value)
{
    str += " -circ=";
    str += QString::number(value);
}
void ActionRUN::setRes(int res)
{
    str += " -res=";
    str += QString::number(res);
}
void ActionRUN::setAnti()
{
    str += " -anti";
}
void ActionRUN::setA()
{
    str += " -a";
}
void ActionRUN::setStrimu()
{
    str += " -strimu";
}
void ActionRUN::setStrgps()
{
    str += " -strgps";
}
QString ActionRUN::toString()
{
    return "RUN:" + str;
}
