/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: deviceucm.h
 * Description: USB相机，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEUCM_H
#define DEVICEUCM_H

#include <QObject>
#include "device.h"

class DeviceUCM : public Device
{
public:
    DeviceUCM();                                        //构造函数
    ~DeviceUCM();                                       //析构函数
};

#endif // DEVICEUCM_H
