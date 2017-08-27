/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicestg.h
 * Description: 转台电机，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICESTG_H
#define DEVICESTG_H

#include <QObject>
#include "device.h"

class DeviceSTG : public Device
{
public:
    DeviceSTG();                                        //构造函数
    ~DeviceSTG();                                       //析构函数
};

#endif // DEVICESTG_H
