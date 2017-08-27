/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicecfg.h
 * Description: 设备配置信息，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICECFG_H
#define DEVICECFG_H

#include <QObject>
#include "device.h"

class DeviceCFG : public Device
{
public:
    DeviceCFG();                                        //构造函数
    ~DeviceCFG();                                       //析构函数
};

#endif // DEVICECFG_H
