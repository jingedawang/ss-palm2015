/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicedmi.h
 * Description: DMI参数，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEDMI_H
#define DEVICEDMI_H

#include <QObject>
#include "device.h"

class DeviceDMI : public Device
{
public:
    DeviceDMI();                                        //构造函数
    ~DeviceDMI();                                       //析构函数
};

#endif // DEVICEDMI_H
