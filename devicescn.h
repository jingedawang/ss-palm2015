/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicescn.h
 * Description: 扫描电机，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICESCN_H
#define DEVICESCN_H

#include <QObject>
#include "device.h"

class DeviceSCN : public Device
{
public:
    DeviceSCN();                                        //构造函数
    ~DeviceSCN();                                       //析构函数
};

#endif // DEVICESCN_H
