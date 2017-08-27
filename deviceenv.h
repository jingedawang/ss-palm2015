/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: deviceenv.h
 * Description: 环境状态，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEENV_H
#define DEVICEENV_H

#include <QObject>
#include "device.h"

class DeviceENV : public Device
{
    Q_OBJECT
public:
    DeviceENV();                                        //构造函数
    ~DeviceENV();                                       //析构函数
};

#endif // DEVICEENV_H
